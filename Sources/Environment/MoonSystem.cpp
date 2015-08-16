#include <Headers/Environment/MoonSystem.h>
#include <Headers/Core/DateTime.h>
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

		Astros.New();
		moon = Astros.addrLast();
		moon->image = UID(751191074, 1273901359, 2472514488, 2970955246); // Images/Moon/triron		
		moon->size = 0.05;
		moon->blend = false;
		moon->image_color.set(102, 102, 102, 255);
		moon->light_color = 0;
		moon->glow = 15;
	}

	void MoonSystem::update(const UpdateEvent* event) {
		updateMoonPosition();

		auto twilightSunBorder = barycenterOffset;
		if (moonPosition.y >= twilightSunBorder) {
			moon->draw = true;
		} else {
			moon->draw = false;
		}
	}

	void MoonSystem::updateMoonPosition() {
		auto time = DateTime::getInstance()->getFloatTime();
		setMoonPosition(time);
		moon->pos.normalize();
	}

	void MoonSystem::setMoonPosition(Flt time) {
		phi = DegToRad(util::calculateHourAngle(time) - util::calculateHourAngle(sunsetTime)) + Asin(barycenterOffset);
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
	}

	void MoonSystem::updateSunsetTime(const WorldChangingEvent* event) {
		sunsetTime = util::getSunsetTime(event->getWorldLatitude());
	}

	void MoonSystem::updateBarycenterOffset(const WorldChangingEvent* event) {
		barycenterOffset = -util::calculateBaryCenterOffset(event->getWorldLatitude());
	}

	void MoonSystem::updateMoonPhase(const NewDayEvent* event) {
		createMaskedMoonImage(event);
	}

	void MoonSystem::createMaskedMoonImage(const NewDayEvent* event) {
		// TODO crate phased moon image
	}
}
