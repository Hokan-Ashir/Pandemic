#include <Headers/DayNightCircleSystem/SkySystem.h>

namespace pan {
	SkySystem::SkySystem() {
	}

	SkySystem::~SkySystem() {
	}

	void SkySystem::update() {
		auto sunHeightOverHorizont = starsSystem.getBarycenterHeightOverHorizont();
		dayNightCircleSystem.setSunHeightOverHorizont(sunHeightOverHorizont);
		dayNightCircleSystem.update();

		starsSystem.update();
	}
}