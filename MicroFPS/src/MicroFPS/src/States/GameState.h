/**
 * GameState.h
 * Base class for game states
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
 * Last Update: 25 June 2011
 */

#ifndef __MICROFPS_GAMESTATE_H_
#define __MICROFPS_GAMESTATE_H_

#include "../universal.h"
#include "../GUI/GUI.h"

namespace MicroFPS
{
	/**
	 * GameState
	 * Determine what a GameState consists of
	 */
	class GameState
	{
	public:

		/**
		 * STATE_TYPE
		 * ENUM to determine type of
		 * state
		 */
		enum STATE_TYPE
		{
			LEVEL,
			MENU
		};

		/**
		 * Constructor
		 */
		GameState(){}

		/**
		 * Destructor
		 */
		virtual ~GameState(){}

		/**
		 * criticalLoop
		 * Determine what to add (if anything) to
		 * the predefined game loop (this happens during rendering)
		 *	- time critical stuff (don't put things here unless they need to be)
		 */
		virtual inline void criticalLoop() = 0;

		/**
		 * gameLoop
		 * The normal game loop (post scene render)
		 */
		virtual inline void gameLoop() = 0;

		/**
		 * change()
		 * Void function to simply prepare the
		 * state to be viewed
		 */
		virtual void change() = 0;

		/**
		 * leave()
		 * Prepare a scene to be left
		 */
		virtual void leave() = 0;

		/**
		 * getSceneManager
		 * get the scene manager for the state
		 */
		virtual scenemgr getSceneManager() const = 0;

		/**
		 * getGUI
		 * get GUI object
		 */
		virtual GUI* getGUI() const = 0;
	};
}

#endif // __MICROFPS_GAMESTATE_H_
