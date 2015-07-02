#include <Headers/Environment/SkySystem/WeatherEffects/AbstractWeatherEffect.h>

namespace pan {
	AbstractWeatherEffect::~AbstractWeatherEffect() {
	}

	bool AbstractWeatherEffect::isCreated()	{
		return created == true;
	}

	AbstractWeatherEffect::AbstractWeatherEffect() : created(false) {
	}

	void AbstractWeatherEffect::setIsCreated(bool created) {
		this->created = created;
	}
}