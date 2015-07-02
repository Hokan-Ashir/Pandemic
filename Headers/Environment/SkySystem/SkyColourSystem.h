#ifndef __SKYCOLOURSYSTEM_H__
#define __SKYCOLOURSYSTEM_H__

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class SkyColourSystem : public IUpdateable {
	public:
		explicit SkyColourSystem();		
		void update() override;
		void setSunHeightOverHorizont(Flt sunHeightOverHorizont);

	private:
		/* 
		Possible sun height over horizont (= 2 * R)
		Where R = 1 (see "pos" member comment in Astro.h in Esenthel Engine)
		Because sun circle can have offset \in [-1; 1] 
		(see calculateBaryCenterOffset() method in StarsSystem.h)
		real sun height	in heighest point is 1 + 1 = 2
		and in lowest point is -1 + (-1) = -2
		*/
		const UShort SUN_HEIGHT = 2;

		Flt getHeightOverHorizont(Flt hour) const;
		void initializeHorisonColourInterpolator();
		void initializeSkyColourInterpolator();
		void setSkyColour(Flt sunHeightOverHorizont);
		Vec4 createColour(Byte r, Byte g, Byte b, Byte a = 255);
		Interpolator<Vec4> horizonColors;
		Interpolator<Vec4> skyColors;
		Flt sunHeightOverHorizont;
	};
}

#endif
