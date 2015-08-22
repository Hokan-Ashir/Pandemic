#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Environment/AstroObjectsUtils.h>
#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Core/CurrentDateTime.h>

namespace pan {
	namespace util {
		/**
		 * Angle of full circle (whole degrees, that sun (barycenter) passes through day)
		 */
		const UShort FULL_CIRCLE_ANGLE = 360;

		Flt calculateDayLength(Flt worldLatitude) {
			auto sunriseTime = getSunriseTime(worldLatitude);
			auto sunsetTime = getSunsetTime(worldLatitude);
			return fabs(sunsetTime - sunriseTime);
		}

		Flt calculateNightLength(Flt worldLatitude) {
			auto dayLength = calculateDayLength(worldLatitude);
			return static_cast<Flt>(HOURS_IN_DAY - dayLength);
		}

		Flt calculateBaryCenterOffset(Flt worldLatitude) {
			auto dayLength = calculateDayLength(worldLatitude);
			auto radiusAngle = calculateHourAngle(dayLength);
			// actual formula is "r = R * cos(...)", but R = 1
			// see Astro.h in Esenthel Engine / comment to "pos" field
			return Cos(DegToRad(radiusAngle / 2));
		}
		
		Flt calculateHourAngle(Flt hour) {
			return hour / HOURS_IN_DAY * FULL_CIRCLE_ANGLE;
		}
	}
}