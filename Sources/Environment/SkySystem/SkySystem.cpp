#include <Headers/Environment/SkySystem/SkySystem.h>

namespace pan {
	SkySystem::SkySystem() {
	}

	SkySystem::~SkySystem() {
	}

	void SkySystem::setSunHeightOverHorizont(Flt heightOverHorizont) {
		this->sunHeightOverHorizont = heightOverHorizont;
	}

	void SkySystem::update() {		
		dayNightCircleSystem.setSunHeightOverHorizont(sunHeightOverHorizont);
		dayNightCircleSystem.update();

		cloudsSystem.update();
	}
}