/**
 * Hash.h
 * A core module for Hashing function base class
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

#ifndef __MICROFPS_CORE_HASH_H_
#define __MICROFPS_CORE_HASH_H_

#include "../universal.h"

namespace MicroFPS
{
namespace core
{
	/**
	 * Hash
	 * Abstract base class for hashing functions
	 */
	template<class K,class T>
	class Hash
	{
	public:
		/**
		 * Constructor
		 */
		Hash(){}

		/**
		 * Destructor
		 */
		virtual ~Hash(){}

		/**
		 * operator()
		 * functor to execute hash function
		 * @return u32 hash value
		 */
		virtual u32 operator()(const K& key, u32 size) const = 0;
	};
}
}

#endif // __MICROFPS_CORE_HASH_H_
