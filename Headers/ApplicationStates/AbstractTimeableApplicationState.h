#ifndef __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__
#define __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__

#include <Headers/ApplicationStates/AbstractApplicationState.h>
#include <Headers/Core/CurrentDateTime.h>

namespace pan {

	/**
	 * Class-wrapper that update real game time via DateTime::update() call before call actual <p>
	 * updateActions call in derived classes
	 */
	class AbstractTimeableApplicationState : public AbstractApplicationState {
	public:
		virtual ~AbstractTimeableApplicationState() {}

		virtual Bool update() final override {
			CurrentDateTime::getInstance()->update();
			return updateActions();
		}

	protected:
		virtual Bool updateActions() = 0;
	};
}

#endif
