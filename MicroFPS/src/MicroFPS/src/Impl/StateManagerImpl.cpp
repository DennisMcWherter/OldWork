/**
 * StateManagerImpl.cpp
 * Handles state management implementation
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
 * Last Update: 22 June 2011
 */

#include "StateManagerImpl.h"
#include "../States/MicroFPS_Default_State.h"

/** Note: This is currently _simple_ state management. This will
	be improved in good time - it is important to realize with this
	NAIVE state manager that you can easily alter behavior of your
	program by inserting and removing states without keeping track
	(since this currently IS NOT) */
namespace MicroFPS
{
	/**
	 * Constructor
	 */
	StateManagerImpl::StateManagerImpl(renderer dev)
		: currState("MicroFPS_holder_state")
	{
		states.insert(currState, new MicroFPS_Default_State(dev)); // This prevents crashes
	}

	/**
	 * Destructor
	 */
	StateManagerImpl::~StateManagerImpl()
	{
		// The array will take care of the container memory :)
	}

	/**
	 * getCurrentState
	 * Get the current game state
	 */
	GameState * StateManagerImpl::getCurrentState() const
	{
		return states[currState];
	}
	
	/**
	 * setCurrentState
	 * Change the game state
	 */
	void StateManagerImpl::setCurrentState(std::string state)
	{
		if(state == currState || states[state] == 0) // current or NULL
			return;
		// Update the states to safely switch
		states[currState]->leave();
		currState = state;
		states[currState]->change();
	}

	/**
	 * addState
	 * Add a new state to
	 * the state manager
	 */
	void StateManagerImpl::addState(std::string name, GameState * state)
	{
		if(states.keyExists(name))
			return;
		states.insert(name,state);
	}

	/**
	 * removeState
	 * Remove a particular state from the state manager
	 */
	void StateManagerImpl::removeState(std::string state)
	{
		if(state != currState)
			states.remove(state);
	}

	/**
	 * getGUI
	 * Retrieve current gui object
	 */
	MicroFPS::GUI* StateManagerImpl::getGUI() const
	{
		return states[currState]->getGUI();
	}
}
