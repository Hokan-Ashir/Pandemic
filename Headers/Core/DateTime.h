#ifndef __DATETIME_H_
#define __DATETIME_H_

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/Months.h>

namespace pan {

	/**
	 * The very first year, when game starts when player choose "New game"
	 */
	const UShort START_YEAR = 426;

	/**
	 * Number of days in in-game year
	 */
	const UShort DAYS_IN_YEAR = 365;

	/**
	 * Number of hours in in-game day
	 */
	const UShort HOURS_IN_DAY = 24;

	/**
	 * Number of minutes in in-game hour
	 */
	const UShort MINUTES_IN_HOUR = 60;

	/**
	 * Number of seconds in in-game minute
	 */
	const UShort SECONDS_IN_MINUTE = 60;

	/**
	 * Number of days in moon month, time during which moon became "new" again
	 */
	const UShort DAYS_IN_MOON_MONTH = 30;

	/**
	 * Class, that represent in-game time in comparative format
	 */
	class DateTime {

	public:
		DateTime();
		DateTime(Flt time, UShort dayInMonth, UShort dayInMoonMonth, UShort dayInYear, MonthsEnum month, UShort year);

		/**
		 * Compassion operator <p>
		 * Make compassion from smallest period of time to <p>
		 * biggest, cause if minute equality failed - no other <p>
		 * equality-checks will proceed <p>
		 *
		 * \param const sDateTime & date comparative object
		 * \return bool true, if objects are equal, false otherwise
		 */
		bool operator==(const DateTime& date) const;

		DateTime& operator+=(const DateTime& date);

		Flt getFloatTime() const;
		Flt getTime() const;
		UShort getHours() const;
		UShort getMinutes() const;
		UShort getSeconds() const;		
		UShort getDayInYear() const;
		UShort getDayInMoonMonth() const;
		UShort getYear() const;

		void addTime(Flt time);
		void addHours(UShort hour);
		void addMinutes(UShort minute);

		const static DateTime INFINITE_DATE;

	private:
		/**
		 * This method for incrementing time: <p>
		 * Increment hour if minutes >= MINUTES_IN_HOUR and set minutes to 0 and so on
		 */
		void updateValues();

		/**
		 * Updates time, checking new in-game day is coming <p>
		 * Nullify minutes, hours if their values overflow limits
		 */
		void updateTime();

		/**
		 * Updates time, checking new in-game month is coming <p>
		 * Nullify dayInMonth's value if its value overflow limit
		 */
		void updateMonth();

		/**
		* Updates time, checking new in-game moon month is coming <p>
		* Nullify dayInMoonMonth's value if its value overflow limit
		*/
		void updateMoonMonth();

		/**
		 * Updates time, checking new in-game year is coming <p>
		 * Nullify dayInYear value if its value overflow limit
		 */
		void updateYear();

		/**
		 * In-game time (microseconds/seconds/hours) <p>
		 * Integer part of this value is seconds
		 */
		Flt time;

		/**
		 * In-game day in year
		 */
		UShort dayInYear;

		/**
		 * In-game current month
		 */
		MonthsEnum month;

		/**
		 * In-game day in current month
		 */
		UShort dayInMonth;

		/**
		 * In-game day in moon month
		 */
		UShort dayInMoonMonth;

		/**
		 * In-game year
		 */
		UShort year;
	};
}

#endif
