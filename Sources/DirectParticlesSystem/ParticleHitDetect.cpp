#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/DirectParticlesSystem/PatricleHitDetect.h>

ParticleHitDetect::ParticleHitDetect(std::vector<ACTOR_GROUP>& actorGroups) :
collided(false), collidableActorGroups(actorGroups) {
}

ParticleHitDetect::~ParticleHitDetect() {
}

Bool ParticleHitDetect::hit(ActorInfo &actorInfo) {
	if (actorInfo.obj) {
		collided = true;
		return false;
	}

	for (auto actorGroup : collidableActorGroups) {
		if (actorInfo.group == actorGroup) {
			collided = true;
			return false;
		}
	}	

	return true;
}

Bool ParticleHitDetect::isCollided() const {
	return collided;
}

void ParticleHitDetect::setIsCollided(Bool isCollided) {	 
	this->collided = isCollided;
}