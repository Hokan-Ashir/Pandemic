#ifndef __DIRECTPARTICLEEMITTER_H__
#define __DIRECTPARTICLEEMITTER_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/EventSystem/Events/DrawEvent.h>

namespace pan {

	/**
	 * Class, that describes emitting set of particles from some position
	 */
	class DirectParticleEmitter : public BaseEventHandler {
	public:
		DirectParticleEmitter(UID particleImageUID, Vec particlesSourcePosition);
		~DirectParticleEmitter();
		void draw(const DrawEvent* eventToProceed);
		void update();
		Vec getDirection() const;
		void setDirection(Vec direction);
		Flt getParticlesLifeTime() const;
		void setParticlesLifeTime(Flt lifeTime);

	private:
		void create();

		Box surroundingBox;
		Particles particles;
		Vec particlesSourcePosition;
		UID particleImageUID;
	};
}

#endif