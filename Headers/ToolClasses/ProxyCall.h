#ifndef __PROXYCALL_H__
#define __PROXYCALL_H__

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>

namespace pan {
	/**
	 * Class that manage to convert pointer-to-methods to pointer-to-functions <p>
	 * to pass to Esenthel Engine callback class-methods like Render(&void()) <p><p>
	 *
	 * Usage: <p>
	 * Inside desirable class that want to convert its method pointer to function pointer <p>
	 * i.e "A" with "render" method <p>
	 * ProxyCall::setClass(this) <p>
	 * Render(ProxyCall::render) <p><p>
	 *
	 * \todo 
	 * Maybe do generic method <p>
	 * One ProxyCall for AbstractApplicationState with "init", "draw", "render", "update", "shutdown"
	 * method calls <p>
	 * And one for other objects with "draw", "update", "create" method calls
	 */
	class ProxyCall final : public Singleton<ProxyCall> {
		SET_SINGLETON(ProxyCall)
	public:
		/**
		 * Store pointer to application state in static variable, which is mapped to <p>
		 * init(), draw(), update(), shutdown() and render() calls, so each call of those methods
		 * will call same methods from static variable
		 *
		 * \param AbstractApplicationState* pointer to application state, that want to be active
		 */
		static void setClass(AbstractApplicationState* state);
		static Bool init();
		static void draw();
		static Bool update();
		static void shutdown();
		static void render();

	protected:
		ProxyCall() {
		}

		virtual ~ProxyCall() override {
		}

	private:

		/**
		 * Storage of pointer to currently active application state
		 */
		static AbstractApplicationState* instance;
	};
}

#endif