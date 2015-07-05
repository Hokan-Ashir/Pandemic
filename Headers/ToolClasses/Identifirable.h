#ifndef __IDENTIFIRABLE_H__
#define __IDENTIFIRABLE_H__

namespace pan {

	/**
	 *	Class, that stores string identifier of object
	 */
	class Identifirable {
	public:

		/**
		 * \param std::string id new identificator of object
		 */
		void setId(std::string id) {
			this->id = id;
		}

		/**
		 * NOTE: this method MUST be overridden inside any application state,
		 * in case application want to be registered in StateManager
		 * This is because any application state is template-singleton (see Singleton),
		 * which instance only have access to public methods INSIDE class, that passes as
		 * template parameter to Singleton
		 *
		 * i.e:
		 * class SomeApplicationState : public \ref Singleton<SomeApplicationState>, public \ref Indetifirable
		 *
		 * in this case Singleton::getInstance() only knows about public methods of SomeApplicationState
		 * and not about getId() method, which uses in StateManager::registerState() and StateManager::setCurrentState()
		 *
		 * \return std::string current identifier of object
		 */
		std::string getId() const {
			return id;
		}

	private:

		/**
		 * Current identifier of object
		 */
		std::string id;
	};
}

#endif
