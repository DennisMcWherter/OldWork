/**
 * smartPointer.h
 *
 * Simple smart pointer class
 *
 * Author: Dennis J. McWherter, Jr.
 * 8 Mar 2011
 */

#ifndef __SMART_POINTER_H__
#define __SMART_POINTER_H__

template <class T>
class smartPointer
{
public:
	// Constructors
	smartPointer() : _ptr(new T), _isPointer(true){}
	smartPointer(T obj);
	smartPointer(const smartPointer<T>& copy);
	smartPointer(const T*& copy);

	~smartPointer();

	// Pointer behavior
	T* operator->();
	T& operator*();
	T& operator=(const smartPointer<T>& rhs);
	T& operator=(const T& rhs);
	T* operator&();

	// Destroy pointer
	void free();
	void allocate();
	void allocate(const smartPointer<T>& copy);
	void allocate(T obj);
	void allocate(const T*& copy);

private:
	T* _ptr;
	bool _isPointer;
};

#include "smartPointer.cpp"
#endif
