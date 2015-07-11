#ifndef __WEATHERTYPEEFFECT_H__
#define __WEATHERTYPEEFFECT_H__

#include <Headers/Environment/SkySystem/WeatherSystem.h>
#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	template<WeatherType N> class WeatherTypeEvent : public Event {
	};	
}

#endif
