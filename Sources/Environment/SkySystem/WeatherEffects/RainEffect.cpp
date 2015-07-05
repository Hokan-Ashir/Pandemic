#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	RainEffect::RainEffect(const UID& particleImageUID, const Vec& particlesSourcePosition)
		: DirectParticleEmitter(particleImageUID, particlesSourcePosition) {	
	}

	void RainEffect::createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
	}

	void RainEffect::effect() {
	}

	void RainEffect::destroyActions() {
	}
}