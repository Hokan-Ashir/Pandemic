#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ApplicationStates/MainApplicationState.h>

void InitPre() {	
	MainApplicationState::getInstance()->initializeEgine();
}

Bool Init() {	
	return MainApplicationState::getInstance()->init();
}

void Shut() {
	MainApplicationState::getInstance()->shutdown();
}

Bool Update() {	
	return MainApplicationState::getInstance()->update();
}

void Draw() {	
	MainApplicationState::getInstance()->draw();	
}
