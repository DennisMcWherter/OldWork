/**
 * StateManager.h
 * Handles state management
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

#ifndef __MICROFPS_STATEMANAGER_H_
#define __MICROFPS_STATEMANAGER_H_

#include "../universal.h"
#include "../States/GameState.h"
#include "../GUI/GeneralMenu.h"

namespace MicroFPS
{

	/**
	 * StateManager
	 * Abstract class for state management
	 */
	class StateManager
	{
	public:
		/**
		 * Constructor
		 */
		StateManager(){}

		/**
		 * Destructor
		 */
		virtual ~StateManager(){}

		/**
		 * getCurrentState
		 * Get the current game state
		 */
		virtual GameState * getCurrentState() const = 0;

		/**
		 * setCurrentState
		 * Change the game state
		 */
		virtual void setCurrentState(std::string state) = 0;

		/**
		 * addState
		 * Add a new state to
		 * the state manager
		 */
		virtual void addState(std::string name, GameState * state) = 0;

		/**
		 * removeState
		 * Remove a particular state from the state manager
		 */
		virtual void removeState(std::string state) = 0;

		/**
		 * getGUI
		 * Get GUI pointer
		 */
		virtual GUI* getGUI() const = 0;
	};
}

#endif // __MICROFPS_STATEMANAGER_H_
