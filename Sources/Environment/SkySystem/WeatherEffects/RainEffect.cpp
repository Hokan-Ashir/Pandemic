#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	RainEffect::RainEffect(const UID& particleImageUID, const Vec& particlesSourcePosition)
		: DirectParticleEmitter(particleImageUID, particlesSourcePosition) {	
		//Logger::getInstance()->info("Rain effect runned constructor");
	}

	void RainEffect::create(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		//Logger::getInstance()->info("Rain effect created");
		setIsCreated(true);
	}

	void RainEffect::effect() {
		//Logger::getInstance()->info("Rain effect runned");
	}

	void RainEffect::destroy() {
		//Logger::getInstance()->info("Rain effect destroyed");
		setIsCreated(false);
	}
}