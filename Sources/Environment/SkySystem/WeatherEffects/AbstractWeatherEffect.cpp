#include <Headers/Environment/SkySystem/WeatherEffects/AbstractWeatherEffect.h>

namespace pan {
	AbstractWeatherEffect::~AbstractWeatherEffect() {
	}

	void AbstractWeatherEffect::create(CloudsSystem& cloudSystem, SkyColourSystem& skyColourSystem)	{
		createActions(cloudSystem, skyColourSystem);
		created = true;
	}

	void AbstractWeatherEffect::destroy() {
		destroyActions();
		created = false;
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