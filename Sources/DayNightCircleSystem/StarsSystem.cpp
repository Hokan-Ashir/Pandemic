#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/DayNightCircleSystem/StarsSystem.h>
#include <Headers/DayNightCircleSystem/DateTime.h>

namespace pan {

	void StarsSystem::createVigilantEye() {
		vigilantEye.sun.image = UID(2922889087, 1171051764, 3010789764, 3570309810); // Images/sun
		vigilantEye.sun.size = 0.15;
		vigilantEye.radiusToBarycenter = 0.1;		
		vigilantEye.angleSpeed = 0.001;
		vigilantEye.angle = 0;
		vigilantEye.sun.pos = Vec(
			barycenterPosition.x + vigilantEye.radiusToBarycenter, 
			barycenterPosition.y, 
			barycenterPosition.z
			);
	}

	void StarsSystem::createAllSeeinggEye() {
		allSeeingEye.sun.image = UID(2922889087, 1171051764, 3010789764, 3570309810); // Images/sun
		allSeeingEye.sun.size = 0.05;
		allSeeingEye.radiusToBarycenter = 0.2;	
		allSeeingEye.angleSpeed = 0.002;
		allSeeingEye.angle = 0;
		allSeeingEye.sun.pos = Vec(
			barycenterPosition.x + allSeeingEye.radiusToBarycenter,
			barycenterPosition.y,
			barycenterPosition.z
			);
	}

	StarsSystem::StarsSystem(Flt hour) : hour(hour) {
		barycenterPosition = Vec(0.2, 0.2, 0.0);
		initializeBarycenterSpherialAngles();
		createVigilantEye();
		createAllSeeinggEye();	
		Astros.add(vigilantEye.sun);
		Astros.add(allSeeingEye.sun);
	}

	void StarsSystem::initializeBarycenterSpherialAngles() {
		auto x = barycenterPosition.x;
		auto y = barycenterPosition.y;
		auto z = barycenterPosition.z;
		phi = Atan(y / x);
		theta = Atan(Sqrt(Pow(x, 2) + Pow(y, 2)) / z);
	}

	void StarsSystem::setSunRaysAndHeighlight(SunClass* sun) {
		auto rays = Sqrt(sun->pos.y);
		sun->rays_color = Lerp(0.02f, 0.14f, rays);
		sun->highlight_front = Lerp(0.80f, 0.20f, rays);
	}

	void StarsSystem::setStarPosition(Star* star) {	
		star->angle += star->angleSpeed;
		star->sun.pos.x = barycenterPosition.x + star->radiusToBarycenter * Cos(star->angle);
		star->sun.pos.y = barycenterPosition.y;
		star->sun.pos.z = barycenterPosition.z + star->radiusToBarycenter * Sin(star->angle);
	}

	void StarsSystem::normalizeAndSetHeightLight(SunClass* sun) {
		sun->pos.normalize();
		sun->light_color = (1 - D.ambientColor()) * Sat(Cbrt(sun->pos.y));
	}

	void StarsSystem::setStarsRaysAndHeighlight() {
		setSunRaysAndHeighlight(&vigilantEye.sun);
		setSunRaysAndHeighlight(&allSeeingEye.sun);
	}

	void StarsSystem::setStarsPositions() {
		updateBarycenterPosition();
		setStarPosition(&vigilantEye);
		setStarPosition(&allSeeingEye);
	}

	void StarsSystem::updateBarycenterPosition() {
		auto angle = 0.001;

		phi += angle;
		barycenterPosition.x = Sin(theta) * Cos(phi);
		barycenterPosition.y = Sin(theta) * Sin(phi);
		barycenterPosition.z = Cos(theta);
	}

	void StarsSystem::normalizeStartsPositionsAndHeightLight() {
		normalizeAndSetHeightLight(&vigilantEye.sun);
		normalizeAndSetHeightLight(&allSeeingEye.sun);
	}

	void StarsSystem::update() {
		// because Esenthel Engine set position of Astro object only once
		// during adding it to Astro container, to implement movement of two suns
		// we pop them from container and add them each frame
		// it cost additional CPU, but not dramatically affect memory
		Astros.pop();
		Astros.pop();

		hour += 0.00001;
		if (hour >= HOURS_IN_DAY) {
			hour -= HOURS_IN_DAY;
		}

		setStarsPositions();
		normalizeStartsPositionsAndHeightLight();
		setStarsRaysAndHeighlight();

		Astros.add(vigilantEye.sun);
		Astros.add(allSeeingEye.sun);
	}
}