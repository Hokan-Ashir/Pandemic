#ifndef __ABSTRACTAPPLICATIONSTATE_H__
#define __ABSTRACTAPPLICATIONSTATE_H__

#include <list>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Identifirable.h>
#include <Headers/ToolClasses/IDrawable.h>
#include <Headers/ToolClasses/IUpdatable.h>

namespace pan {
	class AbstractApplicationState : public Identifirable {
	public:
		AbstractApplicationState() {};
		virtual ~AbstractApplicationState() {};

		virtual Bool init() = 0;
		virtual void draw() = 0;
		virtual Bool update() = 0;
		virtual void shutdown() = 0;
		virtual void render() = 0;

	protected:
		void addDrawableObject(std::shared_ptr<IDrawable> object);
		void addUpdateableObject(std::shared_ptr<IUpdateable> object);

		std::list<std::shared_ptr<IDrawable>> drawableObjects;
		std::list<std::shared_ptr<IUpdateable>> updateableObjects;
	};
}

#endif