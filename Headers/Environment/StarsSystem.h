#ifndef __STARSSYSTEM_H__
#define __STARTSSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>

namespace pan {
	/**
	 * Star that create and control movement of binary in-game star system <p>
	 * Both stars moving around stars barycenter (center of star masses), <p>
	 * while barycenter moves circularly, imitating sunset/sunrise on surface
	 */
	class StarsSystem : public BaseEventHandler {
	public:
		explicit StarsSystem();
		void update(const UpdateEvent* eventToProceed);
		Flt getBarycenterHeightOverHorizont() const;		

	private:
		struct Star {
			SunClass sun;
			Flt radiusToBarycenter;	
			Flt angleSpeed;
			Flt angle;
		};

		/**
		 * Angle of full circle (whole degrees, that sun (barycenter) passes through day)
		 */
		const UShort FULL_CIRCLE_ANGLE = 360;

		Flt calculateDayLength(Flt worldLatitude) const;
		Flt calculateNightLength(Flt worldLatitude) const;

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
		Flt calculateBaryCenterOffset(Flt worldLatitude) const;

		/**
		 * Update barycenter offset based on current world latitude (currently hardcoded) <p>
		 * This is made due to optimization - sunset/sunrise times wont change till player <p>
		 * exists in current world
		 *
		 * \todo later create something like WorldManager (which will be final Singleton)
		 * and access current world latitude via its methods;
		 * Other option is firing "change latitude" event from WorldManager, when it loads another world
		 * and StarsSystem will catch it; or it will be subscribed to this event via Observer-pattern
		 */
		void updateBarycenterOffset();

		// calculate hour on circle
		Flt calculateHourAngle(Flt hour) const;

		void setStarsRaysAndHeighlight();
		void setSunRaysAndHeighlight(SunClass* sun);

		void updateBarycenterPosition();
		void setStarsPositions();
		void setStarPosition(Star* star);

		void normalizeStartsPositionsAndHeightLight();
		void normalizeAndSetHeightLight(SunClass* sun);
		
		void createVigilantEye();
		void createAllSeeinggEye();

		/**
		 * Set barycenter position based on time, <p>
		 * which is one of possible strategies to update its position <p>
		 * (see comment inside updateBarycenterPosition() method)
		 * 
		 * \todo add inclination movement, based on latitude
		 * \param Flt current in-game time in form HOUR.MINUTE_SECOND
		 */
		void setBarycenterPosition(Flt time);

		/**
		 * Theta angle in spherical coordinate system <p>
		 * Mathematical case, where theta is angle in XY-plane, NOT in YZ-plane
		 */
		Flt theta;

		/**
		 * Phi angle in spherical coordinate system <p>
		 * Mathematical case, where theta is angle in YZ-plane, NOT in XY-plane
		 */
		Flt phi;
		Vec barycenterPosition;

		/**
		 * See documentation to calculateBaryCenterOffset() method
		 */
		Flt barycenterOffset;
	
		Star vigilantEye;
		Star allSeeingEye;
	};
}

#endif
