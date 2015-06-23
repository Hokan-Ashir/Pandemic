#ifndef __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__
#define __ABSTRACTTIMEABLEAPPLICATIONSTATE_H__

#include <Headers/ApplicationStates/AbstractApplicationState.h>
#include <Headers/DayNightCircleSystem/DateTime.h>

namespace pan {
	/*
	Class that describes real game time update

	Each application state, that want manipulate real game time MUST
	inherit from this class and call 
	virtual void update()
	in overriden update method at first place
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
