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
	 * // create/get State-singleton instance and get its ID <p>
	 * auto stateName = SomeState::getInstance()->getId().data(); <p>
	 * // set new state by its ID <p>
	 * \ref StateManager::getInstance()->setCurrentState(stateName); <p> <p>
	 *
	 * Note: <p>
	 *		All classes that implements AbstractApplicationState, <p>
	 *		if they want to be manipulated by StateManager MUST: <p>
	 *		- set their IDs <p>
	 *		- register themselves in StateManager in their constructors <p>
	 *		- also they need to implement method <p>
	 *			std::string getId() const { <p>
	 *				return Identifirable::getId() <p>
	 *			} <p>
	 * to enable access to identifier after getInstance() call <p>
	 * because singleton only know about methods of template-class, <p>
	 * and not its base classes <p> <p>
	 *
	 * How it works: <p>
	 * <ul>
	 * <li> Esenthel Engine state's (via State struct) pointer-to-functions <p>
	 * are binded in StateManager's constructor via ProxyCall pointer-to-static-method <p>
	 * <li> If some AbstractApplicationState (AAS) want to be called it: <p>
	 *		<ol>
	 *		<li> must set its Id <p>
	 *		<li> must register itself in StateManager <p>
				both actions MUST be in AAS constructor <p>
	 *		</ol>
	 * <li> When state must be called: <p>
	 *		<ol>
	 *		<li> it initialized (via getInstance() call) <p>
	 *		<li> get its name <p>
	 *		<li> by this name its pointer gotten from StateManager map <p>
	 *		<li> this pointer set to ProxyCall <p>
	 *		<li> as ProxyCall already binded to Esenthel Engine state via its pointers (see pt.1) <p>
	 *			it call pointer-to-AAS method that want to be called
	 *		</ol>
	 * </ul>
	 *
	 * \todo string class-name based identification mechanism can be replaced via typeid(ClassName).name()
	 *			or if this is used inside class - typeid(*this).name()
	 */
	class StateManager final : public Singleton<StateManager> {
		SET_SINGLETON(StateManager)

	public:
		
		/**
		 * Wrapper around std::map::insert to add state object as map value, with its name as map key
		 *
		 * \param std::string Id identificator of registering object
		 * \param AbstractApplicationState * state pointer to object, that want to be registered
		 */
		void registerState(std::string Id, AbstractApplicationState* state);

		/**
		 * Set state by its Id as active. <p>
		 * Get pointer to state instance, searching it in state map, if instance not found <p>
		 * method return, doing nothing (warning added to log), <p>
		 * otherwise method bind state pointer-to-methods via ProxyCall and set found state as <p>
		 * active in terms of Esenthel Engine
		 *
		 * \param std::string Id identificator of state, that want to be set as currently active
		 */
		void setCurrentState(std::string Id);

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