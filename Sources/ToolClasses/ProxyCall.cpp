#include <Headers/ToolClasses/ProxyCall.h>

namespace pan {
	AbstractApplicationState* ProxyCall::instance = nullptr;

	void ProxyCall::setClass(AbstractApplicationState* state) {
		instance = state;
	}

	Bool ProxyCall::init() {
		return instance->init();
	}

	void ProxyCall::draw() {
		instance->draw();
	}

	Bool ProxyCall::update() {
		return instance->update();
	}

	void ProxyCall::shutdown() {
		instance->shutdown();
	}

	void ProxyCall::render() {
		instance->render();
	}
}