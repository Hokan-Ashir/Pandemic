#ifndef __PROXYCALL_H__
#define __PROXYCALL_H__

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractApplicationState.h>

// TODO maybe do generic method
// cause one ProxyCall for ApplicationStates with "init", "draw", "render", "update", "shutdown"
// method calls
// and one for other objects with "draw", "update", "create" method calls

/*
Class that manage to convert pointer-to-methods to pointer-to-functions
to pass to Esenthel Engine callback class-methods like Render(&void())

Usage:
inside desirable class that want to convert its method pointer to function pointer
i.e "A" with "render" method
ProxyCall::setClass(this)
Render(ProxyCall::render)
*/
namespace pan {
	class ProxyCall final : public Singleton<ProxyCall> {
		SET_SINGLETON(ProxyCall)
	public:
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
		static AbstractApplicationState* instance;
	};
}

#endif