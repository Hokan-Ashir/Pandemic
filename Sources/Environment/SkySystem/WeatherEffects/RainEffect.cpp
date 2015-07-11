#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	RainEffect::RainEffect() {
	}

	void RainEffect::createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) {
		EventManager::getInstance()->registerEventHandlerMethod(this, &RainEffect::handleEventAction);
		emitter = new DirectParticleEmitter(UID(1305126526, 1249254078, 2971936397, 3966274079), Vec(0, 10, 0));
	}

	void RainEffect::handleEventAction(const WeatherTypeEvent<RAIN>* event) {
		emitter->update();
	}

	void RainEffect::destroyActions() {
		delete emitter;
		EventManager::getInstance()->unregisterEventHandlerMethod(this, &RainEffect::handleEventAction);
	}
}