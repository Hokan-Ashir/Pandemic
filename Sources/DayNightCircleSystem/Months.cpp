#include <Headers/DayNightCircleSystem/Months.h>
#include <Headers/Logging/Logger.h>
#include <string>

namespace pan {
	std::string Months::getMonthName(MonthsEnum& month) const {
		return getMonthInfo(month).monthName;
	}

	unsigned short Months::getMonthSunriseHour(MonthsEnum& month, Coordinates coordinates) const {
		auto info = getMonthInfo(month);
		return convertSunriseHour(info.sunriseHour, coordinates);
	}

	unsigned short Months::getMonthSunriseMinute(MonthsEnum& month, Coordinates coordinates) const {
		auto info = getMonthInfo(month);
		return convertSunriseMinute(info.sunriseMinute, coordinates);
	}

	unsigned short Months::getMonthSettingHour(MonthsEnum& month, Coordinates coordinates) const {
		auto info = getMonthInfo(month);
		return convertSettingHour(info.settingHour, coordinates);
	}

	unsigned short Months::getMonthSettingMinute(MonthsEnum& month, Coordinates coordinates) const {
		auto info = getMonthInfo(month);
		return convertSettingMinute(info.settingMinute, coordinates);
	}

	unsigned short Months::getNumberOfDaysInMonth(MonthsEnum& month) const {
		return getMonthInfo(month).numberOfDays;
	}

	Months::Months() {
		MonthInfo info;
		info.monthName = "Winter - 1";
		info.sunriseHour = 7;
		info.sunriseMinute = 20;
		info.settingHour = 4;
		info.settingMinute = 38;
		info.numberOfDays = 20;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_1, info));

		info.monthName = "Winter - 2";
		info.sunriseHour = 7;
		info.sunriseMinute = 40;
		info.settingHour = 4;
		info.settingMinute = 58;
		info.numberOfDays = 23;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_2, info));

		info.monthName = "Winter - 3";
		info.sunriseHour = 8;
		info.sunriseMinute = 00;
		info.settingHour = 5;
		info.settingMinute = 18;
		info.numberOfDays = 24;
		months.insert(std::pair<MonthsEnum, MonthInfo>(WINTER_3, info));

		info.monthName = "Spring - 1";
		info.sunriseHour = 8;
		info.sunriseMinute = 00;
		info.settingHour = 5;
		info.settingMinute = 18;
		info.numberOfDays = 24;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SPRING_1, info));

		info.monthName = "Spring - 2";
		info.sunriseHour = 8;
		info.sunriseMinute = 20;
		info.settingHour = 5;
		info.settingMinute = 38;
		info.numberOfDays = 21;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SPRING_2, info));

		info.monthName = "Summer - 1";
		info.sunriseHour = 8;
		info.sunriseMinute = 00;
		info.settingHour = 5;
		info.settingMinute = 18;
		info.numberOfDays = 28;
		months.insert(std::pair<MonthsEnum, MonthInfo>(SUMMER_1, info));

		info.monthName = "Autumn - 1";
		info.sunriseHour = 7;
		info.sunriseMinute = 40;
		info.settingHour = 4;
		info.settingMinute = 58;
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

	unsigned short Months::convertSunriseHour(unsigned short sunriseHour, Coordinates coordinates) const {
		// TODO do formula
		return sunriseHour;
	}

	unsigned short Months::convertSunriseMinute(unsigned short sunriseMinute, Coordinates coordinates) const {
		// TODO do formula
		return sunriseMinute;
	}

	unsigned short Months::convertSettingHour(unsigned short settingHour, Coordinates coordinates) const {
		// TODO do formula
		return settingHour;
	}

	unsigned short Months::convertSettingMinute(unsigned short settingMinute, Coordinates coordinates) const {
		// TODO do formula
		return settingMinute;
	}
}