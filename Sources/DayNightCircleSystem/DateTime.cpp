#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/DayNightCircleSystem/DateTime.h>

namespace pan {
	float DateTime::getTime() const {
		return time;
	}

	unsigned short DateTime::getDayInYear() const {
		return dayInYear;
	}

	unsigned short DateTime::getDayInMonth() const {
		return dayInMonth;
	}

	MonthsEnum DateTime::getMonth() const {
		return month;
	}

	unsigned short DateTime::getYear() const {
		return year;
	}

	void DateTime::setTime(float time, unsigned short dayInMonth, unsigned short dayInYear, MonthsEnum month, int year) {
		this->time = time;
		this->dayInMonth = dayInMonth;
		this->dayInYear = dayInYear;
		this->month = month;
		this->year = year;
	}

	void DateTime::updateTime()
	{
		unsigned short hour = static_cast<unsigned short>(time) / 60 / 60;
		if (hour == HOURS_IN_DAY) {
			time -= HOURS_IN_DAY * 60 * 60;
			dayInYear++;
			dayInMonth++;
		}
	}

	void DateTime::updateMonth()
	{
		if (dayInMonth == Months::getInstance()->getNumberOfDaysInMonth(month)) {
			dayInMonth = 0;
			month++;
			if (month > NUMBER_OF_MONTHS) {
				month = WINTER_1;
			}
		}
	}

	void DateTime::updateYear()
	{
		if (dayInYear == DAYS_IN_YEAR) {
			dayInYear = 0;
			year++;
		}
	}

	void DateTime::update() {
		time += Time.rd();
		
		// check new day coming
		updateTime();

		// check new month coming
		updateMonth();

		// check new year coming
		updateYear();
	}

	DateTime::DateTime(float time, unsigned short dayInMonth, unsigned short dayInYear, MonthsEnum month, int year) {
		setTime(time, dayInMonth, dayInYear, month, year);
	}

	DateTime::DateTime() {
		setTime(0, 0, 0, WINTER_1, START_YEAR);
	}

	DateTime::~DateTime() {
	}
}