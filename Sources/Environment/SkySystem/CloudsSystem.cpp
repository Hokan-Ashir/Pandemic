#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/Environment/SkySystem/CloudsSystem.h>

namespace pan {	
	CloudsSystem::CloudsSystem(Int numberOfCloudsLayers) : numberOfCloudsLayers(numberOfCloudsLayers) {		
		/*EventManager::getInstance()->registerEventHandlerMethod(this, &CloudsSystem::update);
		auto cloudsUid = UID(802163481, 1110152069, 2781769901, 3386316786); // Images/clouds
		Clouds.layered.set(numberOfCloudsLayers, cloudsUid);
		for (auto i = 0; i < numberOfCloudsLayers; ++i) {
			Clouds.layered.layer[i].velocity *= 4;
		}*/
	}

	void CloudsSystem::update(const UpdateEvent* event) {
		/*Clouds.layered.update();
		for (auto i = 0; i < numberOfCloudsLayers; ++i) {
			Clouds.layered.layer[i].color = ColorBrightness(Sky.atmosphericHorizonColor().v3().max() * (255.0 / 164));
		}*/
	}
}