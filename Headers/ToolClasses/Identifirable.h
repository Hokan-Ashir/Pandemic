#ifndef __IDENTIFIRABLE_H__
#define __IDENTIFIRABLE_H__

#include <string>

class Identifirable {
public:
	void setId(std::string id) {
		this->id = id;
	}

	std::string getId() const {
		return id;
	}

private:
	std::string id;	
};

#endif
