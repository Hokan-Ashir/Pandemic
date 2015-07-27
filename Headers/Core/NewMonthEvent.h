#ifndef __NEWMONTHEVENT_H__
#define __NEWMONTHEVENT_H__

#include "EventSystem/EventManager.h"
#include "Months.h"

namespace pan {
	class NewMonthEvent : public Event {		
	public:
		explicit NewMonthEvent(MonthsEnum newMonth) : newMonth(newMonth) {}

		MonthsEnum getNewMonth() const {
			return newMonth;
		}

	private:
		MonthsEnum newMonth;
	};
}

#endif
