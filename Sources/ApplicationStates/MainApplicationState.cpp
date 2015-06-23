#include <Headers/Auto.h>

#include <Headers/ApplicationStates/MainApplicationState.h>
#include <Headers/ToolClasses/ProxyCall.h>
#include <Headers/ApplicationStates/StateManager.h>
#include <Headers/DirectParticlesEmitter/DirectParticleEmitter.h>
#include <Headers/DayNightCircleSystem/DayNightCircleSystem.h>
#include <Headers/DayNightCircleSystem/StarsSystem.h>
#include <string>

namespace pan {
	MainApplicationState::MainApplicationState() {
		setId("MainApplicationState");
		StateManager::getInstance()->registerState(getId(), this);
	}

	MainApplicationState::~MainApplicationState() {
	}

	void MainApplicationState::initializeEgine() {
		EE_INIT();
		App.flag = APP_MS_EXCLUSIVE;

		D.ambientPower(0.2f);
		D.mode(App.desktopW() * 0.75f, App.desktopH() * 0.8f);

		Cam.dist = 1;
		Cam.at.set(16, 4, 2);
	}

	void createAstroObjects() {
		AstrosDraw = true;
		for (float i = 0.5; i < 1; i += 0.1) {
			for (float j = 0.5; j < 1; j += 0.1) {
				for (float k = 0.5; k < 1; k += 0.1) {
					Astro& astro = Astros.New();			
					/*if (i < 0.3 && i > -0.3
						|| (j < 0.3 && j > -0.3)
						|| (k < 0.3 && k > -0.3)) {
						astro.image = UID(3002038440, 1119925754, 1297635470, 3138736218); // red
					} else if (i < 0.6 && i > -0.6
						|| (j < 0.6 && j > -0.6)
						|| (k < 0.6 && k > -0.6)) {
						astro.image = UID(1642411942, 1241835978, 685888395, 754744485); // blue
					} else {*/
						astro.image = UID(2920929257, 1140060994, 1579244686, 3365792635); // green
					//}
					astro.pos = Vec(i, j, k);
					astro.size *= 0.7;
					astro.blend = true;
					//astro.image_color.set(102, 102, 102, 136);
					//astro.light_color = 0;
					//astro.glow = 255;
				}
			}
			
		}
		
	}

	Bool MainApplicationState::init() {
		Physics.create(EE_PHYSX_DLL_PATH);

		Game::World.activeRange(D.viewRange())
			.New(UID(793057521, 1165468649, 532672188, 1296740157)); // TestWorld
		if (Game::World.settings().environment) {
			Game::World.settings().environment->set();
		}

		//std::shared_ptr<DirectParticleEmitter> emitter(new DirectParticleEmitter(UID(1305126526, 1249254078, 2971936397, 3966274079), Vec(0, 20, 0)));
		//addDrawableObject(emitter);
		//addUpdateableObject(emitter);

		Flt hour = 5;
		//std::shared_ptr<DayNightCircleSystem> dayNightSystem(new DayNightCircleSystem(hour));
		//addUpdateableObject(dayNightSystem);

		//createAstroObjects();
		std::shared_ptr<StarsSystem> starsSystem(new StarsSystem(hour));
		addUpdateableObject(starsSystem);

		return true;
	}

	void MainApplicationState::draw() {
		ProxyCall::setClass(this);
		Renderer(ProxyCall::render);
	}

	Bool MainApplicationState::update() {
		AbstractTimeableApplicationState::update();

		if (Kb.bp(KB_ESC)) {
			return false;
		}

		Cam.transformByMouse(0.1f, 100, CAMH_ZOOM | (Ms.b(1) ? CAMH_MOVE : CAMH_ROT));
		Game::World.update(Cam.at);

		for (auto updateable : updateableObjects) {
			updateable->update();
		}

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
				for (auto drawable : drawableObjects) {
					drawable->draw();
				}
			}
			break;
		}
	}

	std::string MainApplicationState::getId() const {
		return Identifirable::getId();
	}
}