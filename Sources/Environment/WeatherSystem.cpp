#include <Headers/Environment/WeatherSystem.h>

namespace pan {
	WeatherSystem::WeatherSystem() : currentWeather(SUNNY), defaultWeather(SUNNY) {
	}

	WeatherSystem::~WeatherSystem()	{
	}

	void WeatherSystem::setWeather(WeatherType& weatherType, UShort hoursDuration, UShort minutesDuration) {
		currentWeather = weatherType;
		// TODO set other parameters
	}

	void WeatherSystem::setDefaultWeather(WeatherType& weatherType)	{
		currentWeather = weatherType;
	}

	void WeatherSystem::update() {
		skySystem->update();
		// TODO add explicit call of DirectParticleEmitter's destructor every time
		// current weather effect ends

		/*auto sunHeightOverHorizont = starsSystem.getBarycenterHeightOverHorizont();
		dayNightSystem->setSunHeightOverHorizont(sunHeightOverHorizont);
		dayNightSystem->update();*/
	}
}