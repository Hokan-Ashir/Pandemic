#include <Headers/ApplicationStates/AbstractApplicationState.h>

void AbstractApplicationState::addDrawableObject(std::shared_ptr<Drawable> object) {
	drawableObjects.push_back(object);
}

void AbstractApplicationState::addUpdateableObject(std::shared_ptr<Updateable> object) {
	updateableObjects.push_back(object);
}