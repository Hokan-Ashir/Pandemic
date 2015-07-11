#ifndef __UPDATEEVENT_H__
#define __UPDATEEVENT_H__

#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	/**
	 * Core update-event, for objects, that want to be updated in current application state
	 * update-loop call (AbstractApplicationState::update())
	 */
	class UpdateEvent : public Event {

	};
}

#endif