#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Environment/StarsSystem.h>
#include <Headers/Core/DateTime.h>
#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Environment/SunHeightChangedEvent.h>

namespace pan {
	const Vec StarsSystem::MIDYEAR_MIDDAY_RAYS_COLOUR = Vec(192.0, 186.0, 98.0);	
	const Vec StarsSystem::SUNRISE_RAYS_COLOUR = Vec(35.0, 35.0, 35.0) / 255;
	
	StarsSystem::StarsSystem() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &StarsSystem::updateNewDayIncoming);
		EventManager::getInstance()->registerEventHandlerMethod(this, &StarsSystem::update);
		// TODO subscribe to event like "NewWorldSetEvent"
		if (util::WORLD_LATITUDE < 0) {
			sunInclination = DegToRad(2 * util::POLAR_LATITUDE + util::WORLD_LATITUDE);
		} else {
			sunInclination = DegToRad(util::POLAR_LATITUDE - util::WORLD_LATITUDE);
		}
		updateBarycenterOffset();
		NewDayEvent event(DateTime::getInstance()->getDayInYear());
		updateNewDayIncoming(&event);
		updateBarycenterPosition();

		createVigilantEye();
		createAllSeeingEye();	
		
		Astros.add(allSeeingEyeSun);
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

	/**
	 * To simulate sunset/sunrise offsets during year, according to this
	 * http://notesfromnoosphere.blogspot.ca/2012/05/simple-geometry-of-sun-paths.html
	 *
	 * sun has negative offset during June solstice and positive offset during December solstice
	 * (sign of offset is taken from Z-axis orientation in Esenthel Engine).
	 *
	 * To calculate sun's offset correctly we must emulate this function
	 * Assuming number of days in year = 365
	 * -------- March equinox day (20th March) = 79
	 * -------- June solstice day (20th June) = 172
	 * -------- September equinox day (23th September) = 266
	 * -------- December solstice day (22th December) = 356
	 * -------- June's solstice offset = -0.4
	 * -------- December's solstice offset = 0.4
	 * sun's offset function will be look like:
	 *
	 *     |         |         |
	 * z <-|---------|---------|---------
	 *     |         |         |
	 *    356        79       172
	 *   (0,4)       266      (-0.4)
	 *               (0.0)
	 *
	 * offset for 0-day (0,36) will be calculated like this:
	 *
	 * offset_range = 0.4 - 0.0
	 * end_year_days = 365 - 356
	 * zero_day_offset = 0.4 - (offset_range / (end_year_days + 79)) * end_year_days
	 *
	 * offsets
	 *     |
	 * 0,4 |                       *
	 *     |                      * *
	 * 0,36| *                   *   *
	 *     |  *                 *
	 *     |   *               *
	 *     |    *             * 
	 *     |-----*-----------*---------------------------------- days
	 *     | 0   79   172  266   356 365
	 *     |       *       *
	 *     |        *     *
	 *     |         *   *
	 *     |          * *
	 * -0,4|           *
	 *     |
	 *
	 * 
	 * This function perfectly brokes to three intervals 
	 * - descending interval [0; 172]
	 * - ascending interval [172; 356]
	 * - descending interval [356; 365]
	 * which are calculated in this method
	 */
	Flt StarsSystem::getSunsetSunriseHorizontOffset(UShort dayInYear) {
		auto zeroDayOffset = lateSolsticeOffset - (lateSolsticeOffset / (DAYS_IN_YEAR - LATE_SOLSTICE_DAY + EARLY_EQUINOX_DAY)) 
			* (DAYS_IN_YEAR - LATE_SOLSTICE_DAY);

		Flt resultOffset = 0;
		if (dayInYear >= 0 && dayInYear < EARLY_SOLSTICE_DAY) {
			resultOffset = zeroDayOffset - ((Abs(earlySolsticeOffset) + zeroDayOffset) / EARLY_SOLSTICE_DAY) * dayInYear;
		} else if (dayInYear >= EARLY_SOLSTICE_DAY && dayInYear < LATE_SOLSTICE_DAY) {
			resultOffset = earlySolsticeOffset
				+ ((Abs(earlySolsticeOffset) + zeroDayOffset) / (LATE_SOLSTICE_DAY - EARLY_SOLSTICE_DAY)) * (dayInYear - EARLY_SOLSTICE_DAY);
		} else if (dayInYear >= LATE_SOLSTICE_DAY && dayInYear <= DAYS_IN_YEAR) {
			resultOffset = lateSolsticeOffset
				- ((lateSolsticeOffset - zeroDayOffset) / (DAYS_IN_YEAR - LATE_SOLSTICE_DAY)) * (dayInYear - LATE_SOLSTICE_DAY);
		}

		return resultOffset;
	}

	void StarsSystem::setBarycenterPosition(Flt time) {
		// TODO get this value from something like WorldManager
		auto sunriseTime = util::getSunriseTime(util::WORLD_LATITUDE);
		phi = DegToRad(calculateHourAngle(time) - calculateHourAngle(sunriseTime)) + Asin(barycenterOffset);
		theta = DegToRad(90.0f);
		barycenterPosition.x = Cos(phi);
		barycenterPosition.y = Sin(sunInclination) * Sin(phi);
		barycenterPosition.z = Sin(phi) * Cos(sunInclination) + sunHorizonOffset;
		barycenterPosition.y -= barycenterOffset;
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

	/**
	 * Updates main sun's rays colour in 3 stages:
	 * 1. From dusk till dawn (night): barycenterPosition.y \in [-barycenterOffset; -1] 
	 *		(1 is celestial sphere radius) see Astro.h comment to "pos" member
	 *
	 *		At this stage sun's rays are off: Vec(0, 0, 0), cause no sun is visible under terrain/water surface
	 *
	 * 2. From sunset till dusk and from dawn till sunrise (twilight): barycenterPosition.y \in [-barycenterOffset; 0]
	 *
	 *		At this stage sun's rays visible, but not bright, cause sun is still under terrain/water surface
	 *		And ray's brightness calculated as part of SUNRISE_RAYS_COLOUR value 
	 *		with 0 * SUNRISE_RAYS_COLOUR at barycenterPosition.y == -barycenterOffset (= dusk, dawn)
	 *		and SUNRISE_RAYS_COLOUR at barycenterPosition.y == 0 (= sunrise, sunset)
	 *
	 * 3. From sunrise till sunset (day): barycenterPosition.y \in [0; 1]
	 *		(1 is celestial sphere radius) see Astro.h comment to "pos" member
	 *
	 *		At this stage sun is visible and sun's rays begin to shine from SUNRISE_RAYS_COLOUR to their maximum
	 *		which defines by barycenter position relative to its midday position (which defines by day of year)
	 *		with SUNRISE_RAYS_COLOUR at barycenterPosition.y == 0 (= sunrise, sunset)
	 *		with X (calculated for different day differently, see code) at barycenterPosition.y == middayBarycenterPosition (= midday)
	 */
	void StarsSystem::updateVigilantEyeRaysColour() {		
		Flt twilightSunBorder = -barycenterOffset;		
		if (barycenterPosition.y < twilightSunBorder) {
			Sun.rays_color = Vec(0, 0, 0);
			return;
		}

		if (barycenterPosition.y < 0) {
			Sun.rays_color = (Abs(twilightSunBorder) - Abs(barycenterPosition.y)) / Abs(twilightSunBorder) * SUNRISE_RAYS_COLOUR;
			return;
		}

		auto barycenterYPositionRatio = barycenterPosition.y / middayBarycenterPosition;
		// this is CDF (cumulative distribution function) of exponential distribution
		barycenterYPositionRatio = 1 - exp(-brightnessCoefficient * barycenterYPositionRatio);
		if (barycenterYPositionRatio >= 1.0) {
			barycenterYPositionRatio = 1.0;
		}
		Sun.rays_color = middayRaysColour * barycenterYPositionRatio / 255 + SUNRISE_RAYS_COLOUR;
	}

	void StarsSystem::updateMiddayRaysIntensity(UShort dayInYear) {
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

	void StarsSystem::updateNewDayIncoming(const NewDayEvent* eventToProceed) {
		auto dayInYear = eventToProceed->getNewDayNumberInYear();		
		updateMiddayRaysIntensity(dayInYear);

		sunHorizonOffset = getSunsetSunriseHorizontOffset(dayInYear);
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
		// TODO subscribe to event like "NewWorldSetEvent"
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