#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include <map>

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>

/*
Class that manage storing and setting Esenthel Engine states


Usage:
// create/get State-singleton instance and get its ID
auto stateName = IntroState::getInstance()->getId().data();
// set new state by its ID
StateManager::getInstance()->setCurrentState(stateName);

Note:
All classes that implements AbstractApplicationState, 
if they want to be manipulated by StateManager MUST:
	- set their IDs 
	- register themselves in StateManager
in their constructors
	- also they need to implement method
	std::string getId() const {
		return Identifirable::getId()
	}
	to enable access to identifier after getInstance() call
	because singleton only know about methods of templated class, 
	and not its base classes

How it works:
1. Esenthel Engine state's (via "State" struct) pointer-to-functions
are binded in StateManager's constructor via ProxyCall pointer-to-static-method
2. If some AbstractApplicationState (AAS) want to be called it:
	- must set its Id
	- must register itself in StateManager
both actions MUST be in AAS constructor
3. When state must be called:
	- it initialized (via getInstance() call)
	- get its name
	- by this name its pointer gotten from StateManager map
	- this pointer set to ProxyCall
	- as ProxyCall already binded to Esenthel Engine state via its pointers (see pt.1)
	it call pointer-to-AAS method that want to be called
*/
namespace pan {
	class StateManager final : public Singleton<StateManager> {
		SET_SINGLETON(StateManager)

	public:
		void registerState(std::string Id, AbstractApplicationState* state);
		void setCurrentState(std::string Id);

	protected:
		StateManager();
		virtual ~StateManager() override;

	private:
		std::map<std::string, AbstractApplicationState*> states;
		State engineState;
	};
}

#endif