#ifndef __ABSTRACTAPPLICATIONSTATE_H__
#define __ABSTRACTAPPLICATIONSTATE_H__

#include <list>
#include <boost/smart_ptr/shared_ptr.hpp>

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Identifirable.h>
#include <Headers/ToolClasses/Drawable.h>
#include <Headers/ToolClasses/Updatable.h>

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
	void addDrawableObject(std::shared_ptr<Drawable> object);
	void addUpdateableObject(std::shared_ptr<Updateable> object);	

	std::list<std::shared_ptr<Drawable>> drawableObjects;
	std::list<std::shared_ptr<Updateable>> updateableObjects;
};

#endif