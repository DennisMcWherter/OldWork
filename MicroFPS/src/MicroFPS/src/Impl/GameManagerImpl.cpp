/**
 * GameManagerImpl.cpp
 * GameManager Implementation
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

#include "GameManagerImpl.h"

namespace MicroFPS
{
	/**
	 * GameManagerImpl()
	 * Constructor
	 */
	GameManagerImpl::GameManagerImpl(stringc windowTitle)
		: rmgr(0), stmgr(0), pmgr(0), player(0), title(windowTitle)
	{
		std::cout<< "MicroFPS Gaming Framework v0.1.0" << std::endl;
		try
		{
			rmgr   = new RenderManagerImpl;
			emgr   = new EventManagerImpl(getRenderManager()->getRenderDevice());
			stmgr  = new StateManagerImpl(getRenderManager()->getRenderDevice());
			gmgr   = new GUIManagerImpl;
			pmgr   = new PhysicsManagerImpl(getRenderManager()->getRenderDevice());
			player = new PlayerManagerImpl;
		} catch(const std::runtime_error & e) {
			throw e;
		}
		if(rmgr == NULL)
			throw std::runtime_error("Could not initialize render manager!");
		if(emgr == NULL)
			throw std::runtime_error("Could not initialize event manager!");
		if(stmgr == NULL)
			throw std::runtime_error("Could not initialize state manager!");
		if(gmgr == NULL)
			throw std::runtime_error("Could not initialize GUI manager!");
		if(pmgr == NULL)
			throw std::runtime_error("Could not initialize physics manager!");
		if(player == NULL)
			throw std::runtime_error("Could not initialize player manager!");
	}

	/**
	 * ~GameManagerImpl()
	 * Destructor
	 */
	GameManagerImpl::~GameManagerImpl()
	{
		// Destroy stuff
		if(player)
			delete player;
		if(gmgr)
			delete gmgr;
		if(pmgr)
			delete pmgr;
		if(stmgr)
			delete stmgr;
		if(emgr)
			delete emgr;
		if(rmgr)
			delete rmgr;
	}

	/**
	 * start()
	 * Initialize game loop
	 */
	void GameManagerImpl::start()
	{
		// Grab our engine's loop method
		// What we will want to do here then, is pass the current
		// GameState* to the loop so that it can run any necessary
		// functions in the loop (i.e. physics, etc.)
		while(rmgr->loop())
			rmgr->gameLoop(stmgr->getCurrentState());
	}

	/**
	 * destroy
	 */
	void GameManagerImpl::destroy()
	{
		delete this;
	}

	/**
	 * getRenderManager
	 */
	RenderManager * GameManagerImpl::getRenderManager() const
	{
		return rmgr;
	}

	/**
	 * getStateManager
	 */
	StateManager * GameManagerImpl::getStateManager() const
	{
		return stmgr;
	}

	/**
	 * getPhysicsManager
	 */
	PhysicsManager * GameManagerImpl::getPhysicsManager() const
	{
		return pmgr;
	}

	/**
	 * getPlayerManager
	 */
	PlayerManager * GameManagerImpl::getPlayerManager() const
	{
		return player;
	}

	/**
	 * getGUIManager
	 */
	GUIManager * GameManagerImpl::getGUIManager() const
	{
		return gmgr;
	}

	/**
	 * getEventManager
	 */
	EventManager * GameManagerImpl::getEventManager() const
	{
		return emgr;
	}

	/**
	 * createGameManager()
	 * Create a new game manager
	 */
	GameMgr createGameManager(stringc windowTitle)
	{
		return new GameManagerImpl(windowTitle);
	}
}
