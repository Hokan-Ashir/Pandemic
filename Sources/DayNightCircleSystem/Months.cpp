#include <Headers/DayNightCircleSystem/Months.h>
#include <Headers/Logging/Logger.h>
#include <string>

namespace pan {
	std::string Months::getMonthName(MonthsEnum& month) const {
		return getMonthInfo(month).monthName;
	}	

	unsigned short Months::getNumberOfDaysInMonth(MonthsEnum& month) const {
		return getMonthInfo(month).numberOfDays;
	}

	Months::Months() {
		MonthInfo info;
		info.monthName = "Winter - 1";
		info.numberOfDays = 20;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_1, info));

		info.monthName = "Winter - 2";
		info.numberOfDays = 23;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_2, info));

		info.monthName = "Winter - 3";
		info.numberOfDays = 24;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_3, info));

		info.monthName = "Spring - 1";
		info.numberOfDays = 24;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SPRING_1, info));

		info.monthName = "Spring - 2";
		info.numberOfDays = 21;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SPRING_2, info));

		info.monthName = "Summer - 1";
		info.numberOfDays = 28;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SUMMER_1, info));

		info.monthName = "Autumn - 1";
		info.numberOfDays = 20;
		months.insert(std::pair<MonthsEnum, MonthInfo>(AUTUMN_1, info));
	}

	Months::~Months() {
	}

	Months::MonthInfo Months::getMonthInfo(MonthsEnum month) const {
		MonthInfo info;
		try {
			info = months.at(month);
		} catch (std::out_of_range e) {
			Logger::getInstance()->warning(std::string("No month with value '" + std::to_string(month) + "' exists").data());
			info = months.begin()->second;
		}

		return info;
	}
}