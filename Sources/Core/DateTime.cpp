#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/DateTime.h>

namespace pan {
	Flt DateTime::getTime() const {
		return time;
	}

	UShort DateTime::getHours() const {
		return static_cast<Short> (time / 60 / 60);
	}

	UShort DateTime::getMinutes() const {
		auto hours = getHours();
		return static_cast<UShort>((time - hours * 60 * 60) / 60);
	}

	UShort DateTime::getSeconds() const {
		auto hours = getHours();
		auto minutes = getMinutes();
		return static_cast<UShort>(time - hours * 60 * 60 - minutes * 60);
	}

	UShort DateTime::getDayInYear() const {
		return dayInYear;
	}

	UShort DateTime::getDayInMonth() const {
		return dayInMonth;
	}

	MonthsEnum DateTime::getMonth() const {
		return month;
	}

	UShort DateTime::getYear() const {
		return year;
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
			time -= HOURS_IN_DAY * 60 * 60;
			dayInYear++;
			dayInMonth++;
		}
	}

	void DateTime::updateMonth() {
		if (dayInMonth == Months::getInstance()->getNumberOfDaysInMonth(month)) {
			dayInMonth = 0;
			month++;
			if (month > NUMBER_OF_MONTHS) {
				month = WINTER_1;
			}
		}
	}

	void DateTime::updateYear()	{
		if (dayInYear == DAYS_IN_YEAR) {
			dayInYear = 0;
			year++;
		}
	}

	void DateTime::update() {
		time += SECOND_TICK;
		
		// check new day coming
		updateTime();

		// check new month coming
		updateMonth();

		// check new year coming
		updateYear();
	}

	DateTime::DateTime(Flt time, UShort dayInMonth, UShort dayInYear, MonthsEnum month, UShort year) {
		setTime(time, dayInMonth, dayInYear, month, year);
	}

	DateTime::DateTime() {
		setTime(0, 0, DAYS_IN_YEAR / 2, WINTER_1, START_YEAR);
	}

	DateTime::~DateTime() {
	}
}