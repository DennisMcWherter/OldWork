/**
 * Bullet_Physics.h
 * This is the bullet physics
 *   connector
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
 * Last Update: 5 July 2011
 */

#ifndef __MICROFPS_BULLET_PHYSICS_H_
#define __MICROFPS_BULLET_PHYSICS_H_

#include "Physics.h"

#include "../Core/Array.h"

namespace MicroFPS
{
	/**
	 * Bullet_Physics
	 * Bullet physics connector
	 */
	class Bullet_Physics : public Physics
	{
	public:
		/**
		 * Constructor
		 */
		Bullet_Physics();

		/**
		 * Destructor
		 */
		virtual ~Bullet_Physics();

		/**
		 * getWorld()
		 * get the physics world
		 */
		virtual physicsworld * getWorld() const;

		/**
		 * addCollisionObject
		 * Add an object to keep track
		 *	of in the bullet world
		 */
		virtual void addCollisionObject(colobj * object, const std::string& name);

		/**
		 * updateCollisions
		 * Update all Bullet world collisions
		 */
		virtual void updateCollisions(u32 time);

		/**
		 * updateTimeStep
		 * Step through simulation
		 */
		virtual inline void updateTimeStep(u32 time);

	private:
		u32 lastStep;
		btSoftBodyRigidBodyCollisionConfiguration * config;
		btCollisionDispatcher * dispatcher;
		btDbvtBroadphase * bphase;
		btSequentialImpulseConstraintSolver * solver;
		physicsworld * world;
		btSoftBodyWorldInfo worldinfo;
		core::Array<colobj*> objects;
	};
}

#endif // __MICROFPS_BULLET_PHYSICS_H_
