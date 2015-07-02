#include <Headers/Environment/LocalEnvironment.h>

namespace pan {
	LocalEnvironment::LocalEnvironment() {
	}

	LocalEnvironment::~LocalEnvironment() {
	}

	void LocalEnvironment::update()	{
		auto baryCenterHeightOverHorizont = starsSystem.getBarycenterHeightOverHorizont();
		weatherSystem.setSunHeightOverHorizont(baryCenterHeightOverHorizont);

		starsSystem.update();
		weatherSystem.update();
	}
}