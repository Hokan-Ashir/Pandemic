#ifndef __WEATHERSYSTEM_H__
#define __WEATHERSYSTEM_H__

#include <map>

#include <Headers/ToolClasses/IUpdatable.h>
#include <Headers/Environment/SkySystem/SkyColourSystem.h>
#include "CloudsSystem.h"
#include "WeatherEffects/AbstractWeatherEffect.h"
#include <Headers/Core/DateTime.h>

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
	
	class WeatherSystem : public IUpdateable {
	public:		
		WeatherSystem();
		~WeatherSystem();
		void setSunHeightOverHorizont(Flt heightOverHorizont);
		void setWeather(WeatherType weatherType, UShort hoursDuration, UShort minutesDuratuion);
		void setDefaultWeather();
		
		// TODO maybe add setter and getter to WeatherSystem position, if there will be necessarity
		// to create another rain not just in place where player stays
		void update() override;

	private:
		void updateWeather();
		void initializeWeatherTypes();

		// time till currentWeather will exists
		sDateTime time;
		WeatherType currentWeather;
		// type of weather begins any time another weather setted by "setWeather()" ends
		WeatherType defaultWeather;
		// TODO maybe make this elements constant
		// maybe use similar solution for other maps
		std::map<WeatherType, AbstractWeatherEffect*> weatherTypes;

		Flt sunHeightOverHorizont;
		CloudsSystem cloudsSystem;
		SkyColourSystem skyColourSystem;
	};
}

#endif
