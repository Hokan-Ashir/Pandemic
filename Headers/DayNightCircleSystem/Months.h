#ifndef __MONTHS_H__
#define __MONTHS_H__

#include <map>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ToolClasses/FinalClass.h>

namespace pan {
	enum MonthsEnum {
		WINTER_1 = 0,
		WINTER_2,
		WINTER_3,
		SPRING_1,
		SPRING_2,
		SUMMER_1,
		AUTUMN_1,
		NUMBER_OF_MONTHS = AUTUMN_1 + 1
	};

	inline MonthsEnum& operator++(MonthsEnum& month, int) {
		auto i = static_cast<int>(month);
		month = static_cast<MonthsEnum>((i + 1) % NUMBER_OF_MONTHS);
		return month;
	}

	class Months : public Singleton <Months>, virtual FinalClass {
		SET_SINGLETON(Months)
	public:

		std::string getMonthName(MonthsEnum& month) const;		
		unsigned short getNumberOfDaysInMonth(MonthsEnum& month) const;

	protected:
		Months();
		~Months();

	private:
		struct MonthInfo {
			std::string monthName;			
			unsigned short numberOfDays;
		};

		std::map<MonthsEnum, MonthInfo> months;
		MonthInfo getMonthInfo(MonthsEnum month) const;	
	};
}

#endif
