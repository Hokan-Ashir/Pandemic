#ifndef __ABSTRACTAPPLICATIONSTATE_H__
#define __ABSTRACTAPPLICATIONSTATE_H__

#include <Engine/Headers/EsenthelEngine.h>
#include <Headers/ToolClasses/Identifirable.h>

class AbstractApplicationState : public Identifirable {
public:
	AbstractApplicationState() {};
	virtual ~AbstractApplicationState() {};

	virtual Bool init() = 0;
	virtual void draw() = 0;
	virtual Bool update() = 0;
	virtual void shutdown() = 0;	
	virtual void render() = 0;
};

#endif