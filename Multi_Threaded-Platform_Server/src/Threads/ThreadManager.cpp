/**
 * Threads/ThreadManager.cpp
 * Threads class
 *
 * File part of "Multithreaded Multiplatform Server"
 *
 * Dennis J. McWherter, Jr.
 * 12/28/10
 */

#include "ThreadManager.h"
#include "../config.h"
#include <iostream>
#ifdef _WIN32
#include <process.h> // _beginthreand & _endthread live here 
#endif

// Linux sleep in MS
#ifdef __linux__
void Sleep(int ms)
{
	usleep(1000*ms);
}
#endif

// Clear queue method
void clear(std::queue<int> &q)
{
	std::queue<int> empty;
	std::swap(q,empty);
}

// Init static members
Sockets *ThreadManager::server = new Sockets(hostname,port);
#ifdef _WIN32
T_SEM ThreadManager::_acceptSem = CreateSemaphore(NULL,1,1,NULL);
T_MUTEX ThreadManager::_cMutex = CreateMutex(NULL,false,NULL);
#else
T_SEM ThreadManager::_acceptSem;
T_MUTEX ThreadManager::_cMutex = PTHREAD_MUTEX_INITIALIZER;
#endif
bool ThreadManager::_shutdown = false;
int ThreadManager::_threadCount = 0;
std::queue<int> ThreadManager::_connQueue = std::queue<int>();
std::queue<int> ThreadManager::_actQueue  = std::queue<int>();
std::string ThreadManager::_err = "";

ThreadManager::ThreadManager(std::string a,int p)
{
	if(server->init() == 1)
		_err = "Could not initialize server!";

	// Init semaphore for *nix
#ifdef __linux__
	if(sem_init(&_acceptSem,0,1))
		_err = "Could not initialize semaphore!";
#endif

	// Start our 3 main threads - If we have no fatal errors
	if(_err.empty())
	{
#ifdef _WIN32 // WIN32 method
		_threads[0] = (HANDLE)_beginthread(listenThread,0,NULL);
		_threads[1] = (HANDLE)_beginthread(connThread,0,NULL);
		_threads[2] = (HANDLE)_beginthread(processThread,0,NULL);
#else // LINUX
		_threads[0] = pthread_create(&_threadId[0],NULL,&listenThread,NULL);
		_threads[1] = pthread_create(&_threadId[1],NULL,&connThread,NULL);
		_threads[2] = pthread_create(&_threadId[2],NULL,&processThread,NULL);
#endif
	}
}

ThreadManager::~ThreadManager()
{
	// Server exiting... Close shop and empty queues
	_shutdown = true;
	clear(_connQueue);
	clear(_actQueue);
	delete server;
	std::cout<< "Please wait while threads clean up..." << std::endl << std::endl;
	int c = _threadCount+1, t = 0;
	while(_threadCount != 0)
	{
		if(_threadCount < c)
		{
			std::cout<< "Attempting to close thread "<< _threadCount << " silently..."<< std::endl;
			c--;
		}
		if(t > 500)
		{
			std::cout<< "Force closing thread "<< _threadCount << "..."<< std::endl;
			_threadCount--;
			t = -1;
		}
		t++;
	}
}

int ThreadManager::getThreadCount()
{
	return _threadCount;
}

std::string ThreadManager::getError()
{
	return _err;
}

void ThreadManager::incrementThreadCount()
{
#ifdef _WIN32
	DWORD dwCount = 0, dwWait;
	while(dwCount < 20)
	{
		dwWait = WaitForSingleObject(_cMutex,INFINITE);
		switch(dwWait)
		{
			case WAIT_OBJECT_0:
				_threadCount++;
				if(!ReleaseMutex(_cMutex))
					_err = "Could not release mutex!";
				dwCount = 20;
			break;
			case WAIT_ABANDONED:
				_err = "Abandoned mutex!";
			break;
		}
	}
#else
	pthread_mutex_lock(&_cMutex);
	_threadCount++;
	pthread_mutex_unlock(&_cMutex);
#endif
}

void ThreadManager::decrementThreadCount()
{
#ifdef _WIN32 // Windows is a little bit more verbose than LINUX xD
	DWORD dwCount = 0, dwWait;
	while(dwCount < 20)
	{
		dwWait = WaitForSingleObject(_cMutex,INFINITE);
		switch(dwWait)
		{
			case WAIT_OBJECT_0:
				_threadCount--;
				if(!ReleaseMutex(_cMutex))
					_err = "Could not release mutex!";
				dwCount = 20;
			break;
			case WAIT_ABANDONED:
				_err = "Abandoned mutex!";
			break;
		}
	}
#else
	pthread_mutex_lock(&_cMutex);
	_threadCount--;
	pthread_mutex_unlock(&_cMutex);
#endif
}

