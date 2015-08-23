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
		void rotateMaskedMoonImage(const Flt worldLatitude);

		void subscribeToEvents();
		void createMoon();
		void updateMoonPosition();
		void setMoonPosition(Flt time);
		void createMaskedMoonImage(UShort dayInMoonMonth);

		// get moon's image rotation angle (IN DEGREES) based on current moon phase and world latitude		
		Flt getMoonImageAngle(Flt worldLatitude) const;

		// Image rotation tecniuqe, with aliasing (in three stages - see here http://datagenetics.com/blog/august32013/)
		Vec2 rotateVectorAroundOrigin(Int x, Int y, Int originX, Int originY, Flt radianAngle) const;

		/**
		 * See documentation to calculateBaryCenterOffset() method
		 */
		Flt barycenterOffset;

		/**
		 * Phi angle in spherical coordinate system <p>
		 * Mathematical case, where theta is angle in YZ-plane, NOT in XY-plane
		 */
		Flt phi;

		/**
		 * Sunset time for current world latitude
		 */
		Flt sunsetTime;

		Vec moonPosition;

		Image maskedMoonImage;
		Astro* moon;
	};	
}

#endif
