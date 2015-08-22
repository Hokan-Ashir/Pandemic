#ifndef __CURRENTDATETIME_H_
#define __CURRENTDATETIME_H_

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/Core/DateTime.h>
#include <Headers/WorldsManagment/WorldChangingEvent.h>

/**
 * Whole number of game astro objects (Moon + second sun)
 */
const UShort NUMBER_OF_ASTRO_OBJECTS = 2;

namespace pan {	

	/**
	 * Class that represents and updates current in-game time <p>
	 * Has getters and setters, and also is Singleton, so each class can have access
	 * to it and know current in-game time
	 */
	class CurrentDateTime final : public Singleton<CurrentDateTime>, public BaseEventHandler {
		SET_SINGLETON(CurrentDateTime)
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
		DateTime getDateTime() const;

		/**
		 * \return UShort number of day in current year
		 */
		UShort getDayInYear() const;
		
		void update();

		void updateLongitudeHourOffset(const WorldChangingEvent* event);	
		
	protected:
		explicit CurrentDateTime(DateTime dateTime);
		CurrentDateTime();
		~CurrentDateTime();

	private:
		/**
		 * Time that passes each frame in game
		 * 0.015 approximately equal 1 seconds in real life
		 */
		const Flt SECOND_TICK = 0.015 * 2500;

		DateTime dateTime;		
	};
}

#endif
