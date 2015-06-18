#ifndef __DIRECTPARTICLE_SYSTEM_H__
#define __DIRECTPARTICLE_SYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Drawable.h>
#include <Headers/ToolClasses/Updatable.h>

class DirectParticleSystem : public Drawable, public Updateable
{
public:
	DirectParticleSystem(UID particleImageUID, Vec particlesSourcePosition);
	~DirectParticleSystem();	
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

#endif