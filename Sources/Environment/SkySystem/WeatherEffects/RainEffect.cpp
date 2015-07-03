#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	RainEffect::RainEffect(const UID& particleImageUID, const Vec& particlesSourcePosition)
		: DirectParticleEmitter(particleImageUID, particlesSourcePosition) {	
		//Logger::getInstance()->info("Rain effect runned constructor");
	}

	void RainEffect::createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		//Logger::getInstance()->info("Rain effect created");
	}

	void RainEffect::effect() {
		//Logger::getInstance()->info("Rain effect runned");
	}

	void RainEffect::destroyActions() {
		//Logger::getInstance()->info("Rain effect destroyed");
	}
}