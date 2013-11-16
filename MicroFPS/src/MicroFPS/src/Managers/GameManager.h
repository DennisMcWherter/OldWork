/**
 * GameManager.h
 * Essentially the core of the system - the glue to the entire thing
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

#ifndef __MICROFPS_GAMEMANAGER_H_
#define __MICROFPS_GAMEMANAGER_H_

#include "../universal.h"
#include "RenderManager.h"
#include "StateManager.h"
#include "PhysicsManager.h"
#include "PlayerManager.h"
#include "GUIManager.h"
#include "EventManager.h"

namespace MicroFPS
{
	/**
	 * GameManager
	 * The glue to the entire system
	 */
	class GameManager
	{
	public:

		/**
		 * GameManager()
		 * General default constructor
		 */
		GameManager(){}

		/**
		 * ~GameManager()
		 * Virtual destructor
		 * we're done
		 */
		virtual ~GameManager(){}

		/**
		 * start
		 * The function which will initialize the game loop
		 */
		virtual void start() = 0;

		/**
		 * getRenderManager()
		 * Get the render manager
		 */
		virtual RenderManager * getRenderManager() const = 0;

		/**
		 * getStateManager()
		 * Get the state manager
		 */
		virtual StateManager * getStateManager() const = 0;

		/**
		 * getPhysicsManager
		 * Retrieve physics manager
		 */
		virtual PhysicsManager * getPhysicsManager() const = 0;

		/**
		 * getPlayerManager
		 * Retrieve player manager
		 */
		virtual PlayerManager * getPlayerManager() const = 0;

		/**
		 * getGUIManager
		 */
		virtual GUIManager * getGUIManager() const = 0;

		/**
		 * getEventManager
		 * get the event manager for event handlers
		 */
		virtual EventManager * getEventManager() const = 0;

		/**
		 * destroy
		 * Destroy the current object
		 */
		virtual void destroy() = 0;
	};

	// Define a method to create game manager
	typedef GameManager * GameMgr;
	GameMgr MICROFPSAPI createGameManager(stringc windowTitle="Game");
}
#endif // __MICROFPS_GAMEMAANGER_H_
