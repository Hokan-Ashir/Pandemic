#ifndef __WORLDCHANGINGEVENT_H__
#define __WORLDCHANGINGEVENT_H__

#include <Headers/Core/EventSystem/EventManager.h>
#include <Engine/Headers/EsenthelEngine.h>

namespace pan {
	// temporary store world latitude here
	const Flt WORLD_LATITUDE = 45;

	class WorldChangingEvent : public Event {
	public:
		WorldChangingEvent(UID worldUID, Flt worldLatitude, Int longitudeHourOffset)
			: worldUID(worldUID), worldLatitude(worldLatitude), longitudeHourOffset(longitudeHourOffset) {
		}

		UID getWorldUID() const {
			return worldUID;
		}

		Flt getWorldLatitude() const {
			return worldLatitude;
		}

		Int getLongitudeHourOffset() const {
			return longitudeHourOffset;
		}

	private:
		UID worldUID;
		Flt worldLatitude;

		// UTC-like time offset; UTC+0 is for longitude = 0
		Int longitudeHourOffset;
	};
}

#endif