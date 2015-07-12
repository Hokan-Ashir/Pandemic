#ifndef __WEATHERTYPEEFFECT_H__
#define __WEATHERTYPEEFFECT_H__

#include <Headers/Environment/SkySystem/WeatherSystem.h>
#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	class WeatherTypeEvent : public Event {
	public:
		explicit WeatherTypeEvent(WeatherType weatherType) : weatherType(weatherType) {}

		WeatherType getWeatherType() const {
			return weatherType;
		}

	private:
		WeatherType weatherType;
	};	
}

#endif
