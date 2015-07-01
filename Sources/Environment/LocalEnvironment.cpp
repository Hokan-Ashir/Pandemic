#include <Headers/Environment/LocalEnvironment.h>

namespace pan {
	LocalEnvironment::LocalEnvironment() {
	}

	LocalEnvironment::~LocalEnvironment() {
	}

	void LocalEnvironment::update()	{
		auto baryCenterHeightOverHorizont = starsSystem.getBarycenterHeightOverHorizont();
		skySystem.setSunHeightOverHorizont(baryCenterHeightOverHorizont);

		starsSystem.update();
		skySystem.update();
	}
}