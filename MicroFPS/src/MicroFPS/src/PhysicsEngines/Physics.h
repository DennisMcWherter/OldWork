/**
 * Physics.h
 * Base physics class
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
 * Last Update: 9 July 2011
 */

#ifndef __MICROFPS_PHYSICS_H_
#define __MICROFPS_PHYSICS_H_

#include "../universal.h"

namespace MicroFPS
{
	/**
	 * Physics
	 * Physics abstract base class
	 */
	class Physics
	{
	public:
		/**
		 * Collision Object Type Enum
		 * NOTE: This will be used later
		 *	when we have "createPlayer"
		 *	"createProjectile" functions, etc.
		 */
		enum COLLISION_TYPE
		{
			BT_PLAYER,
			BT_PROJECTILE
		};

		/**
		 * Constructor
		 */
		Physics(){}

		/**
		 * Destructor
		 */
		virtual ~Physics(){}

		/**
		 * getWorld
		 */
		virtual physicsworld * getWorld() const = 0;

		/**
		 * addCollisionObject
		 */
		virtual void addCollisionObject(colobj * object, const std::string& name) = 0;

		/**
		 * updateCollisions
		 */
		virtual void updateCollisions(u32 time) = 0;

		/**
		 * updateTimeStep
		 */
		virtual void updateTimeStep(u32 time) = 0;
	};
}

#endif // __MICROFPS_PHYSICS_H_
