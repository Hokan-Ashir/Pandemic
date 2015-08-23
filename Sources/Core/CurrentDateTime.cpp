#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/CurrentDateTime.h>

namespace pan {

	Flt CurrentDateTime::getFloatTime() const {		
		return dateTime.getFloatTime();
	}

	UShort CurrentDateTime::getHours() const {
		return dateTime.getHours();
	}

	UShort CurrentDateTime::getMinutes() const {		
		return dateTime.getMinutes();
	}

	UShort CurrentDateTime::getSeconds() const {		
		return dateTime.getSeconds();
	}

	DateTime CurrentDateTime::getDateTime() const	{
		return dateTime;
	}

	UShort CurrentDateTime::getDayInYear() const {
		return dateTime.getDayInYear();
	}

	UShort CurrentDateTime::getDayInMoonMonth() const {
		return dateTime.getDayInMoonMonth();
	}

	void CurrentDateTime::update() {
		// if you want to speed up in-game time, slow it down, or even stop
		// just change increment value of "time", or change SECOND_TICK constant
		if (Kb.b(KB_1)) {
			dateTime.addTime(SECOND_TICK);
		}
	}

	void CurrentDateTime::updateLongitudeHourOffset(const WorldChangingEvent* event) {
		dateTime.addHours(event->getLongitudeHourOffset());
	}

	CurrentDateTime::CurrentDateTime(DateTime dateTime) {
		this->dateTime = dateTime;
		EventManager::getInstance()->registerEventHandlerMethod(this, &CurrentDateTime::updateLongitudeHourOffset);
	}

	CurrentDateTime::CurrentDateTime() : CurrentDateTime(DateTime()) 
	{}

	CurrentDateTime::~CurrentDateTime() {
	}
}