#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Environment/StarsSystem.h>
#include <Headers/Core/DateTime.h>
#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Environment/SunHeightChangedEvent.h>

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

	void StarsSystem::setBarycenterPosition(Flt time) {
		auto sunriseTime = util::getSunriseTime(util::WORLD_LATITUDE);		
		phi = DegToRad(calculateHourAngle(time) - calculateHourAngle(sunriseTime)) + Asin(barycenterOffset);
		theta = DegToRad(90.0f);
		barycenterPosition.x = Sin(theta) * Cos(phi);
		barycenterPosition.y = Sin(theta) * Sin(phi);
		barycenterPosition.z = Cos(theta);				
		barycenterPosition.y -= barycenterOffset;
	}

	StarsSystem::StarsSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &StarsSystem::update);
		updateBarycenterOffset();
		auto time = DateTime::getInstance()->getFloatTime();
		setBarycenterPosition(time);

		createVigilantEye();
		createAllSeeinggEye();	
		
		Astros.add(vigilantEye.sun);
		Astros.add(allSeeingEye.sun);
	}

	void StarsSystem::setSunRaysAndHeighlight(SunClass* sun) {
		auto rays = Sqrt(sun->pos.y);
		sun->rays_color = Lerp(0.02f, 0.14f, rays);
		sun->highlight_front = Lerp(0.80f, 0.20f, rays);
	}

	void StarsSystem::setStarPosition(Star* star) {	
		star->angle += star->angleSpeed;
		if (star->angle >= PI2) {
			star->angle -= PI2;
		}

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
		/*
		Another possibility to set barycenter position based on angle speed, NOT on DateTime::time
		TODO check this method speed
		It may be faster, if so, we can use Strategy-pattern to use more effective method,
		if we're not manipulating DateTime::time

		auto angle = SECOND_TICK * PI2 / (SECONDS_IN_MINUTE * MINUTES_IN_HOUR * HOURS_IN_DAY);

		phi += angle;
		if (phi >= PI2)	{
			phi -= PI2;
		}

		barycenterPosition.x = Sin(theta) * Cos(phi);
		barycenterPosition.y = Sin(theta) * Sin(phi);
		barycenterPosition.z = Cos(theta);		
		barycenterPosition.y -= calculateBaryCenterOffset();
		*/	

		auto time = DateTime::getInstance()->getFloatTime();
		setBarycenterPosition(time);
		SunHeightChangedEvent event(getBarycenterHeightOverHorizont());
		EventManager::getInstance()->fireEvent(&event);
	}

	void StarsSystem::normalizeStartsPositionsAndHeightLight() {
		normalizeAndSetHeightLight(&vigilantEye.sun);
		normalizeAndSetHeightLight(&allSeeingEye.sun);
	}

	void StarsSystem::update(const UpdateEvent* eventToProceed) {
		// because Esenthel Engine set position of Astro object only once
		// during adding it to Astro container, to implement movement of two suns
		// we pop them from container and add them each frame
		// it cost additional CPU, but not dramatically affect memory
		Astros.pop();
		Astros.pop();

		setStarsPositions();
		normalizeStartsPositionsAndHeightLight();
		setStarsRaysAndHeighlight();	

		Astros.add(vigilantEye.sun);
		Astros.add(allSeeingEye.sun);
	}

	Flt StarsSystem::calculateDayLength(Flt worldLatitude) const {
		auto sunriseTime = util::getSunriseTime(worldLatitude);
		auto sunsetTime = util::getSunsetTime(worldLatitude);
		return fabs(sunsetTime - sunriseTime);
	}

	Flt StarsSystem::calculateNightLength(Flt worldLatitude) const {
		auto dayLength = calculateDayLength(worldLatitude);
		return static_cast<Flt>(HOURS_IN_DAY - dayLength);
	}

	Flt StarsSystem::calculateBaryCenterOffset(Flt worldLatitude) const {
		auto dayLength = calculateDayLength(worldLatitude);
		auto radiusAngle = calculateHourAngle(dayLength);
		// actual formula is "r = R * cos(...)", but R = 1
		// see Astro.h in Esenthel Engine / comment to "pos" field
		return Cos(DegToRad(radiusAngle / 2));		 
	}

	Flt StarsSystem::getBarycenterHeightOverHorizont() const {
		// actual formula is "h = R * sin(...) - r", but R = 1
		// see Astro.h in Esenthel Engine / comment to "pos" field
		return Sin(phi) - barycenterOffset;
	}

	void StarsSystem::updateBarycenterOffset() {		
		barycenterOffset = calculateBaryCenterOffset(util::WORLD_LATITUDE);
	}

	Flt StarsSystem::calculateHourAngle(Flt hour) const	{
		return hour / HOURS_IN_DAY * FULL_CIRCLE_ANGLE;
	}
}