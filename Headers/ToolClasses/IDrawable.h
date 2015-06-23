#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

namespace pan {
	class IDrawable {
	public:
		virtual ~IDrawable() {
		}

		virtual void draw() = 0;
	};
}

#endif
