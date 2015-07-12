#ifndef __RAINEFFECT_H__
#define __RAINEFFECT_H__

#include "AbstractWeatherEffect.h"
#include <Headers/DirectParticlesEmitter/DirectParticleEmitter.h>
#include "WeatherTypeEvent.h"

namespace pan {
	class RainEffect : public AbstractWeatherEffect, public BaseEventHandler {
	public:
		explicit RainEffect();
		void createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) override;
		void destroyActions() override;
	protected:
		void handleEvent(const WeatherTypeEvent* event);
		bool predicateEvent(const WeatherTypeEvent* event);
	private:
		DirectParticleEmitter* emitter;
	};
}

#endif
