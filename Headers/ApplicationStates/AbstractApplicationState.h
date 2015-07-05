#ifndef __ABSTRACTAPPLICATIONSTATE_H__
#define __ABSTRACTAPPLICATIONSTATE_H__

#include <list>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Identifirable.h>
#include <Headers/ToolClasses/IDrawable.h>
#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	/**
	 * Abstract class of any state in the game <p>
	 * With usage of ProxyCall impersonate State from Esenthel Engine <p>
	 * (see documentation for ProxyCall for more info) <p>
	 * Also allow all derived classes to assign to themselves identifier via Identifirable class inheritance <p> <p>
	 * Stores game objects and systems that want to be drawn (implements IDrawable), <p>
	 * which will be drawn in draw() method, <p>
	 * or/and updated (implements IUpdateable), which will be updated in update() method
	 */
	class AbstractApplicationState : public Identifirable {
	public:
		AbstractApplicationState();
		virtual ~AbstractApplicationState();

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
		 * Wrapper around std::list::push_back() to register drawable object for drawing
		 *
		 * \param std::shared_ptr<IDrawable> object object that want to be drawn
		 */
		void addDrawableObject(std::shared_ptr<IDrawable> object);

		/**
		 * Wrapper around std::list::push_back() to register updateable object for update
		 *
		 * \param std::shared_ptr<IUpdateable> object object that want to be updated
		 */
		void addUpdateableObject(std::shared_ptr<IUpdateable> object);

		/**
		 *	\ref List of objects, that want to be drawn
		 */
		std::list<std::shared_ptr<IDrawable>> drawableObjects;

		/**
		 *	\ref List of objects, that want to be updated
		 */
		std::list<std::shared_ptr<IUpdateable>> updateableObjects;
	};
}

#endif