#ifndef __MAINAPPLICATIONSTATE_H__
#define __MAINAPPLICATIONSTATE_H__

#include <Headers/ToolClasses/Singleton.h>
#include <Headers/ApplicationStates/AbstractTimeableApplicationState.h>

namespace pan {

	/**
	 * Main class of application <p>
	 * Describe Esenthel Engine/keyboard/display initialization, registration of other system-classes, <p>
	 * that want to be updated/drawn
	 */
	class MainApplicationState final : public Singleton <MainApplicationState>, public AbstractTimeableApplicationState {
		SET_SINGLETON(MainApplicationState)

	protected:
		MainApplicationState();
		virtual ~MainApplicationState() override;
	public:

		/**
		 * Initialize Esenthel Engine, keyboard layer, display, sets their parameters
		 */
		void initializeEgine();
		virtual Bool init() override;
		virtual void draw() override;
		virtual Bool update() override;
		virtual void shutdown() override;
		virtual void render() override;
	};
}

#endif