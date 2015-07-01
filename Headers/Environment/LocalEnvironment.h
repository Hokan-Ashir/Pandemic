#ifndef __LOCALENVIRONMENT_H__
#define __LOCALENVIRONMENT_H__

#include <Headers/ToolClasses/IUpdatable.h>
#include "SkySystem/SkySystem.h"
#include "StarsSystem.h"

namespace pan {
	class LocalEnvironment : public IUpdateable {
	public:
		LocalEnvironment();
		~LocalEnvironment();
		void update() override;
	private:
		SkySystem skySystem;
		StarsSystem starsSystem;
	};
}

#endif
