#ifndef __DRAWEVENT_H__
#define __DRAWEVENT_H__

#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	/**
	 * Core draw-event, for objects, that want to be drawn in current application state
	 * draw-loop call (AbstractApplicationState::draw())
	 */
	class DrawEvent : public Event {

	};
}

#endif