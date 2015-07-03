#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Environment/SkySystem/WeatherSystem.h>
#include <Headers/Environment/SkySystem/WeatherEffects/AbstractWeatherEffect.h>
#include <Headers/Environment/SkySystem/WeatherEffects/SunnyEffect.h>
#include <Headers/Environment/SkySystem/WeatherEffects/RainEffect.h>

namespace pan {
	void WeatherSystem::initializeWeatherTypes() {
		weatherTypes.insert(std::make_pair(SUNNY, new SunnyEffect()));
		weatherTypes.insert(std::make_pair(RAIN, new RainEffect()));
	}

	WeatherSystem::WeatherSystem() {
		initializeWeatherTypes();
		defaultWeather = SUNNY;
		setDefaultWeather();		
	}

	WeatherSystem::~WeatherSystem() {
	}

	void WeatherSystem::setSunHeightOverHorizont(Flt heightOverHorizont) {
		this->sunHeightOverHorizont = heightOverHorizont;
	}

	void WeatherSystem::setWeather(WeatherType weatherType, UShort hoursDuration, UShort minutesDuratuion)	{
		time.year = DateTime::getInstance()->getYear();
		time.dayInYear = DateTime::getInstance()->getDayInYear();
		time.hour = DateTime::getInstance()->getHours() + hoursDuration;
		time.minute = DateTime::getInstance()->getMinutes() + minutesDuratuion;
		time.updateTime();

		// no need to recreate weather effect, if we set the same weather
		if (weatherType == currentWeather) {
			return;
		}

		auto currentEffect = weatherTypes.at(currentWeather);
		auto effect = weatherTypes.at(weatherType);
		if (!effect->isCreated()) {			
			effect->create(cloudsSystem, skyColourSystem);			
			currentEffect->destroy();
		}

		currentWeather = weatherType;
	}

	void WeatherSystem::setDefaultWeather()	{
		currentWeather = defaultWeather;
		auto effect = weatherTypes.at(currentWeather);
		effect->create(cloudsSystem, skyColourSystem);
		time.year = USHRT_MAX;
		time.dayInYear = USHRT_MAX;
		time.hour = USHRT_MAX;
		time.minute = USHRT_MAX;
	}

	void WeatherSystem::updateWeather()	{
		// check if this leads to copying (with using references, not pointers)
		// TODO check in other same places
		auto effect = weatherTypes.at(currentWeather);		

		auto realTime = DateTime::getInstance()->getDateTime();
		if (realTime == time) {
			effect->destroy();
			setDefaultWeather();
			effect = weatherTypes.at(defaultWeather);
		}

		effect->effect();
	}

	void WeatherSystem::update() {
		skyColourSystem.setSunHeightOverHorizont(sunHeightOverHorizont);
		skyColourSystem.update();

		cloudsSystem.update();		
		updateWeather();
	}
}