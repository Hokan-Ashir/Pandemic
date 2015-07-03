#include <Headers/Environment/SkySystem/WeatherEffects/SunnyEffect.h>

namespace pan {
	SunnyEffect::SunnyEffect() {
		//Logger::getInstance()->info("Sunny effect runned constructor");
	}

	void SunnyEffect::createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		//Logger::getInstance()->info("Sunny effect created");
	}

	void SunnyEffect::effect() {
		//Logger::getInstance()->info("Sunny effect runned");
	}

	void SunnyEffect::destroyActions() {
		//Logger::getInstance()->info("Sunny effect destroyed");
	}
}