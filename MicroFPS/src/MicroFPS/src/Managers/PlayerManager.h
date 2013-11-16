/**
 * PlayerManager.h
 * Player Manager
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

#ifndef __MICROFPS_PLAYERMANAGER_H_
#define __MICROFPS_PLAYERMANAGER_H_

#include "../universal.h"
#include "../Player/Player.h"

namespace MicroFPS
{
	/**
	 * PlayerManager Base class
	 * Perhaps can be extended for network play?
	 */
	class PlayerManager
	{
	public:
		/**
		 * Constructor
		 */
		PlayerManager(){}

		/**
		 * Destructor
		 */
		virtual ~PlayerManager(){}

		/**
		 * getPlayer
		 * @return Player * - pointer to current player node
		 */
		virtual Player * getPlayer() const = 0;

		/**
		 * setPlayer
		 *	- This function will _DESTROY_ the current player
		 *		if the input is valid
		 * @param Player * - player to replace the current one
		 * @return bool - true if successful, false if not
		 */
		virtual bool setPlayer(Player * player) = 0;
	};
}

#endif // __MICROFPS_PLAYERMANAGER_H_
