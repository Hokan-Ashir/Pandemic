#ifndef __SKYCOLOURSYSTEM_H__
#define __SKYCOLOURSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Environment/SunHeightChangedEvent.h>

namespace pan {
	class SkyColourSystem : public BaseEventHandler {
	public:
		explicit SkyColourSystem();		
		void update(const SunHeightChangedEvent* event);

	private:
		/**
		 * Possible sun height over horizont (= 2 * R)
		 * Where R = 1 (see "pos" member comment in Astro.h in Esenthel Engine)
		 * Because sun circle can have offset \in [-1; 1] 
		 * (see StarsSystem::calculateBaryCenterOffset())
		 * real sun height in highest point is 1 + 1 = 2
		 * and in lowest point is -1 + (-1) = -2
		*/
		const UShort SUN_HEIGHT = 2;

		void initializeHorisonColourInterpolator();
		void initializeSkyColourInterpolator();

		/**
		 * Fills colour interpolator with gradient-like horizontal-oriented image
		 * (preferabaly 1px height)
		 */
		void fillInterpolatorWithImageData(Interpolator<Vec4>* interpolator, UID imageUID);
		void setSkyColour(Flt sunHeightOverHorizont);
		Interpolator<Vec4> horizonColors;
		Interpolator<Vec4> skyColors;
	};
}

#endif
