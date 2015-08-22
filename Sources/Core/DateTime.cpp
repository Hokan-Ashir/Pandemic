#include <Headers/Core/DateTime.h>
#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/NewMonthEvent.h>
#include <Headers/Core/NewYearEvent.h>
#include <Headers/Core/NewDayEvent.h>

namespace pan {
	const DateTime DateTime::INFINITE_DATE(USHRT_MAX * MINUTES_IN_HOUR * SECONDS_IN_MINUTE,
	                                                USHRT_MAX, USHRT_MAX, USHRT_MAX, AUTUMN_1, USHRT_MAX);

	DateTime::DateTime() {
		this->time = 0;
		this->dayInMonth = 0;
		this->dayInMoonMonth = 0;
		this->dayInYear = 0;
		this->month = WINTER_1;
		this->year = START_YEAR;
	}

	DateTime::DateTime(Flt time, UShort dayInMonth, UShort dayInMoonMonth, UShort dayInYear, MonthsEnum month, UShort year) {
		this->time = time;
		this->dayInMonth = dayInMonth;
		this->dayInMoonMonth = dayInMoonMonth;
		this->dayInYear = dayInYear;
		this->month = month;
		this->year = year;
	}

	bool DateTime::operator ==(const DateTime& date) const {
		return time == date.getTime()
				&& dayInYear == date.getDayInYear()
				&& year == date.getYear();
	}

	DateTime& DateTime::operator+=(const DateTime& date) {
		time += date.getTime();
		dayInMoonMonth += date.getDayInMoonMonth();
		dayInYear += date.getDayInYear();
		year += date.getYear();
		updateValues();

		return *this;
	}

	Flt DateTime::getTime() const {
		return time;
	}

	Flt DateTime::getFloatTime() const {
		return time / (MINUTES_IN_HOUR * SECONDS_IN_MINUTE);
	}

	UShort DateTime::getHours() const {
		return static_cast<Short>(time / SECONDS_IN_MINUTE / MINUTES_IN_HOUR);
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

	UShort DateTime::getDayInMoonMonth() const {
		return dayInMoonMonth;
	}

	UShort DateTime::getYear() const {
		return year;
	}

	void DateTime::updateValues() {
		updateTime();
		updateMonth();
		updateMoonMonth();
		updateYear();
	}

	void DateTime::updateTime() {
		auto hour = getHours();
		if (hour != HOURS_IN_DAY) {
			return;
		}

		time -= HOURS_IN_DAY * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
		dayInYear++;
		dayInMonth++;

		NewDayEvent event(dayInYear);
		EventManager::getInstance()->fireEvent(&event);
	}

	void DateTime::updateMonth() {
		if (dayInMonth != Months::getInstance()->getNumberOfDaysInMonth(month)) {
			return;
		}

		dayInMonth = 0;
		month++;
		if (month > NUMBER_OF_MONTHS) {
			month = WINTER_1;
		}

		NewMonthEvent event(month);
		EventManager::getInstance()->fireEvent(&event);
	}

	void DateTime::updateMoonMonth() {
		if (dayInMoonMonth != DAYS_IN_MOON_MONTH) {
			return;
		}

		dayInMoonMonth = 0;
	}

	void DateTime::updateYear() {
		if (dayInYear != DAYS_IN_YEAR) {
			return;
		}

		dayInYear = 0;
		year++;

		NewYearEvent event(year);
		EventManager::getInstance()->fireEvent(&event);
	}

	UShort DateTime::getDayInYear() const {
		return dayInYear;
	}

	void DateTime::addTime(Flt time) {
		this->time += time;
		updateValues();
	}

	void DateTime::addHours(UShort hour) {
		this->time += hour * MINUTES_IN_HOUR * SECONDS_IN_MINUTE;
		updateValues();
	}

	void DateTime::addMinutes(UShort minute) {
		this->time = minute * SECONDS_IN_MINUTE;
		updateValues();
	}
}
