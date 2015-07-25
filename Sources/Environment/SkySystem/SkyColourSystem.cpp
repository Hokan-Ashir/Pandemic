#include <Headers/Environment/SkySystem/SkyColourSystem.h>

namespace pan {

	SkyColourSystem::SkyColourSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &SkyColourSystem::update);
		initializeHorisonColourInterpolator();
		initializeSkyColourInterpolator();
	}

	void SkyColourSystem::initializeHorisonColourInterpolator() {
		horizonColors.loop = true;
		horizonColors.min_x = -SUN_HEIGHT;
		horizonColors.max_x = SUN_HEIGHT;

		// TODO make latitude/day-of-year-dependent sky/horizont colour changes
		// loading sky/horizont colour via gradient image
		horizonColors.add(-SUN_HEIGHT, createColour(30, 40, 56));

		horizonColors.add(-1, createColour(30, 40, 56));
		horizonColors.add(-0.75, createColour(30, 40, 56));
		horizonColors.add(-0.5, createColour(65, 86, 112));
		horizonColors.add(-0.25, createColour(114, 68, 56));
		horizonColors.add(0, createColour(145, 84, 99));
		horizonColors.add(0.25, createColour(232, 193, 115));
		horizonColors.add(0.5, createColour(113, 234, 222));
		horizonColors.add(0.75, createColour(155, 240, 232));
		horizonColors.add(1, createColour(201, 248, 243));
		
		horizonColors.add(SUN_HEIGHT, createColour(201, 248, 243));
	}

	void SkyColourSystem::initializeSkyColourInterpolator() {
		skyColors.loop = true;
		skyColors.min_x = -SUN_HEIGHT;
		skyColors.max_x = SUN_HEIGHT;

		Vec4 colour(15, 31, 47, 255);
		auto hsbColor =  RgbToHsb(colour.v3());
		skyColors.add(-SUN_HEIGHT, colour / 255);

		for (auto i = -1.0; i <= 1.0; i += 0.25) {
			colour = Vec4(HsbToRgb(hsbColor), 255);
			skyColors.add(i, colour / 255);
			// during night sky become brighter/darker faster than during day
			if (i >= 0) {
				hsbColor.z += 18.5;
			} else {				
				hsbColor.z += 25;
			}
		}
		
		skyColors.add(SUN_HEIGHT, colour / 255);
	}

	Vec4 SkyColourSystem::createColour(Byte r, Byte g, Byte b, Byte a) {
		return Vec4(r, g, b, a) / 255;
	}

	void SkyColourSystem::setSkyColour(Flt sunHeightOverHorizont) {
		auto horizonColour = horizonColors(sunHeightOverHorizont);
		auto skyColour = skyColors(sunHeightOverHorizont);		
		Sky.atmosphericColor(horizonColour, skyColour);
	}

	void SkyColourSystem::update(const SunHeightChangedEvent* event) {
		setSkyColour(event->getHeightOverHorizont());
	}
}