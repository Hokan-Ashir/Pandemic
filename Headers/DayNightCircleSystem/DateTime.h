#ifndef __DATETIME_H_
#define __DATETIME_H_

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/DayNightCircleSystem/Months.h>
#include <Headers/ToolClasses/IUpdatable.h>

// the very first year, when game starts when player choose "New game"
const static unsigned short START_YEAR = 426; 
const static unsigned short DAYS_IN_YEAR = 320;
const static unsigned short HOURS_IN_DAY = 6;
// assuming definition of second and minute in game the same as IRL
// assuming 1 second IRL = 1 second in game
namespace pan {
	class DateTime : public Singleton<DateTime>, public IUpdateable, virtual FinalClass {
		SET_SINGLETON(DateTime)
	public:
		float getTime() const;
		unsigned short getDayInYear() const;
		unsigned short getDayInMonth() const;
		MonthsEnum getMonth() const;
		unsigned short getYear() const;
		virtual void update() override;
		void setTime(float time, unsigned short dayInMonth, unsigned short dayInYear, MonthsEnum month, int year);
		
	protected:
		DateTime(float time, unsigned short dayInMonth, unsigned short dayInYear, MonthsEnum month, int year);
		DateTime();
		~DateTime();

	private:
		void updateTime();
		void updateMonth();
		void updateYear();

		// integer part of this value is seconds
		float time;
		unsigned short dayInYear;
		unsigned short dayInMonth;
		MonthsEnum month;
		// = START_YEAR + number of years passed in game
		unsigned short year;
	};
}

#endif
