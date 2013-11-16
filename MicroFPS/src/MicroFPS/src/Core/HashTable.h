/**
 * HashTable.h
 * Hash table base class
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
 * Last Update: 17 June 2011
 */

#ifndef __MICROFPS_CORE_HASHTABLE_H_
#define __MICROFPS_CORE_HASHTABLE_H_

#include "Hash.h"

namespace MicroFPS
{
namespace core
{
	/**
	 * HashTable
	 * Abstract base class for hash tables
	 */
	template<class K,class T>
	class HashTable
	{
	public:
		/**
		 * Constructor
		 */
		HashTable(){}

		/**
		 * Destructor
		 */
		virtual ~HashTable(){}

		/**
		 * operator[]
		 * Access elements
		 */
		virtual const T & operator[](const K& key) const = 0;

		/**
		 * find
		 * Access elements
		 */
		virtual const T & find(const K& key) const = 0;

		/**
		 * getSize
		 * get number of elements
		 */
		virtual u32 getSize() const = 0;

		/**
		 * keyExists
		 * Check if key exists
		 */
		virtual bool keyExists(const K& key) const = 0;

		/**
		 * insert
		 * Add element to map
		 */
		virtual void insert(const K& key, const T& value) = 0;

		/**
		 * remove
		 * Remove an element from table
		 */
		virtual void remove(const K& key) = 0;

		/**
		 * clear
		 * Clear the map
		 */
		virtual void clear() = 0;

		/**
		 * empty
		 * Check if is empty
		 */
		virtual bool empty() const = 0;
	private:
		/**
		 * resize
		 * Resize the table/rehash
		 */
		virtual void resize() = 0;
	};
}
}

#endif // __MICROFPS_CORE_HASHTABLE_H_
