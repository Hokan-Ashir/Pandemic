#include <Headers/ToolClasses/Singleton.h>


template <typename T>
T* Singleton<T>::Instance() {
	if (instance == nullptr) {
		instance = new T;
	}

	ASSERT(instance != nullptr);

	return instance;
}

template <typename T>
void Singleton<T>::DestroyInstance() {
	delete instance;
	instance = nullptr;
}