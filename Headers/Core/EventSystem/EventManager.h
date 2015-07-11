#ifndef __EVENTMANAGER_H__
#define __EVENTMANAGER_H__

// undefine macroses or typedefs declared in Esenthel Engine headers
#undef T
#undef C

#include <map>
#include <list>
#include <typeindex>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <Headers/ToolClasses/Singleton.h>

namespace pan {

	/**
	 * Base event class; All event classes MUST be derived from it, otherwise <p>
	 * compiler will rise error via BOOST_STATIC_ASSERT((boost::is_base_of< ... >::value)); assertion <p>
	 * NOTE: this is compiler-time assertion
	 */
	class Event	{
	};	

	/**
	 * Base event handler class; All event handler classes MUST be derived from it, otherwise <p>
	 * compiler will rise error via BOOST_STATIC_ASSERT((boost::is_base_of< ... >::value)); assertion <p>
	 * NOTE: this is compiler-time assertion
	 */
	class BaseEventHandler {
	public:
		virtual ~BaseEventHandler() {};
		void handleEvent(const Event* eventToProceed) {
			call(eventToProceed);
		}

	private:
		virtual void call(const Event* eventToProceed) {};
	};	

	/**
	 * Class, that store and correspond type of events to list of their handlers <p>
	 * All source code is taken and slightly modified/formatted from here: <p>
	 * http://www.gamedev.net/page/resources/_/technical/game-programming/effective-event-handling-in-c-r2459
	 * <p> <p>
	 * One alternative variant can be storing map like: <p>
	 *
	 *		template<class E> std::map<std::type_index, std::list<IEventHandler<E>*>> handlers; <p>
	 *
	 * where "E" is type of Event (kindof "E extends Event" in Java)
	 * and IEventHandler will look like:
	 *
	 * template<class E> class IEventHandler {
	 * public:
	 *		void handleEvent(const E* event);
	 * }
	 *
	 * BUT this wont work in C++, cause compiler know nothing about "E", it can be "Event"/"Object"/anything
	 * So to avoid this, author of this method use class-wrapper (BaseEventHandler), from which any event-hadler
	 * class MUST derive; 
	 * Those base class method (BaseEventHandler::handleEvent()) can call real event-handler class method, which
	 * will handle real event
	 */
	class EventManager : public Singleton<EventManager> {
		SET_SINGLETON(EventManager)
	public:
		/**
		 * Search through all possible events in handlers-map, find corresponding event-handlers <p>
		 * and laucnch them, passing incoming event <p>
		 * NOTE: Non-derivable from Event classes won't proceed <p>
		 *
		 * \param const E* eventToProceed - event that fired and must be proceed
		 */
		template<class E> void fireEvent(const E* eventToProceed) {
			BOOST_STATIC_ASSERT((boost::is_base_of<Event, E>::value));

			auto it = handlers.find(std::type_index(typeid(*eventToProceed)));
			if (it != handlers.end()) {
				for (auto handler : it->second) {
					handler->handleEvent(eventToProceed);
				}
			}
		}

		/**
		 * Search through all possible events in handlers-map, find corresponding event-handlers list <p>
		 * (if not - create empty list) <p>
		 * and add instance of BaseEventHandler to it <p>
		 * NOTE: Non-derivable from Event classes won't proceed <p>
		 * NOTE: Non-derivable from BaseEventHandler classes won't proceed <p>
		 *
		 * \param T* instance - object, that store event-handler method
		 * \param void (T::*method)(E*) - pointer to event-handler method, that will be stored
		 */
		template <class T, class E>	void registerEventHandlerMethod(T* instance, void (T::*method)(E*)) {
			BOOST_STATIC_ASSERT((boost::is_base_of<Event, E>::value));
			BOOST_STATIC_ASSERT((boost::is_base_of<BaseEventHandler, T>::value));

			auto key = std::type_index(typeid(E));
			std::list<BaseEventHandler*> list;
			try {
				list = handlers.at(key);
				list.push_back(new MemberFunctionHandler<T, E>(instance, method));
				handlers.at(key) = list;
			} catch (std::out_of_range e) {
				list.push_back(new MemberFunctionHandler<T, E>(instance, method));
				handlers.insert(std::make_pair(std::type_index(typeid(E)), list));
			}
		}

		/**
		* Search through all possible events in handlers-map, find corresponding event-handlers list <p>
		* and delete instance corresponding of BaseEventHandler <p>
		* NOTE: Non-derivable from Event classes won't proceed <p>
		* NOTE: Non-derivable from BaseEventHandler classes won't proceed <p>
		*
		* \param T* instance - object, that store event-handler method
		* \param void (T::*method)(E*) - pointer to event-handler method, that will be deleted
		*/
		template <class T, class E>	void unregisterEventHandlerMethod(T* instance, void (T::*method)(E*)) {
			BOOST_STATIC_ASSERT((boost::is_base_of<Event, E>::value));
			BOOST_STATIC_ASSERT((boost::is_base_of<BaseEventHandler, T>::value));

			auto it = handlers.find(std::type_index(typeid(E)));
			if (it != handlers.end()) {
				for (auto handler : it->second) {
					if (static_cast<MemberFunctionHandler<T, E> *>(handler)->getInstance() == instance) {
						it->second.remove(handler);
						return;
					}
				}
			}			
		}

	private:
		/**
		 * Wrapper-class, base for all event handlers <p>
		 * Simply store pointer to real event-handler object and pointer to real event-handler method <p>
		 * via static downcasting to real event type <p>
		 * And provide interface to call them via BaseEventHandler::call() method
		 */
		template <class T, class E>
		class MemberFunctionHandler : public BaseEventHandler {
		public:
			typedef void (T::*MemberFunc)(E*);
			MemberFunctionHandler(T* instance, MemberFunc method) : instance(instance), method(method) {};

			void call(const Event* eventToProceed) override {
				(instance->*method)(static_cast<E*>(eventToProceed));
			}
		
			T* getInstance() const {
				return instance;
			}

		private:
			T* instance;
			MemberFunc method;
		};

		std::map<std::type_index, std::list<BaseEventHandler*>> handlers;
	};
}

#endif
