#ifndef __WEATHERSYSTEM_H__
#define __WEATHERSYSTEM_H__

#include <map>

#include <Headers/Environment/SkySystem/SkyColourSystem.h>
#include "CloudsSystem.h"
#include "WeatherEffects/AbstractWeatherEffect.h"
#include <Headers/Core/DateTime.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>

namespace pan {
	// TODO weather modificators like CLOUDY/NONCLOUDY, THUNDER/NONTHUNDER
	enum WeatherType {
		SUNNY = 0,
		RAIN,
		SNOW,
		HAIL,
		DUST_STORM,
		FOG,
		WINTER_STORM,
		NUMBER_OF_WEATHER_TYPES = WINTER_STORM + 1
	};
	
	class WeatherSystem : public BaseEventHandler {
	public:		
		WeatherSystem();
		~WeatherSystem();
		void setWeather(WeatherType weatherType, UShort hoursDuration, UShort minutesDuratuion);
		void setDefaultWeather();
		
		// TODO maybe add setter and getter to WeatherSystem position, if there will be necessarily
		// to create another rain not just in place where player stays
		void update(const UpdateEvent* event);

	private:
		void initializeWeatherTypes();

		/**
		 * Time till currentWeather will exists
		 */
		sDateTime time;
		WeatherType currentWeather;

		/**
		 * Type of weather, that begins any time another weather settled by setWeather() method ends
		 */
		WeatherType defaultWeather;
		std::map<WeatherType, AbstractWeatherEffect*> weatherTypes;

		CloudsSystem cloudsSystem;
		SkyColourSystem skyColourSystem;
	};
}

#endif
