#include <Headers/ApplicationStates/AbstractApplicationState.h>

namespace pan {
	void AbstractApplicationState::addDrawableObject(std::shared_ptr<IDrawable> object) {
		drawableObjects.push_back(object);
	}

	void AbstractApplicationState::addUpdateableObject(std::shared_ptr<IUpdateable> object) {
		updateableObjects.push_back(object);
	}
}