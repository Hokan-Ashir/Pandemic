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
	 * is represented by extern Sun variable and lesser star (named allseeingEye) represented by Astro variable
	 * (and because of this allseeingEye can't shine), this is visually negated by placing starts near each other
	 */
	class StarsSystem : public BaseEventHandler {
	public:
		explicit StarsSystem();
		
		void update(const UpdateEvent* eventToProceed);				
		void updateNewDayIncoming(const NewDayEvent* eventToProceed);

		/**
		 * Updates barycenter offset, sun's inclination and sunrise time
		 */
		void updateCelestialSphereParameters(const WorldChangingEvent* event);		
		Flt getBarycenterHeightOverHorizont() const;

		~StarsSystem();

	private:
		struct StarParameters {
			Flt radiusToBarycenter;	
			Flt angleSpeed;
			Flt angle;
		};

		/**
		 * Coefficient of brightness calculation formula, that represent speed, with which
		 * brightness increase during forenoon and decrease during afternoon
		 *
		 * Mathematicaly this is "lambda" parameter of exponential distribution
		 */
		const Flt brightnessCoefficient = 2.5;
		
		void subscribeToEvents();

		void updateStarsParameters();
		void updateBarycenterPosition();
		void setStarsPositions();
		void updateVigilantEyeRaysColour();
		Vec getUpdatedStarPosition(StarParameters* star);

		void normalizeStarsPositions() const;
		
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
		Astro* allSeeingEyeSun;
		StarParameters allSeeingEyeParameters;
		StarParameters vigilantEyeParameters;
	};
}

#endif
