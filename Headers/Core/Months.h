#ifndef __MONTHS_H__
#define __MONTHS_H__

#include <map>

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Singleton.h>

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

	class Months final : public Singleton <Months> {
		SET_SINGLETON(Months)
	public:
		/**
		 * Gets number of days in month, based on its value in enum <p>
		 * In no month found in collection of maps, warning raised in log <p>
		 * And number of days in first month returned
		 *
		 * \param MonthsEnum month element of MonthEnum, which info extracted
		 * \return UShort number of days in month
		 */
		UShort getNumberOfDaysInMonth(MonthsEnum& month) const;

	protected:
		Months();
		~Months();

	private:
		struct MonthInfo {
			std::string monthName;			
			UShort numberOfDays;
		};

		/**
		 * Collection of months and their info
		 */
		std::map<MonthsEnum, MonthInfo> months;

		/**
		 * Gets month info, based on its value in enum <p>
		 * In no month found in collection of maps, warning raised in log <p>
		 * And month info of first month returned
		 *
		 * \param MonthsEnum month element of MonthEnum, which info extracted
		 * \return pan::Months::MonthInfo info about month
		 */
		MonthInfo getMonthInfo(MonthsEnum month) const;	
	};
}

#endif
