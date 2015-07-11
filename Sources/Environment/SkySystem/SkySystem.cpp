#include <Headers/Environment/SkySystem/SkyColourSystem.h>
#include <Headers/Core/DateTime.h>

namespace pan {
	void SkyColourSystem::initializeHorisonColourInterpolator() {
		horizonColors.loop = true;
		horizonColors.min_x = -SUN_HEIGHT;
		horizonColors.max_x = SUN_HEIGHT;
				
		horizonColors.add(getHeightOverHorizont(0), createColour(30, 40, 56));
		horizonColors.add(getHeightOverHorizont(5), createColour(97, 113, 136));
		horizonColors.add(getHeightOverHorizont(7), createColour(110, 136, 152));
		horizonColors.add(getHeightOverHorizont(12), createColour(121, 142, 164));		
		horizonColors.add(getHeightOverHorizont(15), createColour(121, 137, 154));
		horizonColors.add(getHeightOverHorizont(20), createColour(130, 130, 110));
		horizonColors.add(getHeightOverHorizont(21), createColour(111, 111, 105));
		horizonColors.add(getHeightOverHorizont(22), createColour(72, 80, 101));

		horizonColors.add(-SUN_HEIGHT, createColour(30, 40, 56));
		horizonColors.add(SUN_HEIGHT, createColour(121, 142, 164));
	}

	void SkyColourSystem::initializeSkyColourInterpolator() {
		skyColors.loop = true;
		skyColors.min_x = -SUN_HEIGHT;
		skyColors.max_x = SUN_HEIGHT;

		skyColors.add(getHeightOverHorizont(0), createColour(12, 16, 23));
		skyColors.add(getHeightOverHorizont(5), createColour(61, 87, 124));
		skyColors.add(getHeightOverHorizont(7), createColour(78, 107, 149));
		skyColors.add(getHeightOverHorizont(12), createColour(70, 107, 161));
		skyColors.add(getHeightOverHorizont(15), createColour(58, 95, 144));
		skyColors.add(getHeightOverHorizont(20), createColour(59, 82, 126));
		skyColors.add(getHeightOverHorizont(21), createColour(41, 57, 89));
		skyColors.add(getHeightOverHorizont(22), createColour(26, 30, 41));

		skyColors.add(-SUN_HEIGHT, createColour(12, 16, 23));
		skyColors.add(SUN_HEIGHT, createColour(70, 107, 161));
	}

	SkyColourSystem::SkyColourSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &SkyColourSystem::update);
		initializeHorisonColourInterpolator();
		initializeSkyColourInterpolator();
	}

	Vec4 SkyColourSystem::createColour(Byte r, Byte g, Byte b, Byte a) {
		return Vec4(r, g, b, a) / 255;
	}

	Flt SkyColourSystem::getHeightOverHorizont(Flt hour) const	{
		if (hour >= HOURS_IN_DAY / 2) {
			hour = HOURS_IN_DAY - hour;
		} 

		// 1 is radius of AstroSphere (see comment to "pos" member in Astro.h in Esenethel Engine)
		return hour / (HOURS_IN_DAY / 2 / SUN_HEIGHT) - 1;
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