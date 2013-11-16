/**
 * PhysicsManagerImpl.h
 * Implementation of Physics Manager
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

#ifndef __MICROFPS_PHYSICSMANAGERIMPL_H_
#define __MICROFPS_PHYSICSMANAGERIMPL_H_

#include "../PhysicsEngines/Physics.h"
#include "../Managers/PhysicsManager.h"
#include <list>
#include <queue>

namespace MicroFPS
{
	class PhysicsManagerImpl : public PhysicsManager
	{
	public:
		/**
		 * Constructor
		 */
		PhysicsManagerImpl(renderer device);

		/**
		 * Destructor
		 */
		virtual ~PhysicsManagerImpl();

		/**
		 * getWorld()
		 */
		virtual physicsworld * getWorld() const;

		/**
		 * getPhysicsEngine()
		 */
		virtual Physics * getPhysicsEngine() const;

		/**
		 * addCollisionObject
		 */
		virtual rigidbody* addCollisionObject(scenenode* node, Physics::COLLISION_TYPE type=Physics::BT_PLAYER);

		/**
		 * addCollisionMap
		 */
		virtual rigidbody* addCollisionMap(meshscenenode *node);

		/**
		 * updateCollisions
		 */
		virtual void updateCollisions();

		/**
		 * updateTimeStep
		 */
		virtual void updateTimeStep(u32 time);
	private:

		// Some helper functions to cleanup and such
		u32 getTime() const;
		void destroy();
		void queueProcess();

		Physics * engine;
		renderer device;
		std::list<rigidbody*> collisions; // Hold all collisions to update
		std::queue<rigidbody*> colRemovals;
		mapshape * map;
	};
}

#endif // __MICROFPS_PHYSICSMANAGERIMPL_H_
