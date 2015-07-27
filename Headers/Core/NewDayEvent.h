#ifndef __NEWDAYEVENT_H__
#define __NEWDAYEVENT_H__

#include <Engine/Headers/EsenthelEngine.h>
#include "EventSystem/EventManager.h"

namespace pan {
	class NewDayEvent : public Event {		
	public:
		explicit NewDayEvent(UShort newDayNumberInYear) : newDayNumberInYear(newDayNumberInYear) {}

		UShort getNewDayNumberInYear() const {
			return newDayNumberInYear;
		}

	private:
		UShort newDayNumberInYear;
	};
}

#endif
