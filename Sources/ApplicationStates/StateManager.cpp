#include <string>

#include <Headers/ApplicationStates/StateManager.h>
#include <Headers/ToolClasses/ProxyCall.h>
#include <Headers/Logging/Logger.h>

namespace pan {
	void StateManager::registerState(AbstractApplicationState* state) {
		std::string className = typeid(state).name();
		states.insert(std::pair < std::string, AbstractApplicationState* >(className, state));
		Logger::getInstance()->info(std::string("State with Id '" + className + "' registered").data());
	}

	void StateManager::setCurrentState(AbstractApplicationState* state) {
		std::string className = typeid(state).name();
		Logger::getInstance()->info(std::string("Calling state with Id '" + className + "'").data());
		
		try {
			state = states.at(className);
		} catch (std::out_of_range e) {
			Logger::getInstance()->warning(std::string("State with Id '" + className + "' does not exists").data());
			return;
		}

		ProxyCall::setClass(state);
		engineState.set();
		Logger::getInstance()->info(std::string("State with Id '" + className + "' called").data());
	}

	StateManager::StateManager() : engineState(ProxyCall::update, ProxyCall::draw, ProxyCall::init, ProxyCall::shutdown) {
	}

	StateManager::~StateManager() {
	}
}