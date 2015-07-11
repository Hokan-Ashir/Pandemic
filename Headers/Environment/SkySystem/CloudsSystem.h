#ifndef __CLOUDSSYSTEM_H__
#define __CLOUDSSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>

namespace pan {
	class CloudsSystem : public BaseEventHandler {
	public:
		explicit CloudsSystem(Int numberOfCloudsLayers = 3);
		void update(const UpdateEvent* event);
	private:
		Int numberOfCloudsLayers;		
	};
}

#endif
