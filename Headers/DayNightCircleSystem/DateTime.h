#ifndef __DATETIME_H_
#define __DATETIME_H_

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/DayNightCircleSystem/Months.h>
#include <Headers/ToolClasses/IUpdatable.h>

// the very first year, when game starts when player choose "New game"
const unsigned short START_YEAR = 426; 
const unsigned short DAYS_IN_YEAR = 365;
const unsigned short HOURS_IN_DAY = 24;
// assuming definition of second and minute in game the same as IRL
// assuming 1 second IRL = 1 second in game

const Flt SECOND_TICK = 0.015 * 2500;

namespace pan {
	class DateTime : public Singleton<DateTime>, public IUpdateable, virtual FinalClass {
		SET_SINGLETON(DateTime)
	public:
		Flt getTime() const;
		UShort getHours() const;
		UShort getMinutes() const;
		UShort getSeconds() const;

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
