#ifndef __ASTROOBJECTUTILS_H__
#define __ASTROOBJECTUTILS_H__

namespace pan {
	namespace util {
		/**
		 * This method is used to draw barycenter (and so as stars) in such way
		 * that arc of barycenter-circle movement will suffice length of day on this latitude in this day of year
		 * i.e:
		 * Let we stand on equator (latitude = 0) and calculated sunrise/sunset times are 6h and 18h respectively
		 * We take sun sphere with radius 1 (see comment to "pos" field in Astro.h in Esenthel Engine headers)
		 * Thus angle of rising sun will be 0, and angle of setting sun will be 180
		 *
		 *			   ...
		 *  /					   \
		 * /						\
		 * r - - - - - - - - - - - - s - - - - horizon
		 * \						/
		 *  \					   /
		 *			   ...
		 *
		 * where "r" is position of rising sun, "s" - position of setting sun
		 *
		 * As we go to the North or to the South sunrise/sunset times changes
		 * i.e:
		 * Let we stand on 45N deg and calculated sunrise/sunset times are 8h and 16h respectively
		 * So position of the sun (relative to equator circle) in this hours will be:
		 *
		 *   /					  \
		 *  r					   s
		 * /						\
		 * | - - - - - - - - - - - -| - - - - horizon
		 * \						/
		 *  \					   /
		 *		 		...
		 * 
		 * BUT to manage fact that sun rise and set on line of horizon we adjust horizon line
		 * in a way that "r" and "s" positions will still be on horizon
		 *
		 * 	  /					  \
		 *   r - - - - - - - - - - s - - - - new horizon
		 *  /			| r`		\
		 * | - - - - - - - - - - - - | - - - - horizon
		 * \						/
		 *  \					   /
		 *
		 * And this method calculate offset of this modified horizon "r`"
		 * So, to get new real position of barycenter on 45N degree latitude,
		 * we subtract "r`" from barycenter Y-position
		 * Calculation formula taken from http://mathworld.wolfram.com/CircularSector.html
		 * in this link it is referenced as "h"
		 *
		 * \param Flt worldLatitude latitude of world in which barycenter offset will be calculated
		 * \return Flt calculated offset
		 */
		Flt calculateBaryCenterOffset(Flt worldLatitude);

		// calculate hour on circle
		Flt calculateHourAngle(Flt hour);
	}
}

#endif
