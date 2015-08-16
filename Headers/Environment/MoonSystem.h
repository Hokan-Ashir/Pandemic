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
		void updateBarycenterOffset(const WorldChangingEvent* event);
		void updateSunsetTime(const WorldChangingEvent* event);

		void subscribeToEvents();
		void createMoon();
		void updateMoonPosition();
		void setMoonPosition(Flt time);
		void createMaskedMoonImage(const NewDayEvent* event);

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

		ImagePtr maskedMoonImage;
		Astro* moon;
	};	
}

#endif
