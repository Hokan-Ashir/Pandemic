#ifndef __WORLDCHANGINGEVENT_H__
#define __WORLDCHANGINGEVENT_H__

#include <Headers/Core/EventSystem/EventManager.h>
#include <Engine/Headers/EsenthelEngine.h>

namespace pan {
	// temporary store world latitude here
	const Flt WORLD_LATITUDE = 45;

	class WorldChangingEvent : public Event {
	public:
		WorldChangingEvent(UID worldUID, Flt worldLatitude) : worldUID(worldUID), worldLatitude(worldLatitude) {}

		UID getWorldUID() const {
			return worldUID;
		}

		Flt getWorldLatitude() const {
			return worldLatitude;
		}

	private:
		UID worldUID;
		Flt worldLatitude;
	};
}

#endif