// Thread Routines
/* Listen for incoming connections and send them to the queue */
T_PROC ThreadManager::listenThread(void* lParam)
{
	incrementThreadCount();
	int r = 0;
	std::cout<< "Successfully listening for clients on "<< server->getAddr() << " on port "<< server->getPort() << std::endl;
	while(!_shutdown)
	{
#ifdef _WIN32
		WaitForSingleObject(_acceptSem,INFINITE); // If we don't catch the semaphore we will have CPU issues.. wait indefinitely
#else
		// Linux pick up
#endif
		if(!server->isFull() && !_shutdown)
		{
			r = server->acceptClient(); // Get socket number - this blocks until incoming client is found
			_connQueue.push(r); // Add member to the stack
#ifdef _WIN32
			ReleaseSemaphore(_acceptSem,1,NULL);
#else
			// Linux release
#endif
		}
		Sleep(250); // Sleep 250 ms
	}

#ifdef _WIN32 // _shutdown == true - let's kill it
	CloseHandle(_acceptSem); // Destroy this thing so we're not blocking other threads from cleaning up
#else
	sem_destroy(&_acceptSem);
#endif

	// Loop ended? Thread dies...
	decrementThreadCount(); // Decrement
#ifdef _WIN32
	_endthread();
#else
	pthread_exit(0);
#endif
}

/* Send welcome response to the next client in line */
T_PROC ThreadManager::connThread(void* lParam)
{
	incrementThreadCount();
	int curr = -1;
	while(!_shutdown)
	{
#ifdef _WIN32 // Block this with a semaphore
		WaitForSingleObject(_acceptSem,INFINITE);
		// Signaled, now lose it so our parent thread can pick it back up
		ReleaseSemaphore(_acceptSem,1,NULL);
#else
		sem_wait(&_acceptSem);
		sem_post(&_acceptSem);
#endif
		if(!_connQueue.empty() && !_shutdown) // If semaphore released on shutdown, make sure we don't run through this again
		{
			curr = _connQueue.front();
			if(curr != -1)
			{
				server->writeSocket(curr,"Connected!\r\nWelcome to a server which can run on Windows and Linux!\r\n");
				_connQueue.pop();
				std::cout<< "Client connected from address: "<< server->getClientAddr(curr) << std::endl;
			}
		} else if(!_shutdown)
			curr = -1;
		Sleep(500);
	}
	decrementThreadCount();
#ifdef _WIN32
	_endthread();
#else
	pthread_exit(0);
#endif
}

T_PROC ThreadManager::processThread(void* lParam)
{
	incrementThreadCount();
	T_TYPE threadId = 0;
	while(!_shutdown)
	{
		_actQueue = server->pollRes(); // Check for new requests
		while(!_actQueue.empty() && !_shutdown) // Old requests before we check for new ones
		{
			if(_threadCount < MAX_THREAD_COUNT)
			{
#ifdef _WIN32
				_beginthread(userThread,0,(void*)_actQueue.front());
#else
				pthread_create(&threadId,NULL,&userThread,(void*)_actQueue.front());
#endif
				_actQueue.pop();
			} else
				Sleep(100); // Sleep 100 ms to wait for another spot
		}
	}
	decrementThreadCount();
#ifdef _WIN32
	_endthread();
#else
	pthread_exit(0);
#endif
}

T_PROC ThreadManager::userThread(void* lParam)
{
	incrementThreadCount();
	int i = (int)lParam, res = 0;
	char buf[257];

#ifdef _WIN32
	res = recv(server->getSocket(i),buf,256,0);
	buf[sizeof(buf)-res] = '\0';
#else
	res = read(server->getSocket(i),buf,256);
#endif
	if(res == 0 && server->getSocket(i) != -1) // Client exit - make sure we don't send this message multiple times if already exitde
	{
		std::cout<< "Client exiting..."<< std::endl << std::endl;
		server->clientExit(i);
	} else if(!_shutdown) { // If we're shutting down, just discared the messages...
		std::cout<< "From client "<< server->getClientAddr(i) << ": "<< buf << std::endl;
	}
	decrementThreadCount();
#ifdef _WIN32
	_endthread();
#else
	pthread_exit(0);
#endif
}
