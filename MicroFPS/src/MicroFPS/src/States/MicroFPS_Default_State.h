/**
 * MicroFPS_Default_State.h
 * Default blank state
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

#ifndef __MICROFPS_DEFAULT_STATE_H_
#define __MICROFPS_DEFAULT_STATE_H_

#include "GameState.h"

namespace MicroFPS
{
	class MicroFPS_Default_State : public GameState
	{
	public:
		/**
		 * Connstructor
		 */
		MicroFPS_Default_State(renderer dev) : device(dev), smgr(dev->getSceneManager()->createNewSceneManager()),
			type(MENU) {}

		/**
		 * Destructor
		 */
		virtual ~MicroFPS_Default_State(){ if(smgr) smgr->drop(); }

		/**
		 * criticalLoop()
		 */
		virtual inline void criticalLoop(){}

		/**
		 * gameLoop
		 */
		virtual inline void gameLoop(){}

		/**
		 * change
		 */
		virtual void change(){}

		/**
		 * leave
		 */
		virtual void leave(){}

		/**
		 * getSceneManager
		 */
		virtual scenemgr getSceneManager() const
		{
#ifdef USE_IRRLICHT_ENGINE
			return smgr;
#endif
			return 0; // Should never hit this - this _will_ crash
		}

		virtual GUI* getGUI() const { return 0; }
	private:
		renderer device;
		scenemgr smgr;
		STATE_TYPE type;
	};
}

#endif // __MICROFPS_DEFAULT_STATE_H_
