#ifndef SINGLETON_H
#define SINGLETON_H
#include "Poco/Mutex.h"
#include <memory>
/*
Infernale890: this class is used to declare a single static object per type in a safe way.
example:

log.h -> #define log Singleton<Log>::Instance() //it's not necessary
log.cpp -> ISTANTIATE_SINGLETON(log) //it's necessary because it istantiates the static members of Singleton, only one per type is permitted

file.cpp-> log.do_action() //access the static object of type log
*/
template <typename T>
class Singleton
{
	public:
	static T& Instance()
	{
		Poco::FastMutex::ScopedLock lock(*_mutex);
		if (!_instance.get())
		{
			_instance.reset(new T);
		}
		return *_instance;
	}

	static void DestroyInstance()
	{
		Poco::FastMutex::ScopedLock lock(*_mutex);
		try
		{
			_instance.reset(); //automatically set to null
		} catch(...) {}
	}

	protected:
		Singleton(){}

	private:
		static 	std::auto_ptr<Poco::FastMutex>	_mutex;
		static 	std::auto_ptr<T>		_instance;
};

#define ISTANTIATE_SINGLETON(obj) \
	template class Singleton<obj>; \
	template<> std::auto_ptr<Poco::FastMutex> Singleton<obj>::_mutex(new Poco::FastMutex); \
	template<> std::auto_ptr<obj> Singleton<obj>::_instance(NULL);

#endif
