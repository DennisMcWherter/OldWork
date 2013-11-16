/**
 * Array.h
 * Associative array implementation based of hash table
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

#ifndef __MICROFPS_CORE_ARRAY_H_
#define __MICROFPS_CORE_ARRAY_H_

#include "HashTable.h"
#include "StringHash.h"
#include <string>
#include <list>
#include <utility>

namespace MicroFPS
{
namespace core
{
	/**
	 * Array
	 * Implementation of hash table
	 */
	template<class T>
	class Array : public HashTable<std::string,T>
	{
	public:
		/**
		 * Constructor
		 */
		Array();

		/**
		 * Destructor
		 */
		virtual ~Array();

		/**
		 * Copy constructor
		 */
		Array(const Array<T>& rhs);

		/**
		 * Assignment operator
		 */
		virtual Array<T>& operator=(const Array<T>& rhs);

		/**
		 * operator[]
		 * Access elements
		 */
		virtual const T & operator[](const std::string& key) const;

		/**
		 * find
		 * Access elements
		 */
		virtual const T & find(const std::string& key) const;

		/**
		 * getSize
		 * get number of elements
		 */
		virtual u32 getSize() const;

		/**
		 * keyExists
		 * Check if key exists
		 */
		virtual bool keyExists(const std::string & key) const;

		/**
		 * insert
		 * Add element to map
		 */
		virtual void insert(const std::string& key, const T& value);

		/**
		 * remove
		 * Remove an element from table
		 */
		virtual void remove(const std::string& key);

		/**
		 * clear
		 * Clear the map
		 */
		virtual void clear();

		/**
		 * empty
		 * Check if is empty
		 */
		virtual bool empty() const;

	private:
		/**
		 * resize
		 * Resize the table/rehash
		 */
		virtual void resize();

		/**
		 * Cleanup pointers
		 */
		template<class TX>
		struct cleanupPtrs
		{
			static void destroy(std::list<std::pair<std::string,TX> > *& table, u32 size){}
			static void remove(TX& item){}
		};

		template<class TX>
		struct cleanupPtrs<TX*>
		{
			static void destroy(std::list<std::pair<std::string,TX*> > *& table, u32 size);
			static void remove(TX*& item);
		};

		// Member variables
		// Default type
		template<class TX>
		struct defaultType{ defaultType() : value(TX()){} TX value; };
		template<class TX>
		struct defaultType<TX*>{ defaultType() : value(0){} TX* value; };

		u32 count, size; // Number of elements occupying the table and size of the table
		StringHash<T> hash;
		std::list<std::pair<std::string,T> > * table; // Bucket
		defaultType<T> def; // Default return
	};

}
}

// heh. templates
#include "Array.cpp"

#endif // __MICROFPS_CORE_ARRAY_H_
