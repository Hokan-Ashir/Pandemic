#ifndef __WHEATHERSYSTEM_H__
#define __WHEATHERSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/IUpdatable.h>
#include <Headers/DirectParticlesEmitter/DirectParticleEmitter.h>
#include <Headers/Environment/SkySystem/SkySystem.h>

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
		void setWeather(WeatherType& weatherType, UShort hoursDuration, UShort minutesDuratuion);
		void setDefaultWeather(WeatherType& weatherType);
		// TODO maybe add setter and getter to WeatherSystem position, if there will be necessarity
		// to create another rain not just in place where player stays
		void update() override;

	private:
		SkySystem* skySystem;		

		WeatherType currentWeather;

		// type of weather begins any time another weather setted by "setWeather()" ends
		WeatherType defaultWeather;
		DirectParticleEmitter* currentPrecipitation;
	};
}
#endif
