#include <Headers/DirectParticlesEmitter/DirectParticleEmitter.h>
#include <Headers/DirectParticlesEmitter/PatricleHitDetect.h>

namespace pan {
	DirectParticleEmitter::DirectParticleEmitter(UID particleImageUID, Vec particlesSourcePosition) {
		this->particlesSourcePosition = particlesSourcePosition;
		this->particleImageUID = particleImageUID;
		create();
	}

	DirectParticleEmitter::~DirectParticleEmitter() {
	}

	void DirectParticleEmitter::create() {
		surroundingBox.set(25, 1, 25);
		auto image = Images(particleImageUID);
		auto color = Color(153, 153, 153, 116);
		auto numberOfParticles = Random(2000, 3000); //Random drops from 2000 to 3000
		Flt radius = 0.0; //for first time rain don't exist.
		Flt life_avg = 5.0; //How long rain live.

		particles.create(image, color, numberOfParticles, radius, life_avg);
		particles.source(surroundingBox);
		particles.accel.set(0, -25, 0); //All drops move down
		particles.vel_random = 100.0; //How far away from the formed particle falling drops
		particles.damping = 0.98;
	}

	void DirectParticleEmitter::draw() {
		particles.draw();
	}

	void DirectParticleEmitter::update() {
		particles.update();

		std::vector<ACTOR_GROUP> actorGroups;
		actorGroups.push_back(AG_TERRAIN);
		ParticleHitDetect hited(actorGroups);

		surroundingBox.set(25, 1, 25, particlesSourcePosition);
		particles.matrix.set(surroundingBox, particlesSourcePosition);

		for (auto i = 0; i < particles.p.elms(); ++i) {
			auto particle = particles.p(i);
			Physics.cuts(Capsule(0.1, particle.pos, particle.pos + Vec(0, 0.5, 0)), hited);
			if (hited.isCollided()) {
				particle.life = 20; //How long all drops live
				particles.radius = RandomF(0.4, 0.8); //How big are all drops (radius)
				particle.ang_vel = 20;
			}
			hited.setIsCollided(false);
		}
	}


	Vec DirectParticleEmitter::getDirection() const {
		return particles.accel;
	}

	void DirectParticleEmitter::setDirection(Vec direction) {
		particles.accel.set(direction.x, direction.y, direction.z);
	}

	Flt DirectParticleEmitter::getParticlesLifeTime() const {
		return particles.life;
	}

	void DirectParticleEmitter::setParticlesLifeTime(Flt lifeTime) {
		particles.life = lifeTime;
	}
}