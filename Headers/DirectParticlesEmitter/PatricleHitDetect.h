#ifndef __PARTICLEHITDETECT_H__
#define __PARTICLEHITDETECT_H__

#include <vector>
#include <Engine/Headers/EsenthelEngine.h>

class ParticleHitDetect : public PhysCutsCallback
{
public:
	explicit ParticleHitDetect(std::vector<ACTOR_GROUP>& actorGroups);

	virtual ~ParticleHitDetect();

private:
	Bool collided;
	std::vector<ACTOR_GROUP>& collidableActorGroups;

	virtual Bool hit(ActorInfo& actorInfo) override;

public:
	Bool isCollided() const;
	void setIsCollided(Bool isCollided);
};

#endif