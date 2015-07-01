#ifndef __CLOUDSSYSTEM_H__
#define __CLOUDSSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class CloudsSystem : public IUpdateable {
	public:
		explicit CloudsSystem(Int numberOfCloudsLayers = 3);
		~CloudsSystem();
		void update() override;
	private:
		Int numberOfCloudsLayers;		
	};
}

#endif
