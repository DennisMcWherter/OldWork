/**
 * StateManagerImpl.h
 * Handles implementation of state management
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
 * Last Update: 16 June 2011
 */

#ifndef __MICROFPS_STATEMANAGERIMPL_H_
#define __MICROFPS_STATEMANAGERIMPL_H_

#include <vector>
#include "../Managers/StateManager.h"
#include "../Core/Array.h"

namespace MicroFPS
{
	/**
	 * StateManagerImpl
	 * Implementation for state manager
	 */
	class StateManagerImpl : public StateManager
	{
	public:
		/**
		 * Constructor
		 */
		StateManagerImpl(renderer device);

		/**
		 * Destructor
		 */
		virtual ~StateManagerImpl();

		/**
		 * getCurrentState
		 * Get the current game state
		 */
		virtual GameState * getCurrentState() const;

		/**
		 * setCurrentState
		 * Change the game state
		 */
		virtual void setCurrentState(std::string state);

		/**
		 * addState
		 * Add a new state to
		 * the state manager
		 */
		virtual void addState(std::string name, GameState * state);

		/**
		 * removeState
		 * Remove a particular state from the state manager
		 */
		virtual void removeState(std::string state);

		/**
		 * getGUI
		 * get GUI object
		 */
		virtual GUI* getGUI() const;

	private:
		MicroFPS::core::Array<GameState*> states;
		std::string currState;
	};
}

#endif // __MICROFPS_STATEMANAGERIMPL_H_
