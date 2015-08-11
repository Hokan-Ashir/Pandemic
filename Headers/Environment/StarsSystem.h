#ifndef __STARSSYSTEM_H__
#define __STARTSSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>
#include <Headers/Core/NewDayEvent.h>
#include <Headers/WorldsManagment/WorldChangingEvent.h>

namespace pan {
	/**
	 * Star that create and control movement of binary in-game star system <p>
	 * Both stars moving around stars barycenter (center of star masses), <p>
	 * while barycenter moves circularly, imitating sunset/sunrise on surface
	 *
	 * IMPORTANT:
	 * Cause "rays_colour" parameter, which describes sun's brightness (and also colour of "God's rays")
	 * only takes effect on so called "Main Sun" (extern Sun variable from Sun.h), main star (named vigilantEye)
	 * is represented by extern Sun variable and lesser star (named allseeingEye) represented by SunClass variable
	 * (and because of this allseeingEye can't shine)
	 */
	class StarsSystem : public BaseEventHandler {
	public:
		explicit StarsSystem();
		void update(const UpdateEvent* eventToProceed);				
		void updateNewDayIncoming(const NewDayEvent* eventToProceed);
		void updateSunriseTime(const WorldChangingEvent* event);

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
		void updateBarycenterOffset(const WorldChangingEvent* event);

		void updateSunInclination(const WorldChangingEvent* event);


		Flt getBarycenterHeightOverHorizont() const;		

	private:
		struct StarParameters {
			Flt radiusToBarycenter;	
			Flt angleSpeed;
			Flt angle;
		};

		/**
		 * Angle of full circle (whole degrees, that sun (barycenter) passes through day)
		 */
		const UShort FULL_CIRCLE_ANGLE = 360;

		/**
		 * Coefficient of brightness calculation formula, that represent speed, with which
		 * brightness increase during forenoon and decrease during afternoon
		 *
		 * Mathematicaly this is "lambda" parameter of exponential distribution
		 */
		const Flt brightnessCoefficient = 2.5;

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
		
		void subscribeToEvents();

		// calculate hour on circle
		Flt calculateHourAngle(Flt hour) const;

		void updateBarycenterPosition();
		void setStarsPositions();
		void updateVigilantEyeRaysColour();
		Vec getUpdatedStarPosition(StarParameters* star);

		void normalizeStarsPositions();
		
		void createVigilantEye();
		void createAllSeeingEye();

		/**
		 * Set barycenter position based on time, <p>
		 * which is one of possible strategies to update its position <p>
		 * (see comment inside updateBarycenterPosition() method)
		 * 
		 * \todo add inclination movement, based on latitude
		 * \param Flt current in-game time in form HOUR.MINUTE_SECOND
		 */
		void setBarycenterPosition(Flt time);

		Flt getSunsetSunriseHorizontOffset(UShort dayInYear);		

		/**
		* Calculate midday rays intensity for current day, based on mid year midday rays intensity
		* (MIDYEAR_MIDDAY_RAYS_COLOUR class member)
		*/
		void updateMiddayRaysIntensity(UShort dayInYear);

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

		const Flt earlySolsticeOffset = -0.4;

		const Flt lateSolsticeOffset = 0.4;

		/**
		 * Sun's inclination for current latitude (in radians)
		 */
		Flt sunInclination;

		/**
		* Sun's horizont offset for current day
		*/
		Flt sunHorizonOffset;

		Vec barycenterPosition;

		/**
		 * See documentation to calculateBaryCenterOffset() method
		 */
		Flt barycenterOffset;

		/**
		 * Position of barycenter in midday, using to calculate brightness ratio of current sun's position
		 * see updateVigilantEyeRaysColour() method calculations
		 */
		Flt middayBarycenterPosition;

		/**
		 * Colour of main sun's rays in midday at (DAYS_IN_YEAR / 2) day (describe sun's brightness)
		 */
		const static Vec MIDYEAR_MIDDAY_RAYS_COLOUR;

		/**
		 * Colour of main sun's rays in midday at sunrise (when barycenter.y = 0)
		 */
		const static Vec SUNRISE_RAYS_COLOUR;
		
		/**
		 * Colour of main sun's rays in midday at CURRENT day (describe sun's brightness)
		 */
		Vec middayRaysColour;

		/**
		 * Sunrise time for current world latitude
		 */
		Flt sunriseTime;

		/**
		 * Second star (allSeeingEye), see comment to this class for more info
		 */
		SunClass allSeeingEyeSun;
		StarParameters allSeeingEyeParameters;
		StarParameters vigilantEyeParameters;
	};
}

#endif
