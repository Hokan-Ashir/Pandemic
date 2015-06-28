#ifndef __SKYSYSTEM_H__
#define __SKYSYSTEM_H__

#include <Headers/ToolClasses/IUpdatable.h>
#include <Headers/DayNightCircleSystem/StarsSystem.h>
#include <Headers/DayNightCircleSystem/DayNightCircleSystem.h>

namespace pan {
	class SkySystem : public IUpdateable {
	public:
		SkySystem();
		~SkySystem();
		void update() override;

	private:
		StarsSystem starsSystem;
		DayNightCircleSystem dayNightCircleSystem;
	};
}

#endif
