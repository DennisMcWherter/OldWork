/**
 * GameManagerImpl.h
 * Implementation of the GameManager
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
 * Last Update: 23 June 2011
 */

#ifndef __MICROFPS_GAMEMANAGERIMPL_H_
#define __MICROFPS_GAMEMANAGERIMPL_H_

#include "../Managers/GameManager.h"
#include "RenderManagerImpl.h"
#include "StateManagerImpl.h"
#include "PhysicsManagerImpl.h"
#include "PlayerManagerImpl.h"
#include "GUIManagerImpl.h"
#include "EventManagerImpl.h"

namespace MicroFPS
{
	/**
	 * GameManagerImpl
	 * Implementation of the Game Manager
	 */
	class GameManagerImpl : public GameManager
	{
	public:
		/**
		 * GameManagerImpl()
		 * General Constructor
		 */
		GameManagerImpl(stringc windowTitle);

		/**
		 * ~GameManagerImpl()
		 * Standard virtual destructor
		 */
		virtual ~GameManagerImpl();

		/**
		 * start()
		 * Initializes the game loop
		 * @return void
		 */
		virtual void start();

		/**
		 * getRenderManager()
		 * Get the render manager
		 */
		virtual RenderManager * getRenderManager() const;

		/**
		 * getStateManager
		 * Retrieve the state manager
		 */
		virtual StateManager * getStateManager() const;

		/**
		 * getPhysicsManager
		 * Retrieve physics manager
		 */
		virtual PhysicsManager * getPhysicsManager() const;

		/**
		 * getPlayerManager
		 * Retrieve player manager
		 */
		virtual PlayerManager * getPlayerManager() const;

		/**
		 * getGUIManager
		 * get GUI manager
		 */
		virtual GUIManager * getGUIManager() const;

		/**
		 * getEventManager
		 * get the event manager for event handlers
		 */
		virtual EventManager * getEventManager() const;

		/**
		 * destroy
		 * Destroy the current object
		 */
		virtual void destroy();

	private:
		RenderManager * rmgr;
		EventManager * emgr;
		StateManager * stmgr;
		PhysicsManager * pmgr;
		GUIManager * gmgr;
		PlayerManager * player;
		stringc title;
	};
}

#endif // __MICROFPS_GAMEMANAGER_H_
