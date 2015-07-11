#ifndef __SUNHEIGHTCHANGEDEVENT_H__
#define __SUNHEIGHTCHANGEDEVENT_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	class SunHeightChangedEvent : public Event {
	public:
		SunHeightChangedEvent(Flt heightOverHorizont) {
			this->heightOverHorizont = heightOverHorizont;
		}

		Flt getHeightOverHorizont() const {
			return heightOverHorizont;
		}
	private:
		Flt heightOverHorizont;
	};
}

#endif