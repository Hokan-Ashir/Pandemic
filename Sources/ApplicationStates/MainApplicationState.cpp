#include <string>

#include <Headers/Auto.h>
#include <Headers/ApplicationStates/MainApplicationState.h>
#include <Headers/ToolClasses/ProxyCall.h>
#include <Headers/ApplicationStates/StateManager.h>
#include <Headers/Core/EventSystem/EventManager.h>
#include <Headers/Core/EventSystem/Events/UpdateEvent.h>
#include <Headers/Core/EventSystem/Events/DrawEvent.h>
#include <Headers/Environment/SkySystem/WeatherSystem.h>
#include <Headers/Environment/StarsSystem.h>

namespace pan {
	MainApplicationState::MainApplicationState() {		
		StateManager::getInstance()->registerState(this);
		ProxyCall::setClass(this);
	}

	MainApplicationState::~MainApplicationState() {
	}

	void MainApplicationState::initializeEgine() {
		EE_INIT();
		App.flag = APP_MS_EXCLUSIVE;

		D.ambientPower(0.2f);
		D.mode(App.desktopW() * 0.75f, App.desktopH() * 0.8f);
		D.highPrecColRT(true);

		Cam.dist = 1;
		Cam.at.set(16, 4, 2);
	}

	Bool MainApplicationState::init() {
		Physics.create(EE_PHYSX_DLL_PATH);

		Game::World.activeRange(D.viewRange())
			.New(UID(793057521, 1165468649, 532672188, 1296740157)); // TestWorld
		if (Game::World.settings().environment) {
			Game::World.settings().environment->set();
		}
		
		std::shared_ptr<BaseEventHandler> starsSystem(new StarsSystem());
		addEventHandler(starsSystem);
		std::shared_ptr<BaseEventHandler> weatherSystem(new WeatherSystem());
		addEventHandler(weatherSystem);

		return true;
	}

	void MainApplicationState::draw() {		
		Renderer(ProxyCall::render);

		auto timeString = std::string("Hour " + std::to_string(DateTime::getInstance()->getHours())
			+ " Minutes: " + std::to_string(DateTime::getInstance()->getMinutes())
			+ " Seconds: " + std::to_string(DateTime::getInstance()->getSeconds()));
		D.text(0, 0.9, timeString.data());
	}

	Bool MainApplicationState::updateActions() {		
		if (Kb.bp(KB_ESC)) {
			return false;
		}

		Cam.transformByMouse(0.1f, 100, CAMH_ZOOM | (Ms.b(1) ? CAMH_MOVE : CAMH_ROT));
		Game::World.update(Cam.at);

		UpdateEvent event;
		EventManager::getInstance()->fireEvent(&event);

		return true;
	}

	void MainApplicationState::shutdown() {
	}

	void MainApplicationState::render() {
		Game::World.draw();

		switch (Renderer()) {
			case RM_BLEND:
			case RM_PALETTE:
			{
				DrawEvent event;
				EventManager::getInstance()->fireEvent(&event);
			}
			break;
		}
	}
}