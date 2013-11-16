/**
 * smartPointer.cpp
 *
 * Simple smart pointer class
 *
 * Author: Dennis J. McWherter, Jr.
 * 8 Mar 2011
 */

template<class T>
smartPointer<T>::smartPointer(T obj)
{
	allocate(obj);
}

template <class T>
smartPointer<T>::smartPointer(const T*& copy)
{
	allocate(copy);
}

template <class T>
smartPointer<T>::smartPointer(const smartPointer<T>& copy)
{
	allocate(copy);
}

template <class T>
smartPointer<T>::~smartPointer()
{
	free();
}

template <class T>
T* smartPointer<T>::operator->()
{
	return _ptr;
}

template <class T>
T& smartPointer<T>::operator*()
{
	// Give some value so we don't de-reference null
	if(!_isPointer)
		allocate();
	return *_ptr;
}

template <class T>
T& smartPointer<T>::operator=(const smartPointer<T>& rhs)
{
	if(_ptr != rhs._ptr)
	{
		free();
		allocate(rhs);
	}
	return *_ptr;
}

template <class T>
T& smartPointer<T>::operator=(const T& rhs)
{
	if(_ptr != &rhs)
	{
		free();
		allocate(rhs);
	}
	return *_ptr;
}

template <class T>
T* smartPointer<T>::operator&()
{
	return (_isPointer) ? _ptr : NULL;
}

template <class T>
void smartPointer<T>::free()
{
	if(_isPointer)
	{
		delete _ptr;
		_isPointer = false;
	}
}

// Initialize a new pointer
template <class T>
void smartPointer<T>::allocate()
{
	if(!_isPointer)
	{
		_ptr = new T;
		_isPointer = true;
	}
}

template <class T>
void smartPointer<T>::allocate(const smartPointer<T>& rhs)
{
	if(!_isPointer)
	{
		_ptr = new T;
		*_ptr = *rhs._ptr;
		_isPointer = true;
	}
}

template <class T>
void smartPointer<T>::allocate(T obj)
{
	if(!_isPointer)
	{
		_ptr = new T;
		*_ptr = obj;
		_isPointer = true;
	}
}

template <class T>
void smartPointer<T>::allocate(const T*& copy)
{
	if(!_isPointer)
	{
		_ptr = new T;
		*_ptr = *copy;
		_isPointer = true;
	}
}
