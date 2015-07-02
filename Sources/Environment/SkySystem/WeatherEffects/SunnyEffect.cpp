#include <Headers/Environment/SkySystem/WeatherEffects/SunnyEffect.h>

namespace pan {
	SunnyEffect::SunnyEffect() {
		//Logger::getInstance()->info("Sunny effect runned constructor");
	}

	void SunnyEffect::create(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		//Logger::getInstance()->info("Sunny effect created");
		setIsCreated(true);
	}

	void SunnyEffect::effect() {
		//Logger::getInstance()->info("Sunny effect runned");
	}

	void SunnyEffect::destroy() {
		//Logger::getInstance()->info("Sunny effect destroyed");
		setIsCreated(false);
	}
}