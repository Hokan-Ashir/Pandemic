#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include <map>

#include <Engine/Headers/EsenthelEngine.h>

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>

namespace pan {

	/**
	 * Class that manage storing and setting Esenthel Engine states <p> <p>
	 *
	 * Usage: <p>
	 * // create/get State-singleton instance <p>
	 * auto state = SomeState::getInstance(); <p>
	 * // set new state by its class name via pointer to state <p>
	 * \ref StateManager::getInstance()->setCurrentState(state); <p> <p>
	 *
	 * Note: <p>
	 *		All classes that implements AbstractApplicationState, <p>
	 *		if they want to be manipulated by StateManager MUST register themselves in StateManager, <p>
	 *		preferably in their constructors <p>
	 *
	 * How it works: <p>
	 * <ul>
	 * <li> Esenthel Engine state's (via State struct) pointer-to-functions <p>
	 * are binded in StateManager's constructor via ProxyCall pointer-to-static-method <p>
	 * <li> If some AbstractApplicationState (AAS) want to be called it: <p>
	 *		<ol>
	 *		<li> must register itself in StateManager, preferably in its constructor <p>
	 *		</ol>
	 * <li> When state must be called: <p>
	 *		<ol>
	 *		<li> it initialized (via getInstance() call) <p>
	 *		<li> get pointer to its instance <p>
	 *		<li> by this pointer, get its name and again its pointer gotten from StateManager map <p>
	 *		<li> this pointer set to ProxyCall <p>
	 *		<li> as ProxyCall already binded to Esenthel Engine state via its pointers (see pt.1) <p>
	 *			it call pointer-to-AAS method that want to be called
	 *		</ol>
	 * </ul>
	 *
	 * \todo Check if it necessary to store application states' names, cause now they are registered <p>
	 *		and called via its pointers
	 */
	class StateManager final : public Singleton<StateManager> {
		SET_SINGLETON(StateManager)

	public:
		
		/**
		 * Wrapper around std::map::insert to add state object as map value, with its name as map key
		 *
		 * \param AbstractApplicationState * state pointer to object, that want to be registered
		 */
		void registerState(AbstractApplicationState* state);

		/**
		 * Set state by its class name (which is got through its pointer) as active. <p>
		 * Get pointer to state instance, searching it in state map, if instance not found <p>
		 * method return, doing nothing (warning added to log), <p>
		 * otherwise method bind state pointer-to-methods via ProxyCall and set found state as <p>
		 * active in terms of Esenthel Engine
		 *
		 * \param std::string Id identificator of state, that want to be set as currently active
		 */
		void setCurrentState(AbstractApplicationState* state);

	protected:
		StateManager();
		virtual ~StateManager() override;

	private:

		/**
		 * Map of registered states of application, with state id as key, and pointer-to-state as value
		 */
		std::map<std::string, AbstractApplicationState*> states;

		/**
		 * Currently active state of Esenthel Engine
		 */
		State engineState;
	};
}

#endif