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
		EventManager::getInstance()->registerEventHandlerMethod(this, &WeatherSystem::update);
		initializeWeatherTypes();
		defaultWeather = SUNNY;
		setDefaultWeather();
	}

	WeatherSystem::~WeatherSystem() {
	}

	void WeatherSystem::setWeather(WeatherType weatherType, UShort hoursDuration, UShort minutesDuratuion)	{
		time = CurrentDateTime::getInstance()->getDateTime();
		time.addHours(hoursDuration);
		time.addMinutes(minutesDuratuion);		

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
		time = DateTime::INFINITE_DATE;
	}

	void WeatherSystem::update(const UpdateEvent* event) {
		// check if this leads to copying (with using references, not pointers)
		// TODO check in other same places
		auto effect = weatherTypes.at(currentWeather);

		auto realTime = CurrentDateTime::getInstance()->getDateTime();
		if (realTime == time) {
			effect->destroy();
			setDefaultWeather();
		}

		WeatherTypeEvent weatherEvent(currentWeather);
		EventManager::getInstance()->fireEvent(&weatherEvent);
	}
}