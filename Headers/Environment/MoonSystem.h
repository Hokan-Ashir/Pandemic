#ifndef __MOONSYSTEM_H__
#define __MOONSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>
#include <Headers/WorldsManagment/WorldChangingEvent.h>
#include <Headers/Core/NewDayEvent.h>

namespace pan {

	class MoonSystem : public BaseEventHandler {
	public:		
		MoonSystem();
		
		void update(const UpdateEvent* event);		
		void updateMoonPhase(const NewDayEvent* event);

		/**
		 * Updates barycenter offset and sunset time
		 */
		void updateCelestialSphereParameters(const WorldChangingEvent* event);

		~MoonSystem();
	private:
		/**
		 * Angle on which moon rotates each moon month - from one "New Moon" phase to another "New Moon" phase
		 */
		const Flt FULL_MOON_MONTH_PHASE_ANGLE = 360.0;

		void updateBarycenterOffset(const WorldChangingEvent* event);
		void updateSunsetTime(const WorldChangingEvent* event);

		void subscribeToEvents();
		void createMoon();
		void updateMoonPosition();
		void setMoonPosition(Flt time);
		void createMaskedMoonImage(UShort dayInMoonMonth, const Flt worldLatitude);
		void updateMoonHourRisingOffset(UShort dayInMoonMonth);

		/**
		 * Get moon's image rotation angle (IN DEGREES) based on current moon phase and world latitude
		 * This calculations based on real Earth moon phases, with little assumptions:
		 * - only latitdue matters, no longitude assists in calculations
		 * - no setting/rising moon angle differences - all moon's phase angles calculated for rising moon 
		 * (Earth moon's rising first quater as In-game moon's first quater, 
		 * Earth moon's rising full moon as In-game moon's full moon); as side effect - moon DOES NOT rotated during night
		 *
		 * Angle assumptions made using this link (http://notesfromnoosphere.blogspot.ca/2012/05/simple-geometry-of-sun-paths.html)
		 * via presented images and also using lunar calendar and Stellarium (http://www.stellarium.org/ru/)
		 *
		 * TODO it can be improved, using shader computations and andanced formulas, that take in longitude and rising/setting moon
		 * dependency. But this still can dramatically affect performance
		 */ 
		Flt getMoonImageAngle(Flt worldLatitude) const;

		// Image rotation tecniuqe, with aliasing (in three stages - see here http://datagenetics.com/blog/august32013/)
		Vec2 rotateVectorAroundOrigin(Int x, Int y, Int originX, Int originY, Flt radianAngle) const;

		/**
		 * See documentation to calculateBaryCenterOffset() method
		 */
		// TODO this variable usage can be improved, by storing additional computations (like Asin(...)) as class members
		Flt barycenterOffset;

		/**
		 * Phi angle in spherical coordinate system <p>
		 * Mathematical case, where theta is angle in YZ-plane, NOT in XY-plane
		 */
		Flt phi;

		/**
		 * Sunrise time "hour angle" for current world latitude
		 */
		Flt sunriseTimeHourAngle;

		/**
		 * Number of hours, that must pass after sunrise, till moon rise
		 *
		 * Difference between sunrise/sunset time and moonrise/moonset time for different phases:
		 * New Moon:				0h
		 * First Quarter:			+6h
		 * Full Moon:				+12h
		 * Last (third) Quarter:	+18h
		 *
		 * This calculations are based on average differences for New Dehli using those links:
		 * http://www.timeanddate.com/moon/india/new-delhi
		 * http://www.timeanddate.com/sun/india/new-delhi
		 */
		UShort moonHourRisingOffset;

		Vec moonPosition;

		Image maskedMoonImage;
		Astro* moon;
	};	
}

#endif
