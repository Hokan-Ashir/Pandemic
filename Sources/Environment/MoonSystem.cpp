#include <Headers/Environment/MoonSystem.h>
#include <Headers/Core/CurrentDateTime.h>
#include <Headers/Environment/SunriseSunsetUtils.h>
#include <Headers/Environment/AstroObjectsUtils.h>

namespace pan {

	MoonSystem::MoonSystem() {
		subscribeToEvents();
		createMoon();
	}

	MoonSystem::~MoonSystem() {
		Astros.removeData(moon);
	}

	void MoonSystem::subscribeToEvents() {
		EventManager::getInstance()->registerEventHandlerMethod(this, &MoonSystem::update);
		EventManager::getInstance()->registerEventHandlerMethod(this, &MoonSystem::updateCelestialSphereParameters);
		EventManager::getInstance()->registerEventHandlerMethod(this, &MoonSystem::updateMoonPhase);
	}

	void MoonSystem::createMoon() {
		// cause Esenthel Engine copy Astro object during
		// Astros.add() method call, we create Asrto object via Astros.New(),
		// then get pointer to it via Astros.addrLast()
		// BUT, cause Astros.New() method reallocate memory, if we first create
		// stars, store pointers to them, then create moon, pointers to stars will be invalid
		// so we allocate enough memory for all Astro-like objects
		if (Astros.elms() < NUMBER_OF_ASTRO_OBJECTS) {
			Astros.setNum(NUMBER_OF_ASTRO_OBJECTS);
		}

		ImagePtr originalImage = UID(751191074, 1273901359, 2472514488, 2970955246); // Images/Moon/triron		
		auto width = originalImage()->w();
		auto height = originalImage()->h();
		maskedMoonImage.create2D(width, height, IMAGE_R8G8B8A8, 1);
		originalImage = NULL;

		Astros.New();
		moon = Astros.addrLast();
		moon->image = &maskedMoonImage;
		moon->size = 0.05;
		moon->blend = true;
		moon->image_color.set(102, 102, 102, 255);
		moon->light_color = 0;
		moon->glow = 15;
	}

	void MoonSystem::update(const UpdateEvent* event) {
		updateMoonPosition();

		auto twilightSunBorder = -barycenterOffset;
		if (moonPosition.y < twilightSunBorder) {
			moon->draw = false;
		} else {
			moon->draw = true;
		}
	}

	void MoonSystem::updateMoonPosition() {
		auto time = CurrentDateTime::getInstance()->getFloatTime();
		setMoonPosition(time);
		moon->pos.normalize();
	}

	void MoonSystem::setMoonPosition(Flt time) {
		time += moonHourRisingOffset;
		if (time >= HOURS_IN_DAY) {
			time -= HOURS_IN_DAY;
		}

		phi = DegToRad(util::calculateHourAngle(time) - sunriseTimeHourAngle) + Asin(barycenterOffset);
		auto theta = DegToRad(90.0f);
		moonPosition.x = Sin(theta) * Cos(phi);
		moonPosition.y = Sin(theta) * Sin(phi);
		moonPosition.z = Cos(theta);
		moonPosition.y -= barycenterOffset;

		moon->pos = moonPosition;
	}

	void MoonSystem::updateCelestialSphereParameters(const WorldChangingEvent* event) {
		updateSunsetTime(event);
		updateBarycenterOffset(event);
		updateMoonPosition();
		createMaskedMoonImage(CurrentDateTime::getInstance()->getDayInMoonMonth(), event->getWorldLatitude());
	}

	void MoonSystem::updateSunsetTime(const WorldChangingEvent* event) {
		auto sunriseTime = util::getSunriseTime(event->getWorldLatitude());
		sunriseTimeHourAngle = util::calculateHourAngle(sunriseTime);
	}

	void MoonSystem::updateBarycenterOffset(const WorldChangingEvent* event) {
		barycenterOffset = util::calculateBaryCenterOffset(event->getWorldLatitude());
	}

	void MoonSystem::updateMoonPhase(const NewDayEvent* event) {
		// TODO replace world latitude to something like WorldManager::getInstance()->getCurrentWorld().getLatitude();
		createMaskedMoonImage(event->getNewDayInMoonMonth(), WORLD_LATITUDE);
		updateMoonHourRisingOffset(event->getNewDayInMoonMonth());
	}	

