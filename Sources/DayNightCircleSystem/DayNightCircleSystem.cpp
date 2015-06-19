#include <Headers/DayNightCircleSystem/DayNightCircleSystem.h>

void DayNightCircleSystem::initializeHorisonColourInterpolator()
{
	horizonColors.loop = true;
	horizonColors.min_x = 0;
	horizonColors.max_x = 24;

	horizonColors.add(0, createColour(30, 40, 56));
	horizonColors.add(4, createColour(54, 77, 108));
	horizonColors.add(6, createColour(97, 113, 136));
	horizonColors.add(8, createColour(110, 136, 152));
	horizonColors.add(12, createColour(121, 142, 164));
	horizonColors.add(15, createColour(121, 137, 154));
	horizonColors.add(20, createColour(130, 130, 110));
	horizonColors.add(21, createColour(111, 111, 105));
	horizonColors.add(22, createColour(72, 80, 101));
}

void DayNightCircleSystem::initializeSkyColourInterpolator()
{
	skyColors.loop = true;
	skyColors.min_x = 0;
	skyColors.max_x = 24;

	skyColors.add(0, createColour(12, 16, 23));
	skyColors.add(4, createColour(22, 29, 45));
	skyColors.add(6, createColour(61, 87, 124));
	skyColors.add(8, createColour(78, 107, 149));
	skyColors.add(12, createColour(70, 107, 161));
	skyColors.add(15, createColour(58, 95, 144));
	skyColors.add(20, createColour(59, 82, 126));
	skyColors.add(21, createColour(41, 57, 89));
	skyColors.add(22, createColour(26, 30, 41));	
}

DayNightCircleSystem::DayNightCircleSystem() {
	hour = 5;

	initializeHorisonColourInterpolator();
	initializeSkyColourInterpolator();
}

Vec4 DayNightCircleSystem::createColour(Byte r, Byte g, Byte b, Byte a) {
	return Vec4(r, g, b, a) / 255;
}

void DayNightCircleSystem::setSkyColour(Flt hour) {
	auto horizonColour = horizonColors(hour);
	auto skyColour = skyColors(hour);
	Sky.atmosphericColor(horizonColour, skyColour);
}

void DayNightCircleSystem::update() {
	hour += Time.d() * 2;
	setSkyColour(hour);
}