#include <Headers/Environment/SkySystem/SkyColourSystem.h>

namespace pan {

	SkyColourSystem::SkyColourSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &SkyColourSystem::update);
		Sky.atmosphericHorizonExponent(0.0);
		initializeHorisonColourInterpolator();
		initializeSkyColourInterpolator();
	}

	void SkyColourSystem::initializeHorisonColourInterpolator() {
		horizonColors.loop = true;
		horizonColors.min_x = -MAXIMUM_SUN_HEIGHT;
		horizonColors.max_x = MAXIMUM_SUN_HEIGHT;

		// TODO make latitude/day-of-year-dependent sky/horizont colour changes
		auto horizonColourImageUID = UID(220838454, 1105424687, 738437037, 3218905559); // Images/Sky/HorizontColour
		fillInterpolatorWithImageData(&horizonColors, horizonColourImageUID);
	}

	void SkyColourSystem::initializeSkyColourInterpolator() {
		skyColors.loop = true;
		skyColors.min_x = -MAXIMUM_SUN_HEIGHT;
		skyColors.max_x = MAXIMUM_SUN_HEIGHT;

		auto skyColourImageUID = UID(1536787649, 1302548901, 3357141931, 2032443279); // Images/Sky/SkyColour
		fillInterpolatorWithImageData(&skyColors, skyColourImageUID);
	}

	void SkyColourSystem::fillInterpolatorWithImageData(Interpolator<Vec4>* interpolator, UID imageUID) {
		ImagePtr image = imageUID;
		Int width = image()->w();
		Int height = image()->h();

		image()->lockRead();
		Vec4 color = image()->color(0, height - 1).asVec4();
		interpolator->add(-MAXIMUM_SUN_HEIGHT, color);

		int index;
		for (auto i = -MAXIMUM_SUN_HEIGHT / 2; i <= MAXIMUM_SUN_HEIGHT / 2; i += INTERPOLATION_STEP) {
			index = (i + MAXIMUM_SUN_HEIGHT / 2) * ((width - 1) / 2);
			color = image()->color(index, height - 1).asVec4();
			interpolator->add(i, color);
		}

		color = image()->color(width - 1, height - 1).asVec4();
		interpolator->add(MAXIMUM_SUN_HEIGHT, color);
		image()->unlock();

		image = NULL;
	}

	void SkyColourSystem::update(const SunHeightChangedEvent* event) {
		auto horizonColour = horizonColors(event->getHeightOverHorizont());
		auto skyColour = skyColors(event->getHeightOverHorizont());
		Sky.atmosphericColor(horizonColour, skyColour);
	}
}