	void MoonSystem::createMaskedMoonImage(UShort dayInMoonMonth, Flt worldLatitude) {
		// TODO maybe somehow update moon's image, if it's already created, 
		// not recreate each in-game day, or while new world setting
		ImagePtr originalImage = UID(751191074, 1273901359, 2472514488, 2970955246); // Images/Moon/triron
		ImagePtr maskedImage = UID(359640653, 1193532235, 1492542109, 2304939175); // Images/Moon/moonMask
		auto width = originalImage()->w();
		auto height = originalImage()->h();
		auto centerX = width / 2;
		auto centerY = height / 2;
		auto angle = DegToRad(getMoonImageAngle(worldLatitude));
		
		originalImage()->lockRead();
		maskedImage()->lockRead();
		maskedMoonImage.lock(LOCK_WRITE);
		auto dayOfMoonMonth = static_cast<Flt>(dayInMoonMonth);
		auto moonIntensity = dayOfMoonMonth / (DAYS_IN_MOON_MONTH / 2);
		if (dayOfMoonMonth > DAYS_IN_MOON_MONTH / 2) {
			moonIntensity = 1 - (moonIntensity - 1);
		} else {
			moonIntensity = 1 - moonIntensity;
		}

		// TODO improve performance, using non-copy creation rotation and SIMD operators
		for (auto x = 0; x < width; ++x) {
			for (auto y = 0; y < height; ++y) {
				// assuming maskImage member constraints are [0; 1]
				// also assuming that maskedImage is in RGB format - so each vector's component (x, y, z) are the same
				Flt alphaChanelValue;
				Vec4 maskedPixel = maskedImage()->color(x, y).asVec4();
				if (dayOfMoonMonth > DAYS_IN_MOON_MONTH / 2) {
					if (maskedPixel.x <= moonIntensity) {
						alphaChanelValue = 1.0;
					} else {
						alphaChanelValue = 0.0;
					}
				} else {
					if (maskedPixel.x >= moonIntensity) {
						alphaChanelValue = 1.0;
					} else {
						alphaChanelValue = 0.0;
					}
				}
				auto resultPixel = originalImage()->color(x, y).asVec4();
				if (resultPixel.w != 0) {
					resultPixel.w = alphaChanelValue;
				} /*else {
				    // TODO add here some sky colour/moon colour blending support
					resultPixel = Sky.atmosphericSkyColor();
				}*/
				auto rotated = rotateVectorAroundOrigin(x, y, centerX, centerY, angle);
				maskedMoonImage.colorF(rotated.x, rotated.y, resultPixel);
			}
		}

		originalImage()->unlock();
		maskedImage()->unlock();
		maskedMoonImage.unlock();

		originalImage = NULL;
		maskedImage = NULL;		
	}

	Flt MoonSystem::getMoonImageAngle(Flt worldLatitude) const {
		auto phaseAngle = FULL_MOON_MONTH_PHASE_ANGLE / DAYS_IN_MOON_MONTH * CurrentDateTime::getInstance()->getDayInMoonMonth();
		auto latitudeAngle = util::POLAR_LATITUDE - worldLatitude;

		return FULL_MOON_MONTH_PHASE_ANGLE - (phaseAngle + latitudeAngle);
	}

	Vec2 MoonSystem::rotateVectorAroundOrigin(Int x, Int y, Int originX, Int originY, Flt radianAngle) const {
		// move image rotation center (here it is image's center) to (0, 0) origin
		// NOTE: It is important to perform calculations on Int values, otherwise aliasing rotation will be lost
		auto x2 = x - originX;
		auto y2 = y - originY;

		// horizontal shear
		x2 = x2 - Tan(radianAngle / 2) * y2;
		y2 = y2;

		// vertical scale
		x2 = x2;
		y2 = x2 * Sin(radianAngle) + y2;

		// vertical shear
		x2 = x2 - Tan(radianAngle / 2) * y2;
		y2 = y2;

		// move image back to rotation center (here it is image's center)
		x2 += originX;
		y2 += originY;

		return Vec2(x2, y2);
	}

	void MoonSystem::updateMoonHourRisingOffset(UShort dayInMoonMonth) {
		moonHourRisingOffset = (dayInMoonMonth * HOURS_IN_DAY) / DAYS_IN_MOON_MONTH;
	}
}
