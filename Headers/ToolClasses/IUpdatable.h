#ifndef __IUPDATEABLE_H__
#define __IUPDATEABLE_H__

namespace pan {
	/**
	 * Interface that each object, that want to be updated,
	 * must implement
	 */
	class IUpdateable {
	public:
		virtual ~IUpdateable() {
		}

		/**
		 * Implementable method for objects, that want to be updated
		 */
		virtual void update() = 0;
	};
}

#endif
