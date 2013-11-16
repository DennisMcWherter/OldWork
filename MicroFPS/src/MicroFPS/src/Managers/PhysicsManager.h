/**
 * PhysicsManager.h
 * Manager the physics
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

#ifndef __MICROFPS_PHYSICSMANAGER_H_
#define __MICROFPS_PHYSICSMANAGER_H_

#include "../universal.h"
#include "../PhysicsEngines/Physics.h"

namespace MicroFPS
{
	/**
	 * PhysicsManager
	 * Base class for physics manager
	 */
	class PhysicsManager
	{
	public:
		/**
		 * Constructor
		 */
		PhysicsManager(){}

		/**
		 * Destructor
		 */
		virtual ~PhysicsManager(){}

		/**
		 * getWorld()
		 * getPhysicsWorld
		 */
		virtual physicsworld * getWorld() const = 0;

		/**
		 * getPhysicsEngine()
		 * get the physics engine
		 */
		virtual Physics * getPhysicsEngine() const = 0;

		/**
		 * addCollisionObject
		 * Add a collision object to the scene
		 */
		virtual rigidbody* addCollisionObject(scenenode *node, Physics::COLLISION_TYPE type=Physics::BT_PLAYER) = 0;

		/**
		 * addCollisionMap
		 * Add a mesh to become the collision map
		 */
		virtual rigidbody* addCollisionMap(meshscenenode* node) = 0;

		/**
		 * updateCollisions
		 * Update all collisions
		 */
		virtual void updateCollisions() = 0;

		/**
		 * updateTimeStep
		 * Step through physics' world time
		 */
		virtual void updateTimeStep(u32 time) = 0;
	};
}

#endif // __MICROFPS_PHYSICSMANAGER_H_
