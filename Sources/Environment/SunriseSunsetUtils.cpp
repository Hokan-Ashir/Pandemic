#include <cmath>

#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Core/CurrentDateTime.h>

namespace pan {
	namespace util {
		// sigma value for Guassian distribution formulae for equator latitude
		const Flt EQUATOR_SIGMA = 6;

		// sigma value for Guassian distribution formulae for polar (north of south) latitude
		// NOTE: technically it's possible to use 0.0 value for polar sigma,
		// but sunset/sunrise time approximation via Guassian distribution is not
		// accurate enough to give correct results with polar sigma = 0.0
		const Flt POLAR_SIGMA = 0.7;		

		// default sunrise hour on equator in 0 hour at first month
		const UShort EQUATOR_DEFAULT_SUNRISE_HOUR = 4;

		// default sunset hour on equator in 0 hour at first month
		const UShort EQUATOR_DEFAULT_SUNSET_HOUR = 18;

		// default Guassian distribution x-argument range
		const UShort GUASSIAN_X_RANGE = 5;

		// real (in terms of in-game year) Guassian distribution x-argument range
		const Flt X_RANGE = static_cast<Flt>(GUASSIAN_X_RANGE) / DAYS_IN_YEAR;

		// coefficient that adds to sunrise time each 10 latitude degrees above/under equator
		// this is used for more accurate real sunrise simulation with Guassian distribution function
		const Flt LATITUDE_SUNRISE_COEFFICIENT = 0.6;

		// coefficient that adds to sunset time each 10 latitude degrees above/under equator
		// this is used for more accurate real sunset simulation with Guassian distribution function
		const Flt LATITUDE_SUNSET_COEFFICIENT = -0.05;		

		UShort getSunriseHour(Flt latitureDegree) {
			// not necessary casting cause compiler will do it itself, but more understandible
			return static_cast<UShort>(getSunriseTime(latitureDegree));
		}

		UShort getSunriseMinute(Flt latitureDegree) {
			auto sunriseTime = getSunriseTime(latitureDegree);
			auto minuteSecondsPart = sunriseTime - static_cast<long>(sunriseTime);
			// unnecessary casting, cause compiler will do it itself, but more understandible
			return static_cast<UShort>(minuteSecondsPart * SECONDS_IN_MINUTE);
		}

		UShort getSunsetHour(Flt latitureDegree) {
			// unnecessary casting, cause compiler will do it itself, but more understandible
			return static_cast<UShort>(getSunsetTime(latitureDegree));
		}

		UShort getSunsetMinute(Flt latitureDegree) {
			auto sunriseTime = getSunsetTime(latitureDegree);
			auto minuteSecondsPart = sunriseTime - static_cast<long>(sunriseTime);
			// unnecessary casting, cause compiler will do it itself, but more understandible
			return static_cast<UShort>(minuteSecondsPart * SECONDS_IN_MINUTE);
		}

		// get Guassian function value, based on argument, sigma and mu parameters
		Flt getGuassianFunctionValue(Flt x, Flt sigma, Flt mu) {
			auto sigmaSquare = sigma * sigma;
			return 1 / sqrt(2 * PI * sigmaSquare) * exp(-Pow(x - mu, 2) / (2 * sigmaSquare));
		}

		// get sigma value for Guassian distribution forulae, modified by latitude
		Flt getLatitideSigma(Flt latitudeDegree) {
			return static_cast<Flt>(EQUATOR_SIGMA - Abs(latitudeDegree) / POLAR_LATITUDE * (EQUATOR_SIGMA - POLAR_SIGMA));
		}

		Flt getSunriseTime(Flt latitudeDegree) {
			auto mu = static_cast<Flt>(GUASSIAN_X_RANGE) / 2;
			auto sigma = getLatitideSigma(latitudeDegree);
			auto latitudeTime = getGuassianFunctionValue(CurrentDateTime::getInstance()->getDayInYear() * X_RANGE, sigma, mu) * HOURS_IN_DAY / 2;
			latitudeTime += EQUATOR_DEFAULT_SUNRISE_HOUR + LATITUDE_SUNRISE_COEFFICIENT * Abs(latitudeDegree) / 10;
			while (latitudeTime >= HOURS_IN_DAY) {
				latitudeTime -= HOURS_IN_DAY;
			}

			return latitudeTime;
		}		

		Flt getSunsetTime(Flt latitudeDegree) {
			auto mu = static_cast<Flt>(GUASSIAN_X_RANGE) / 2;
			auto sigma = getLatitideSigma(latitudeDegree);
			auto latitudeTime = -getGuassianFunctionValue(CurrentDateTime::getInstance()->getDayInYear() * X_RANGE, sigma, mu) * HOURS_IN_DAY / 2;
			latitudeTime += EQUATOR_DEFAULT_SUNSET_HOUR + LATITUDE_SUNSET_COEFFICIENT * Abs(latitudeDegree) / 10;
			while (latitudeTime >= HOURS_IN_DAY) {
				latitudeTime -= HOURS_IN_DAY;
			}

			return latitudeTime;
		}	
	}
}