/**
 * StringHash.h
 * Implementation of string hash
 *
 * Copyright (c) 2011 Dennis J. McWherter, Jr.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *   1. The origin of this software must not be misrepresented; you must not
 *   claim that you wrote the original software. If you use this software
 *   in a product, an acknowledgment in the product documentation would be
 *   appreciated but is not required.
 *
 *   2. Altered source versions must be plainly marked as such, and must not be
 *   misrepresented as being the original software.
 *
 *   3. This notice may not be removed or altered from any source
 *   distribution.
 *
 * Last Update: 20 June 2011
 */

namespace MicroFPS
{
namespace core
{
	/**
	 * Constructor
	 */
	template<class T>
	Array<T>::Array()
		: count(0), size(16)
	{
		try
		{
			table = new std::list<std::pair<std::string, T> >[size];
		} catch(const std::runtime_error& e) {
			throw e;
		}
		if(table == NULL)
			throw std::runtime_error("Could not initialize array!");
	}

	/**
	 * Destructor
	 */
	template<class T>
	Array<T>::~Array()
	{
		cleanupPtrs<T>::destroy(table, size);
		delete [] table; // Clean up
	}

	/**
	 * Copy Ctor
	 */
	template<class T>
	Array<T>::Array(const Array<T>& arr)
	{
		table = new std::list<std::pair<std::string, T> >[arr.size];
		size  = arr.size;
		count = arr.count;
	}

	/**
	 * Assignment operator
	 */
	template<class T>
	Array<T> & Array<T>::operator=(const Array<T>& rhs)
	{
		if(this != &rhs)
		{
			cleanupPtrs<T>::destroy(table, size);
			delete [] table;
			table = new std::list<std::pair<std::string, T> >[rhs.size];
			for(u32 i=0;i<rhs.size;++i)
				table[i] = rhs.table[i];
			size  = rhs.size;
			count = rhs.count;
		}
		return *this;
	}

	/**
	 * getSize
	 * get number of elements
	 */
	template<class T>
	u32 Array<T>::getSize() const
	{
		return size;
	}

	/**
	 * operator[]
	 */
	template<class T>
	const T& Array<T>::operator[](const std::string& key) const
	{
		return find(key);
	}

	/**
	 * find
	 */
	template<class T>
	const T& Array<T>::find(const std::string& key) const
	{
		u32 index = hash(key,size);
		typename std::list<std::pair<std::string,T> >::iterator it;
		for(it=table[index].begin();it!=table[index].end();++it)
			if(it->first == key)
				return it->second;
		return def.value; // Default type
	}

	/**
	 * insert
	 */
	template<class T>
	void Array<T>::insert(const std::string& key, const T& val)
	{
		// Make 0.8 our alpha bit
		if((double)count/size >= 0.8)
			resize(); // Rehash the table and make more room
		if(keyExists(key))
			remove(key); // We are going to overwrite the old key
		table[hash(key,size)].push_front(std::pair<std::string, T>(key,val));
		count++;
	}

	/**
	 * remove
	 */
	template<class T>
	void Array<T>::remove(const std::string& key)
	{
		u32 index = hash(key,size);
		// GCC is tempermental about typename prefix
		typename std::list<std::pair<std::string,T> >::iterator it;
		for(it=table[index].begin();it!=table[index].end();++it)
			if(it->first == key)
			{
				cleanupPtrs<T>::remove(it->second);
				table[index].erase(it);
				count--;
				break;
			}
	}

	/**
	 * keyExists
	 */
	template<class T>
	bool Array<T>::keyExists(const std::string& key) const
	{
		u32 index = hash(key,size);
		typename std::list<std::pair<std::string,T> >::iterator it;
		for(it=table[index].begin();it!=table[index].end();++it)
			if(it->first == key)
				return true;
		return false;
	}

	/**
	 * clear
	 */
	template<class T>
	void Array<T>::clear()
	{
		cleanupPtrs<T>::destroy(table, size);
		delete [] table;
		size = 16;
		count = 0;
		table = new std::list<std::pair<std::string, T> >[16];
	}

	/**
	 * empty
	 */
	template<class T>
	bool Array<T>::empty() const
	{
		return count == 0;
	}

	/**
	 * resize
	 */
	template<class T>
	void Array<T>::resize()
	{
		std::list<std::pair<std::string, T> > * tmp;
		tmp = new std::list<std::pair<std::string, T> >[size*2];
		for(u32 i=0;i<size;++i)
		{
			typename std::list<std::pair<std::string, T> >::iterator it;
			for(it=table[i].begin();it!=table[i].end();++it)
				tmp[hash(it->first,size<<1)].push_front(std::pair<std::string, T>(it->first, it->second));
		}
		delete [] table;
		size <<= 1;
		table = tmp;
	}

	/**
	 * cleanupPtrs
	 */
	template<class T> template<class TX>
	void Array<T>::cleanupPtrs<TX*>::destroy(std::list<std::pair<std::string,TX*> > *& table, u32 size)
	{
		for(u32 i=0;i<size;++i)
		{
			typename std::list<std::pair<std::string,T> >::iterator it;
			for(it=table[i].begin();it!=table[i].end();++it)
				remove(it->second);
		}
	}

	template<class T> template<class TX>
	void Array<T>::cleanupPtrs<TX*>::remove(TX*& item)
	{
		delete item;
		item = 0;
	}
}
}

