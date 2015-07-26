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
		auto horizonColourImageUID = UID(220838454, 1105424687, 738437037, 3218905559); // Images/Sky/HorizontColour
		fillInterpolatorWithImageData(&horizonColors, horizonColourImageUID);
	}

	void SkyColourSystem::initializeSkyColourInterpolator() {
		skyColors.loop = true;
		skyColors.min_x = -SUN_HEIGHT;
		skyColors.max_x = SUN_HEIGHT;

		auto skyColourImageUID = UID(1536787649, 1302548901, 3357141931, 2032443279); // Images/Sky/SkyColour
		fillInterpolatorWithImageData(&skyColors, skyColourImageUID);
	}

	void SkyColourSystem::fillInterpolatorWithImageData(Interpolator<Vec4>* interpolator, UID imageUID) {
		ImagePtr image = imageUID;
		Int width = image()->w();
		Int height = image()->h();

		image()->lockRead();
		Vec4 color = image()->color(0, height - 1).asVec4();
		interpolator->add(-SUN_HEIGHT, color);

		int index;
		for (auto i = -1.0; i <= 1.0; i += 0.25)	{
			index = (i + 1) * ((width - 1) / 2);
			color = image()->color(index, height - 1).asVec4();
			interpolator->add(i, color);
		}

		color = image()->color(width - 1, height - 1).asVec4();
		interpolator->add(SUN_HEIGHT, color);
		image()->unlock();

		image = NULL;
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