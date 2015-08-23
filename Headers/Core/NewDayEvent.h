#ifndef __NEWDAYEVENT_H__
#define __NEWDAYEVENT_H__

#include <Engine/Headers/EsenthelEngine.h>
#include "EventSystem/EventManager.h"

namespace pan {
	class NewDayEvent : public Event {		
	public:
		explicit NewDayEvent(UShort newDayNumberInYear, UShort newDayInMoonMonth) 
			: newDayNumberInYear(newDayNumberInYear), newDayInMoonMonth(newDayInMoonMonth) {}

		UShort getNewDayNumberInYear() const {
			return newDayNumberInYear;
		}

		UShort getNewDayInMoonMonth() const {
			return newDayInMoonMonth;
		}

	private:
		UShort newDayNumberInYear;
		UShort newDayInMoonMonth;
	};
}

#endif
