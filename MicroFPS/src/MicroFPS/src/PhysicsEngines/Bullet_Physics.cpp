/**
 * Bullet_Physics.cpp
 * The bullet connector
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
 * Last Update: 4 July 2011
 */

#include "Bullet_Physics.h"

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	Bullet_Physics::Bullet_Physics()
		: lastStep(0)
	{
		try
		{
			// Use btSoftRigidDynamicsWorld
			//world = NULL;// new btDiscreteDynamicsWorld(NULL, NULL, NULL, NULL);
			config = new btSoftBodyRigidBodyCollisionConfiguration;
			dispatcher = new btCollisionDispatcher(config);
			bphase = new btDbvtBroadphase;
			solver = new btSequentialImpulseConstraintSolver;
			world = new btSoftRigidDynamicsWorld(dispatcher, bphase, solver, config);

			// Setup softbodyworldinfo
			worldinfo.m_broadphase = bphase;
			worldinfo.m_gravity.setValue(0,-9.81,0);

			worldinfo.m_sparsesdf.Initialize();
			worldinfo.m_gravity.setValue(0,-9.81,0);
			worldinfo.air_density = (btScalar)(1.17);
			worldinfo.water_density = (btScalar)(1.0);
			worldinfo.water_offset = 0;
			worldinfo.water_normal = btVector3(0,0,0);
		} catch(const std::runtime_error& e) {
			throw e;
		}
		//if(world == NULL)
			//throw std::runtime_error("Could not initialize physics world!");
	}

	/**
	 * Destructor
	 */
	Bullet_Physics::~Bullet_Physics()
	{
		if(world)
			delete world;
		if(solver)
			delete solver;
		if(bphase)
			delete bphase;
		if(dispatcher)
			delete dispatcher;
		if(config)
			delete config;
	}

	/**
	 * getWorld
	 * Get the physics world
	 */
	physicsworld * Bullet_Physics::getWorld() const
	{
		return world;
	}

	/**
	 * addCollisionObject
	 */
	void Bullet_Physics::addCollisionObject(colobj * object, const std::string& name)
	{
		if(object) // Don't do anything to NULL objects
			objects.insert(name, object);
	}

	/**
	 * updateCollisions
	 */
	void Bullet_Physics::updateCollisions(u32 time)
	{
		// grep: iterate through all items and update their specific
		//	timestep and affectors
	}

	/**
	 * updateTimeStep
	 */
	inline void Bullet_Physics::updateTimeStep(u32 time)
	{
		u32 delta = lastStep-time;
		world->stepSimulation(delta*0.001f, 10); // 10 substeps...
		lastStep = time;
	}
}
