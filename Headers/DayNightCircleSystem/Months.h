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

	class Months : public Singleton <Months>, private virtual FinalClass {
		SET_SINGLETON(Months)
	public:
		struct Coordinates {
			float lattitude;
			float longtitude;
		};

		std::string getMonthName(MonthsEnum& month) const;
		unsigned short getMonthSunriseHour(MonthsEnum& month, Coordinates coordinates) const;
		unsigned short getMonthSunriseMinute(MonthsEnum& month, Coordinates coordinates) const;
		unsigned short getMonthSettingHour(MonthsEnum& month, Coordinates coordinates) const;
		unsigned short getMonthSettingMinute(MonthsEnum& month, Coordinates coordinates) const;
		unsigned short getNumberOfDaysInMonth(MonthsEnum& month) const;

	protected:
		Months();
		~Months();

	private:
		struct MonthInfo {
			std::string monthName;
			// sunrise and setting time
			// stored for 45 degrees north / 75 degrees west coordinates
			// to get sunrise/setting time modified by lattitide
			// and longtitude use getters
			unsigned short sunriseHour;
			unsigned short sunriseMinute;
			unsigned short settingHour;
			unsigned short settingMinute;
			unsigned short numberOfDays;
		};

		std::map<MonthsEnum, MonthInfo> months;

		MonthInfo getMonthInfo(MonthsEnum month) const;
		unsigned short convertSunriseHour(unsigned short sunriseHour, Coordinates coordinates) const;
		unsigned short convertSunriseMinute(unsigned short sunriseMinute, Coordinates coordinates) const;
		unsigned short convertSettingHour(unsigned short settingHour, Coordinates coordinates) const;
		unsigned short convertSettingMinute(unsigned short settingMinute, Coordinates coordinates) const;
	};
}

#endif
