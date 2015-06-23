#include <Headers/ApplicationStates/StateManager.h>
#include <Headers/ToolClasses/ProxyCall.h>
#include <Headers/Logging/Logger.h>

namespace pan {
	void StateManager::registerState(std::string Id, AbstractApplicationState* state) {
		states.insert(std::pair < std::string, AbstractApplicationState* >(Id, state));
		Logger::getInstance()->info(std::string("State with Id '" + Id + "' registered").data());
	}

	void StateManager::setCurrentState(std::string Id) {
		Logger::getInstance()->info(std::string("Calling state with Id '" + Id + "'").data());

		AbstractApplicationState* state = nullptr;
		try {
			state = states.at(Id);
		} catch (std::out_of_range e) {
			Logger::getInstance()->warning(std::string("State with Id '" + Id + "' does not exists").data());
			return;
		}

		ProxyCall::setClass(state);
		engineState.set();
		Logger::getInstance()->info(std::string("State with Id '" + Id + "' called").data());
	}

	StateManager::StateManager() : engineState(ProxyCall::update, ProxyCall::draw, ProxyCall::init, ProxyCall::shutdown) {
	}

	StateManager::~StateManager() {
	}
}