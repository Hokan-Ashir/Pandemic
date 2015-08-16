#ifndef __DATETIME_H_
#define __DATETIME_H_

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/Core/Months.h>

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

// temporary store planet axis tilt here
const Flt AXIS_TILT = 19.8;

// "December" solstice day
const UShort LATE_SOLSTICE_DAY = DAYS_IN_YEAR - (DAYS_IN_YEAR * AXIS_TILT / 1000);

// "June" solstice day
const UShort EARLY_SOLSTICE_DAY = DAYS_IN_YEAR / 2 - (DAYS_IN_YEAR * AXIS_TILT / 1000);

// "March" equinox day
const UShort EARLY_EQUINOX_DAY = EARLY_SOLSTICE_DAY - (LATE_SOLSTICE_DAY - EARLY_SOLSTICE_DAY) / 2;

// "September" equinox day
const UShort LATE_EQUINOX_DAY = EARLY_SOLSTICE_DAY + (LATE_SOLSTICE_DAY - EARLY_SOLSTICE_DAY) / 2;

/**
 * Number of days in moon month, time during which moon became "new" again
 */
const UShort DAYS_IN_MOON_MONTH = 30;

/**
 * Whole number of game astro objects (Moon + second sun)
 */
const UShort NUMBER_OF_ASTRO_OBJECTS = 2;

namespace pan {
	/**
	 * Structure, that represent in-game time in short comparative format 
	 */
	struct sDateTime {

		/**
		 * In-game hour
		 */
		UShort hour;

		/**
		 * In-game minute
		 */
		UShort minute;

		/**
		 * In-game day in year
		 */
		UShort dayInYear;

		/**
		 * In-game year
		 */
		UShort year;

		/**
		 * Compassion operator <p>
		 * Make compassion from smallest period of time to <p>
		 * biggest, cause if minute equality failed - no other <p>
		 * equality-checks will proceed <p>
		 *
		 * \param const sDateTime & date comparative object
		 * \return bool true, if objects are equal, false otherwise
		 */
		bool operator==(const sDateTime& date) {
			// 
			return minute == date.minute
				&& hour == date.hour
				&& dayInYear == date.dayInYear
				&& year == date.year;
		}

		/**
		 * This method for incrementing time: <p>
		 * Increment hour if minutes >= MINUTES_IN_HOUR and set minutes to 0 and so on
		 */
		void updateTime() {	
			if (minute >= MINUTES_IN_HOUR) {
				dayInYear++;
			}

			if (hour >= HOURS_IN_DAY) {				
				dayInYear++;				
			}

			if (dayInYear >= DAYS_IN_YEAR) {
				dayInYear = 0;
				year++;
			}
		}
	};

	/**
	 * Class that represents in-game time <p>
	 * Has getters and setters, and also is Singleton, so each class can have access
	 * to it and know current in-game time
	 */
	class DateTime final : public Singleton<DateTime> {
		SET_SINGLETON(DateTime)
	public:		
		/**
		 * \return Flt time in format "HOUR.MUNUTES_SECONDS"
		 */
		Flt getFloatTime() const;

		/**
		 * \return UShort current hours in current day
		 */
		UShort getHours() const;

		/**
		 * \return UShort current minutes in current hour
		 */
		UShort getMinutes() const;

		/**
		 * \return UShort current seconds in current minute
		 */
		UShort getSeconds() const;

		/**
		 * \return sDateTime time in sDateTime format
		 */
		sDateTime getDateTime() const;

		/**
		 * \return UShort number of day in current year
		 */
		UShort getDayInYear() const;
		
		void update();
		
		void setTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year);
		
	protected:
		DateTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year);
		DateTime();
		~DateTime();

	private:
		/**
		* Time that passes each frame in game
		* 0.015 approximately equal 1 seconds in real life
		*/
		const Flt SECOND_TICK = 0.015 * 2500;

		/**
		 * Updates time, checking new in-game day is coming <p>
		 * Nullify minutes, hours if their values overflow limits
		 */
		void updateTime();

		/**
		 * Updates time, checking new in-game month is coming <p>
		 * Nullify dayInMonths value if its value overflow limit
		 */
		void updateMonth();

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
		* In-game current day in current year
		*/
		UShort dayInYear;

		/**
		* In-game day in current month
		*/
		UShort dayInMonth;

		/**
		* In-game current month
		*/
		MonthsEnum month;

		/**
		* In-game day current year
		*/
		UShort year;
	};
}

#endif
