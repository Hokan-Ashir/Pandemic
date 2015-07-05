#ifndef __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__
#define __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__

#include <Headers/ApplicationStates/AbstractApplicationState.h>
#include <Headers/Core/DateTime.h>

namespace pan {

	/**
	 * Class that update real game time via DateTime::update() call <p> <p>
	 *
	 * Each application state, that want manipulate real game time MUST <p>
	 * inherit from this class and call update(), <p>
	 * in overridden update method, at first place
	 */
	class AbstractTimeableApplicationState : public AbstractApplicationState {
	public:
		virtual Bool update() override {
			DateTime::getInstance()->update();

			return true;
		}
	};
}

#endif
