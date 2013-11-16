/**
 * PhysicsManagerImpl.cpp
 * Physics Manager implementation
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
 * Last Update: 10 July 2011
 */

#include "PhysicsManagerImpl.h"
#include "../PhysicsEngines/Bullet_Physics.h"

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	PhysicsManagerImpl::PhysicsManagerImpl(renderer dev)
		: engine(0), device(dev)
	{
		try
		{
#ifdef USE_BULLET_PHYSICS
			engine = new Bullet_Physics;
#endif
		} catch(const std::runtime_error& e) {
			throw e;
		}
		if(engine == NULL)
			throw std::runtime_error("Could not initialize physics engine.");
	}

	/**
	 * Destructor
	 */
	PhysicsManagerImpl::~PhysicsManagerImpl()
	{
		destroy();
		if(engine)
			delete engine;
	}

	/**
	 * destroy
	 */
	void PhysicsManagerImpl::destroy()
	{
		// Removal queue
		queueProcess();

		// Everything else
		std::list<rigidbody*>::iterator it;
		for(it=collisions.begin();it!=collisions.end();++it)
		{
			if(*it == 0)
				continue;
			scenenode* node = static_cast<scenenode*>((*it)->getUserPointer());
			// Irrlicht specific
			// Must we update ref count?
			if(node)
				node->drop();
			getWorld()->removeRigidBody(*it);
			delete *it;
			// No need to erase; it will clean itself up,
			//	we're only responsible for our pointers
		}

		if(map)
		{
			meshscenenode * n = static_cast<meshscenenode*>(map->getUserPointer());
			if(n)
				n->drop();
			delete map;
		}
	}

	/**
	 * getWorld()
	 * Get physics world
	 */
	physicsworld * PhysicsManagerImpl::getWorld() const
	{
		return engine->getWorld();
	}

	/**
	 * getPhysicsEngine
	 * Return a pointer to the engine
	 */
	Physics * PhysicsManagerImpl::getPhysicsEngine() const
	{
		return engine;
	}

	/** Convert vector type */
	btVector3 vector3dfToBtVector3(const irr::core::vector3df& v)
	{
		return btVector3(v.X, v.Y, v.Z);
	}

	/**
	 * addCollisionObject
	 */
	rigidbody* PhysicsManagerImpl::addCollisionObject(scenenode* node, Physics::COLLISION_TYPE type)
	{
		// Will probably abstract this later to the Bullet_Physics class
		// Bullet specific
		const irr::core::aabbox3df& box = node->getTransformedBoundingBox();
		const irr::core::vector3df& d = box.MaxEdge-box.getCenter();
		const f32 rad(d.getLength()*0.5f);

		btCollisionShape * shape = new btSphereShape(rad);

		// Init pos - Irrlicht specific
		btTransform trans;
		trans.setIdentity();
		trans.setOrigin(btVector3(0,10,0));

		// Default motion state
		btDefaultMotionState * motionstate = new btDefaultMotionState(trans);

		// Local Inertia
		btVector3 LocalInertia;
		shape->calculateLocalInertia(1.0f, LocalInertia);

		rigidbody * body = new rigidbody(1.0f, motionstate, shape, LocalInertia);

		// Setup
		body->setRestitution(-0.5f); // Try to avoid bouncing xD
		body->setFriction(1.0f);
		body->setDamping(0.2f, 0.1f);
		body->setActivationState(4); // Never disable
		body->setCollisionFlags(16); // Character flags
		body->setGravity(btVector3(0,-10,0));
		body->setUserPointer((void*)node); // Attach to node

		// Irrlicht specific (update ref count)
		node->grab();

		getWorld()->addRigidBody(body);

		collisions.push_back(body);
		return body;
	}

	/** Convert Irrlicht mesh to bullet triangle mesh - I will clean
		all of this up later since this is really hacky */
	btTriangleMesh * getTriangleMesh(meshscenenode * m)
	{
		if(m == 0) return 0;
		meshnode * mesh = m->getMesh();
		if(mesh == 0) return 0;
		irr::core::vector3df scale(m->getScale());
		btVector3 vertices[3];
		irr::video::S3DVertex* irrvert = 0;
		irr::video::S3DVertex2TCoords * irr2vert = 0;
		bool standard = true;

		btTriangleMesh * trimesh = new btTriangleMesh;

		for(u32 i=0;i<mesh->getMeshBufferCount();++i)
		{
			irr::scene::IMeshBuffer * mb = mesh->getMeshBuffer(i);
			if(mb->getVertexType() == irr::video::EVT_STANDARD)
				irrvert=(irr::video::S3DVertex*)mb->getVertices();
			else if(mb->getVertexType() == irr::video::EVT_2TCOORDS) {
				irr2vert=(irr::video::S3DVertex2TCoords*)mb->getVertices();
				standard = false;
			}

			if(irrvert == 0 && irr2vert == 0) // No mesh data?
				return 0;

			u16 * indices = mb->getIndices();
			s32 vCount    = mb->getVertexCount();
			for(u32 j=0;j<mb->getIndexCount();j+=3)
			{
				for(u32 k=0;k<3;++k)
				{
					s32 idx = indices[j+k];
					if(idx > vCount)
						break;
					vertices[k] = vector3dfToBtVector3(((standard) ? irrvert[idx].Pos : irr2vert[idx].Pos) * scale);
					//irr::core::vector3df tmp = ((standard) ? irrvert[idx].Pos : irr2vert[idx].Pos*scale);
					//vertices[k] = btVector3(tmp.X, tmp.Y, tmp.Z);
				}
				trimesh->addTriangle(vertices[0], vertices[1], vertices[2]);
			}
		}
		return trimesh;
	}

	/**
	 * addCollisionMap
	 */
	rigidbody* PhysicsManagerImpl::addCollisionMap(meshscenenode * node)
	{
		if(node == 0) return 0; // Avoid crashing here in the library
		// Bullet specific for now
		node->grab();
		btTriangleMesh * mesh = getTriangleMesh(node);

		if(mesh == 0) // Looks like there was no mesh data - or something went wrong?
		{
			node->drop();
			return 0;
		}

		map = new mapshape(mesh, false, true);

		// Init pos - Irrlicht specific
		btTransform trans;
		trans.setIdentity();
		//trans.setOrigin(vector3dfToBtVector3(node->getAbsolutePosition()));
		trans.setOrigin(btVector3(0,0,0));

		// Default motion state
		btDefaultMotionState * motionstate = new btDefaultMotionState(trans);

		// Local Inertia
		btVector3 LocalInertia(0,0,0);
//		map->calculateLocalInertia(0.0, LocalInertia);

		rigidbody * b = new rigidbody(0.0f, motionstate, map, LocalInertia);
		b->setUserPointer((void*)node);
		b->setGravity(btVector3(0,0,0));
		b->setCollisionFlags(1); // Static object
		getWorld()->addRigidBody(b);
		collisions.push_back(b);
		return b;
	}

	// Taken from Irrlicht page
	btVector3 quatToEuler(const btQuaternion & quat)
	{
		btVector3 ret;
		btScalar w = quat.getW(), x = quat.getX(), y = quat.getY(), z = quat.getZ();
		float ws = w*w, xs = x*x, ys = y*y, zs = z*z;
		ret.setX(atan2f(2.0f*(y*z+x*w), -xs-ys+zs+ws));
		ret.setY(asinf(-2.0f*(x*z-y*w)));
		ret.setZ(atan2f(2.0f*(x*y+z*w), xs-ys-zs+ws));
		ret *= irr::core::RADTODEG;
		return ret;
	}

	/**
	 * updateCollisions
	 */
	void PhysicsManagerImpl::updateCollisions()
	{
		// Should eventually be done using abstraction with
		//	"engine"
		std::list<rigidbody*>::iterator it;
		if(!collisions.empty())
		{
			for(it=collisions.begin();it!=collisions.end();++it)
			{
#ifdef USE_IRRLICHT_ENGINE
				rigidbody * obj = *it;
				if(obj == 0)
				{
					collisions.erase(it);
					it--;
					continue;
				}

				scenenode * node = static_cast<scenenode*>((*it)->getUserPointer());
				if(node)
				{
					// Bullet specific code
					// Position
					btVector3 p = obj->getCenterOfMassPosition();
					node->setPosition(irr::core::vector3df((f32)p[0], (f32)p[1], (f32)p[2]));

					// Rotation
					btVector3 e(quatToEuler(obj->getOrientation()));
					node->setRotation(irr::core::vector3df(e[0], e[1], e[2]));
				} else {
					colRemovals.push(*it);
				}
#endif
			}
		}

		// Removal queue
		queueProcess();
	}

	/**
	 * updateTimeStep
	 */
	void PhysicsManagerImpl::updateTimeStep(u32 time)
	{
		engine->updateTimeStep(time);
	}

	/**
	 * getTime
	 */
	u32 PhysicsManagerImpl::getTime() const
	{
		u32 time;
#ifdef USE_IRRLICHT_ENGINE
		time = device->getTimer()->getTime();
#endif
		return time;
	}

	/**
	 * queueProcess
	 */
	void PhysicsManagerImpl::queueProcess()
	{
		if(!colRemovals.empty()) // Don't try to process empty queue
		{
			for(u32 i=0;i<colRemovals.size();++i)
			{
				rigidbody* object = colRemovals.front();
				colRemovals.pop();
				if(object)
				{
					// Irrlicht specific delete
					scenenode * node = static_cast<scenenode*>(object->getUserPointer());
					if(node)
						node->drop();
					getWorld()->removeRigidBody(object);
					delete object;
				}
				i--;
			}
		}
	}
}
