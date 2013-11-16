/**
 * Threads/ThreadManager.h
 * Threads class
 *
 * File part of "Multithreaded Multiplatform Server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

#ifndef __THREADS_THREADMANAGER_H__
#define __THREADS_THREADMANAGER_H__

// Includes
#include "../Sockets/Sockets.h" // Include Sockets
#ifdef _WIN32 // WIN32
#include <Windows.h>
typedef void T_PROC;
typedef DWORD T_TYPE;
typedef HANDLE T_SEM;
typedef HANDLE T_MUTEX;
typedef HANDLE T_RES;
#else // LINUX
#include <pthread.h>
#include <semaphore.h>
typedef void* T_PROC;
typedef pthread_t T_TYPE;
typedef sem_t T_SEM;
typedef pthread_mutex_t T_MUTEX;
typedef int T_RES;
void Sleep(int ms);
#endif
#define MAX_THREAD_COUNT 10 // Max thread count - Should be MAX_CONNECTIONS+3. Use thread-per-client model

class ThreadManager
{
public:
	ThreadManager(std::string a,int p);
	~ThreadManager();

	// Functions
	int getThreadCount();
	std::string getError();

	// Thread Routines
	static T_PROC listenThread(void* lParam);
	static T_PROC processThread(void* lParam);
	static T_PROC connThread(void* lParam);
	static T_PROC userThread(void* lParam);

	// Other functions
	static void incrementThreadCount();
	static void decrementThreadCount();

	// Vars
	static Sockets *server;

private:
	T_RES _threads[MAX_THREAD_COUNT];
	T_TYPE _threadId[MAX_THREAD_COUNT];
	// Static members - need routines to work on these
	static T_MUTEX _cMutex;
	static T_SEM _acceptSem;
	static bool _shutdown;
	static int _threadCount;
	static std::queue<int> _connQueue;
	static std::queue<int> _actQueue;
	static std::string _err;
#ifdef _WIN32 // WIN32 vars
	// WIN32
#else // LINUX vars
	// LINUX
#endif
};
#endif
