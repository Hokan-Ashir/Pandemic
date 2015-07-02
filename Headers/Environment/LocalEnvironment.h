#ifndef __LOCALENVIRONMENT_H__
#define __LOCALENVIRONMENT_H__

#include <Headers/ToolClasses/IUpdatable.h>
#include "StarsSystem.h"
#include "SkySystem/WeatherSystem.h"

namespace pan {
	class LocalEnvironment : public IUpdateable {
	public:
		LocalEnvironment();
		~LocalEnvironment();
		void update() override;
	private:
		WeatherSystem weatherSystem;
		StarsSystem starsSystem;
	};
}

#endif
