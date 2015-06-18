#include <Headers/ApplicationStates/IntroState.h>
#include <Headers/ApplicationStates/StateManager.h>

IntroState::IntroState() {
	setId("IntroState");
	StateManager::getInstance()->registerState(getId(), this);
}

IntroState::~IntroState() {
}

Bool IntroState::init() {
	return true;
}

void IntroState::draw() {
}

Bool IntroState::update() {
	if (Kb.bp(KB_ESC)) {
		return false;
	}

	return true;
}

void IntroState::shutdown() {
}

void IntroState::render() {
}

std::string IntroState::getId() const {
	return Identifirable::getId();
}