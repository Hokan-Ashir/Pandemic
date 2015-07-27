#ifndef __NEWYEAREVENT_H__
#define __NEWYEAREVENT_H__

#include <Engine/Headers/EsenthelEngine.h>
#include "EventSystem/EventManager.h"

namespace pan {
	class NewYearEvent : public Event {
	public:
		explicit NewYearEvent(UShort newYear) : newYear(newYear) {}

		UShort getNewYear() const {
			return newYear;
		}

	private:
		UShort newYear;
	};
}

#endif
