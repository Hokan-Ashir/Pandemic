#ifndef __DIRECTPARTICLE_SYSTEM_H__
#define __DIRECTPARTICLE_SYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/IDrawable.h>
#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class DirectParticleEmitter : public IDrawable, public IUpdateable {
	public:
		DirectParticleEmitter(UID particleImageUID, Vec particlesSourcePosition);
		~DirectParticleEmitter();
		void draw() override;
		void update() override;
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