#ifndef __UPDATEABLE_H__
#define __UPDATEABLE_H__

class Updateable {
public:
	virtual ~Updateable() {		
	}

	virtual void update() = 0;	
};

#endif
