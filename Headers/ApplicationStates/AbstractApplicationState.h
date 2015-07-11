#ifndef __ABSTRACTAPPLICATIONSTATE_H__
#define __ABSTRACTAPPLICATIONSTATE_H__

#include <list>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/Core/EventSystem/EventManager.h>

namespace pan {
	/**
	 * Abstract class of any state in the game <p>
	 * With usage of ProxyCall impersonate State from Esenthel Engine <p>
	 * (see documentation for ProxyCall for more info) <p>
	 * Stores game objects and systems that want to be drawn, which will be drawn in draw() method, <p>
	 * or/and updated, which will be updated in update() method
	 */
	class AbstractApplicationState {
	public:
		virtual ~AbstractApplicationState() {}

		/**
		 * This method that called only once, when state is set as active via State::set() <p>
		 * Impersonates State init-callback function
		 *
		 * \return Bool true, if initialization was successful, false, if any errors occurred
		 */
		virtual Bool init() = 0;

		/**
		 * This method calls each frame to draw object of scene, registered via addDrawableObject() <p>
		 * Impersonates State draw-callback function
		 */
		virtual void draw() = 0;

		/**
		 * This method calls each frame to update object of scene, registered via addUpdateableObject() <p>
		 * Impersonates State update-callback function
		 *
		 * \return Bool true, if update was successful, false, if any errors occurred
		 */
		virtual Bool update() = 0;

		/**
		 * This method that called only once, when state is pop up from state-stack <p>
		 * Impersonates State shutdown-callback function
		 */
		virtual void shutdown() = 0;

		/**
		 * This method calls each frame to render object of scene <p>
		 * Impersonates State render-callback function
		 */
		virtual void render() = 0;
	protected:

		/**
		 * Wrapper around list::push_back call for list of application state core event handlers <p>
		 * 
		 * \param std::shared_ptr<BaseEventHandler> handler - object that whished to be stored
		 */
		void addEventHandler(std::shared_ptr<BaseEventHandler> handler) {
			eventHandlers.push_back(handler);
		}

	private:

		/**
		 * List of application state core event handlers <p>
		 * More precisely, it allows to store objects, that created in application states and must be stored <p>
		 * to be updated/drawn in application state live-loop
		 */
		std::list<std::shared_ptr<BaseEventHandler>> eventHandlers;
	};
}

#endif