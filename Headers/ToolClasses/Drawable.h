#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

class Drawable {
public:
	virtual ~Drawable() {		
	}

	virtual void draw() = 0;	
};

#endif
