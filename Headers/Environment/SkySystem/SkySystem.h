#ifndef __SKYSYSTEM_H__
#define __SKYSYSTEM_H__

#include <Headers/ToolClasses/IUpdatable.h>
#include <Headers/Environment/SkySystem/DayNightCircleSystem.h>
#include "CloudsSystem.h"

namespace pan {
	class SkySystem : public IUpdateable {
	public:
		SkySystem();
		~SkySystem();
		void setSunHeightOverHorizont(Flt heightOverHorizont);
		void update() override;

	private:
		Flt sunHeightOverHorizont;
		CloudsSystem cloudsSystem;
		DayNightCircleSystem dayNightCircleSystem;
	};
}

#endif
