#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	RainEffect::RainEffect() {
	}

	void RainEffect::createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		EventManager::getInstance()->registerEventHandlerMethod(this, &RainEffect::handleEvent, &RainEffect::predicateEvent);
		emitter = new DirectParticleEmitter(UID(1305126526, 1249254078, 2971936397, 3966274079), Vec(0, 10, 0));
	}

	void RainEffect::handleEvent(const WeatherTypeEvent* event) {
		emitter->update();
	}

	bool RainEffect::predicateEvent(const WeatherTypeEvent* event) {
		return event->getWeatherType() == RAIN;
	}

	void RainEffect::destroyActions() {
		delete emitter;
		EventManager::getInstance()->unregisterEventHandlerMethod(this, &RainEffect::handleEvent);
	}
}