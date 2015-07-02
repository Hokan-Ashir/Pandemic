#ifndef __DATETIME_H_
#define __DATETIME_H_

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/Core/Months.h>
#include <Headers/ToolClasses/IUpdatable.h>

// the very first year, when game starts when player choose "New game"
const UShort START_YEAR = 426;
const UShort DAYS_IN_YEAR = 365;
const UShort HOURS_IN_DAY = 24;
const UShort MINUTES_IN_HOUR = 60;
const UShort SECONDS_IN_MINUTE = 60;
// assuming definition of second and minute in game the same as IRL
// assuming 1 second IRL = 1 second in game

const Flt SECOND_TICK = 0.015 * 2500;

namespace pan {
	struct sDateTime {
		UShort hour;
		UShort minute;
		UShort dayInYear;
		UShort year;

		bool operator==(const sDateTime& date) {
			// make comparasion from smallest period of time to 
			// biggest, cause if minute equality failed - no other
			// equality-checks will proceed
			return minute == date.minute
				&& hour == date.hour
				&& dayInYear == date.dayInYear
				&& year == date.year;
		}

		// this method for incrementing time:
		// increment hour if minutes >= MINUTES_IN_HOUR and set minutes to 0
		// and so on
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

	class DateTime : public Singleton<DateTime>, public IUpdateable, virtual FinalClass {
		SET_SINGLETON(DateTime)
	public:
		Flt getTime() const;
		// return time in format "HOUR.MUNUTES_SECONDS"
		Flt getFloatTime() const;
		UShort getHours() const;
		UShort getMinutes() const;
		UShort getSeconds() const;
		sDateTime getDateTime() const;

		UShort getDayInYear() const;
		UShort getDayInMonth() const;
		MonthsEnum getMonth() const;
		UShort getYear() const;
		virtual void update() override;
		void setTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year);
		
	protected:
		DateTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year);
		DateTime();
		~DateTime();

	private:
		void updateTime();
		void updateMonth();
		void updateYear();

		// integer part of this value is seconds
		Flt time;
		UShort dayInYear;
		UShort dayInMonth;
		MonthsEnum month;
		// = START_YEAR + number of years passed in game
		UShort year;
	};
}

#endif
