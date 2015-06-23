/*!
\file       singleton.h
\brief      Implementation of the Singleton template class.
\author     Brian van der Beek
*/

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace pan {
#undef T
#define SET_SINGLETON(classname) friend class Singleton<classname>;

	//! The Singleton class is a template class for creating singleton objects.
	/*!
	When the static getInstance() method is called for the first time, the singleton
	object is created. Every sequential call returns a reference to this instance.
	The class instance can be destroyed by calling the destroyInstance() method.
	*/
	template <typename T> class Singleton {
	public:

		//! Gets a reference to the instance of the singleton class.
		/*!
		\return A reference to the instance of the singleton class.
		If there is no instance of the class yet, one will be created.
		*/
		static T* getInstance() {
			if (instance == nullptr) {
				instance = new T;
			}

			return instance;
		};

		//! Destroys the singleton class instance.
		/*!
		Be aware that all references to the single class instance will be
		invalid after this method has been executed!
		*/
		static void destroyInstance() {
			delete instance;
			instance = nullptr;
		};

	protected:

		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a Singleton instance.
		Singleton() {};

		virtual ~Singleton() {};

	private:
		Singleton(const Singleton& source) {};

		static T* instance;
	};

	//! static class member initialisation.
	template <typename T> T* Singleton<T>::instance = nullptr;
}

#endif // ! defined __SINGLETON_H__