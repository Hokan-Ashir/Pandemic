
#ifndef __FINAL_CLASS_H__
#define __FINAL_CLASS_H__

/*
Usage:

class ClassThatWantToBeNonDerivable : private virtual FinalClass {
	....
}
*/

class FinalClass {
protected:
	FinalClass();
	~FinalClass();
};

#endif __FINAL_CLASS_H__