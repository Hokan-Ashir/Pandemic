#ifndef __DAYNIGHTCIRCLESYSTEM_H__
#define __DAYNIGHTCIRCLESYSTEM_H__

#include <vector>

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Updatable.h>

class DayNightCircleSystem : public Updateable {
public:	
	DayNightCircleSystem();	
	void update() override;

private:
	void initializeHorisonColourInterpolator();
	void initializeSkyColourInterpolator();
	void setSkyColour(Flt hour);
	Vec4 createColour(Byte r, Byte g, Byte b, Byte a = 255);
	Interpolator<Vec4> horizonColors;
	Interpolator<Vec4> skyColors;
	Flt hour;
};

#endif
