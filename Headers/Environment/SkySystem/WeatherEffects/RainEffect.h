#ifndef __RAINEFFECT_H__
#define __RAINEFFECT_H__

#include "AbstractWeatherEffect.h"
#include <Headers/DirectParticlesEmitter/DirectParticleEmitter.h>

namespace pan {
	class RainEffect : public AbstractWeatherEffect, public DirectParticleEmitter {
	public:
		explicit RainEffect(const UID& particleImageUID = UIDZero, const Vec& particlesSourcePosition = VecZero);
		void createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) override;
		void effect() override;
		void destroyActions() override;
	};
}

#endif
