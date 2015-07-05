#ifndef __IDRAWABLE_H__
#define __IDRAWABLE_H__

namespace pan {
	/**
	 * Interface that each object, that want to be drawn,
	 * must implement
	 */
	class IDrawable {
	public:
		virtual ~IDrawable() {
		}

		/**
		 * Implementable method for objects, that want to be drawn
		 */
		virtual void draw() = 0;
	};
}

#endif
