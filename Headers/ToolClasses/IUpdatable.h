#ifndef __IUPDATEABLE_H__
#define __IUPDATEABLE_H__

namespace pan {
	class IUpdateable {
	public:
		virtual ~IUpdateable() {
		}

		virtual void update() = 0;
	};
}

#endif
