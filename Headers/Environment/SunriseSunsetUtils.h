#ifndef __SUNRISESUNSETUTILS_H__
#define __SUNRISESUNSETUTILS_H__

#include <Engine/Headers/EsenthelEngine.h>

/*
		Guide to sunrise/sunset time calculations
		via Guassian distibution functions (GDF)

This is documentation to calculations in this file of sunset/sunrise times
via approximation with GDF

On real Earth times of sunrise and sunset can be approximate via GDF, according to
statistics from this site
http://ptaff.ca/soleil/wizard/?lang=en_CA

But if we take pure GDF (with x \in [0; 5] and y \in [0; 1]) 
and scale it to x \in [0; days_in_year] and y \in [0; hours_in_day]
edges of distribution will be too flat
like:
_________________/\_______________

Thus, we take pure GDF, but pass "x" argument modified by coefficientX:
coefficientX = 5 / days_in_year
realX = x * coefficientX

where 5 is pure GDF x-range

And also modify result value ("y") by coefficientY:
coefficientY = hours_in_day / 2
realY = y * coefficientY

Then we calculate "sigma" (GDF-parameter) offsetted by latitude
And choose "mu" as middle of pure-GDF interval (= 5 / 2)

Also we add equator sunset/sunrise hour offsets and latitude based offsets

Thereby we get sunrise/sunset times
*/

namespace pan {
	namespace util {
		// temporary store world latitude here
		const Flt WORLD_LATITUDE = 0;

		// polar latitude in degreees
		const UShort POLAR_LATITUDE = 90;

		UShort getSunriseHour(Flt latitudeDegree);
		UShort getSunriseMinute(Flt latitudeDegree);
		UShort getSunsetHour(Flt latitudeDegree);
		UShort getSunsetMinute(Flt latitudeDegree);
		Flt getSunriseTime(Flt latitudeDegree);
		Flt getSunsetTime(Flt latitudeDegree);		
	}
}

#endif
