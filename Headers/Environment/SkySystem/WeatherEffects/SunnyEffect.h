#ifndef __SUNNYEFFECT_H__
#define __SUNNYEFFECT_H__

#include "AbstractWeatherEffect.h"

namespace pan {
	class SunnyEffect : public AbstractWeatherEffect {
	public:
		SunnyEffect();
		void createActions(CloudsSystem& cloudsSystem, SkyColourSystem& skyColourSystem) override;
		void effect() override;
		void destroyActions() override;		
	};

}
#endif
