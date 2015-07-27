﻿#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Environment/StarsSystem.h>
#include <Headers/Core/DateTime.h>
#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Environment/SunHeightChangedEvent.h>

namespace pan {
	const Vec StarsSystem::MIDYEAR_MIDDAY_RAYS_COLOUR = Vec(192.0, 186.0, 98.0);		
	
	StarsSystem::StarsSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &StarsSystem::updateMiddayRaysIntensity);
		EventManager::getInstance()->registerEventHandlerMethod(this, &StarsSystem::update);
		updateBarycenterOffset();
		NewDayEvent event(DateTime::getInstance()->getDayInYear());
		updateMiddayRaysIntensity(&event);
		auto time = DateTime::getInstance()->getFloatTime();
		setBarycenterPosition(time);

		createVigilantEye();
		createAllSeeingEye();	
		
		Astros.add(allSeeingEyeSun);
	}

	void StarsSystem::setBarycenterPosition(Flt time) {
		// TODO get this value from something like WorldManager
		auto sunriseTime = util::getSunriseTime(util::WORLD_LATITUDE);
		phi = DegToRad(calculateHourAngle(time) - calculateHourAngle(sunriseTime)) + Asin(barycenterOffset);
		theta = DegToRad(90.0f);
		barycenterPosition.x = Sin(theta) * Cos(phi);
		barycenterPosition.y = Sin(theta) * Sin(phi);
		barycenterPosition.z = Cos(theta);
		barycenterPosition.y -= barycenterOffset;
	}

	void StarsSystem::createVigilantEye() {
		vigilantEyeParameters.radiusToBarycenter = 0;
		vigilantEyeParameters.angleSpeed = 0.00002;
		vigilantEyeParameters.angle = 0;
	}

	void StarsSystem::createAllSeeingEye() {
		allSeeingEyeSun.image = UID(2922889087, 1171051764, 3010789764, 3570309810); // Images/sun
		allSeeingEyeSun.size = 0.005;
		Vec lightColour(255, 160, 64);
		lightColour /= 255;
		Vec imageColour(255, 120, 120);
		allSeeingEyeSun.light_color = lightColour;
		allSeeingEyeSun.image_color.set(imageColour.x, imageColour.y, imageColour.z);
		allSeeingEyeSun.glow = 255;

		allSeeingEyeParameters.radiusToBarycenter = -0.08;		
		allSeeingEyeParameters.angleSpeed = 0.00002;
		allSeeingEyeParameters.angle = 0;
	}

	Vec StarsSystem::getUpdatedStarPosition(StarParameters* star) {
		star->angle += star->angleSpeed;
		if (star->angle >= PI2) {
			star->angle -= PI2;
		}

		Vec updatedStarPosition;
		updatedStarPosition.x = barycenterPosition.x + star->radiusToBarycenter * Cos(star->angle);
		updatedStarPosition.y = barycenterPosition.y;
		updatedStarPosition.z = barycenterPosition.z + star->radiusToBarycenter * Sin(star->angle);

		return updatedStarPosition;
	}

	void StarsSystem::normalizeStarsPositions() {
		allSeeingEyeSun.pos.normalize();
		Sun.pos.normalize();
	}

	void StarsSystem::setStarsPositions() {
		updateBarycenterPosition();
		allSeeingEyeSun.pos = getUpdatedStarPosition(&allSeeingEyeParameters);
		Sun.pos = getUpdatedStarPosition(&vigilantEyeParameters);		
	}

	void StarsSystem::updateVigilantEyeRaysColour() {
		auto barycenterYPositionRatio = Abs(barycenterPosition.y / middayBarycenterPosition);

		// this is CDF (cumulative distribution function) of exponential distribution
		barycenterYPositionRatio = 1 - exp(-brightnessCoefficient * barycenterYPositionRatio);
		if (barycenterYPositionRatio >= 1.0) {
			barycenterYPositionRatio = 1.0;
		}		
		Sun.rays_color = middayRaysColour * barycenterYPositionRatio / 255;
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

	void StarsSystem::update(const UpdateEvent* eventToProceed) {
		// because Esenthel Engine set position of Astro object only once
		// during adding it to Astro container, to implement movement of two suns
		// we pop them from container and add them each frame
		// it cost additional CPU, but not dramatically affect memory
		Astros.pop();		

		setStarsPositions();
		normalizeStarsPositions();
		updateVigilantEyeRaysColour();
		
		Astros.add(allSeeingEyeSun);
	}

	void StarsSystem::updateMiddayRaysIntensity(const NewDayEvent* eventToProceed) {
		auto dayInYear = eventToProceed->getNewDayNumberInYear();
		/*
		Originaly we have [0; DAYS_IN_YEAR] interval
		At DAYS_IN_YEAR / 2 day sun rays intensity equal MIDYEAR_MIDDAY_RAYS_COLOUR
		At 0 day and DAYS_IN_YEAR day sun rays intensity equal (3 * MIDYEAR_MIDDAY_RAYS_COLOUR / 4)
		So before we calculate rays intensity in current day, we divide interval by half
		making it [0; DAYS_IN_YEAR / 2] and translate current day to this interval
		*/
		if (dayInYear > DAYS_IN_YEAR / 2) {
			dayInYear -= (dayInYear - DAYS_IN_YEAR / 2) * 2;
		}

		/*
		After interval dividing, assuming that rays intensity at DAYS_IN_YEAR / 2 day is "a"
		we have sun rays intensity at 0 day as "3a / 4"
		So common formula for rays intensity at any day in year is:
		I = 3a / 4 + day / (DAYS_IN_YEAR / 2) * (a - 3a / 4)
		*/
		middayRaysColour = 3 * MIDYEAR_MIDDAY_RAYS_COLOUR / 4 
			+ (static_cast<Flt>(dayInYear * 2) / DAYS_IN_YEAR) * (MIDYEAR_MIDDAY_RAYS_COLOUR - 3 * MIDYEAR_MIDDAY_RAYS_COLOUR / 4);
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
		if (barycenterOffset < 0) {
			middayBarycenterPosition = 1.0 + barycenterOffset;
		} else {
			middayBarycenterPosition = 1.0 - barycenterOffset;
		}
	}

	Flt StarsSystem::calculateHourAngle(Flt hour) const	{
		return hour / HOURS_IN_DAY * FULL_CIRCLE_ANGLE;
	}
}