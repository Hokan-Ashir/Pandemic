#ifndef __STARSSYSTEM_H__
#define __STARTSSYSTEM_H__

#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class StarsSystem : public IUpdateable {
	public:
		explicit StarsSystem(Flt hour);
		void update() override;

	private:
		struct Star {
			SunClass sun;
			Flt radiusToBarycenter;	
			Flt angleSpeed;
			Flt angle;
		};

		void setStarsRaysAndHeighlight();
		void setSunRaysAndHeighlight(SunClass* sun);

		void updateBarycenterPosition();
		void setStarsPositions();
		void setStarPosition(Star* star);

		void normalizeStartsPositionsAndHeightLight();
		void normalizeAndSetHeightLight(SunClass* sun);

		void initializeBarycenterSpherialAngles();
		void createVigilantEye();
		void createAllSeeinggEye();

		Flt theta;
		Flt phi;
		Vec barycenterPosition;

		Flt hour;		
		Star vigilantEye;
		Star allSeeingEye;
	};
}

#endif
