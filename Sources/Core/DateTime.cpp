#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/DateTime.h>
#include <Headers/Core/NewDayEvent.h>
#include <Headers/Core/NewMonthEvent.h>
#include <Headers/Core/NewYearEvent.h>

namespace pan {

	Flt DateTime::getFloatTime() const {		
		return time / (MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	}

	UShort DateTime::getHours() const {
		return static_cast<Short> (time / SECONDS_IN_MINUTE / MINUTES_IN_HOUR);
	}

	UShort DateTime::getMinutes() const {
		auto hours = getHours();
		return static_cast<UShort>((time - hours * MINUTES_IN_HOUR * SECONDS_IN_MINUTE) / MINUTES_IN_HOUR);
	}

	UShort DateTime::getSeconds() const {
		auto hours = getHours();
		auto minutes = getMinutes();
		return static_cast<UShort>(time - hours * MINUTES_IN_HOUR * SECONDS_IN_MINUTE - minutes * SECONDS_IN_MINUTE);
	}

	sDateTime DateTime::getDateTime() const	{
		sDateTime time;
		time.hour = getHours();
		time.minute = getMinutes();
		time.dayInYear = dayInYear;
		time.year = year;

		return time;
	}

	UShort DateTime::getDayInYear() const {
		return dayInYear;
	}

	void DateTime::setTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year) {
		this->time = time;
		this->dayInMonth = dayInMonth;
		this->dayInYear = dayInYear;
		this->month = month;
		this->year = year;
	}

	void DateTime::updateTime()	{
		auto hour = getHours();
		if (hour == HOURS_IN_DAY) {
			time -= HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
			dayInYear++;
			dayInMonth++;

			NewDayEvent event(dayInYear);
			EventManager::getInstance()->fireEvent(&event);
		}
	}

	void DateTime::updateMonth() {
		if (dayInMonth == Months::getInstance()->getNumberOfDaysInMonth(month)) {
			dayInMonth = 0;
			month++;
			if (month > NUMBER_OF_MONTHS) {
				month = WINTER_1;
			}

			NewMonthEvent event(month);
			EventManager::getInstance()->fireEvent(&event);
		}
	}

	void DateTime::updateYear()	{
		if (dayInYear == DAYS_IN_YEAR) {
			dayInYear = 0;
			year++;

			NewYearEvent event(year);
			EventManager::getInstance()->fireEvent(&event);
		}
	}

	void DateTime::update() {
		// if you want to speed up in-game time, slow it down, or even stop
		// just change increment value of "time", or change SECOND_TICK constant
		time += SECOND_TICK;
		
		// check new day coming
		updateTime();

		// check new month coming
		updateMonth();

		// check new year coming
		updateYear();
	}

	void DateTime::updateLongitudeHourOffset(const WorldChangingEvent* event) {
		time += event->getLongitudeHourOffset() * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
	}

	DateTime::DateTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year) {
		setTime(time, dayInMonth, dayInYear, month, year);
		EventManager::getInstance()->registerEventHandlerMethod(this, &DateTime::updateLongitudeHourOffset);
	}

	DateTime::DateTime() : DateTime(0 * (SECONDS_IN_MINUTE * MINUTES_IN_HOUR) + 0 * SECONDS_IN_MINUTE, 0, DAYS_IN_YEAR / 2, WINTER_1, START_YEAR) 
	{}

	DateTime::~DateTime() {
	}
}