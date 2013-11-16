/**
 * Player.h
 * Player base class
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
 * Last Update: 24 July 2011
 */

#ifndef __MICROFPS_PLAYER_H_
#define __MICROFPS_PLAYER_H_

#include "../universal.h"
#include "../Managers/WeaponManager.h"

namespace MicroFPS
{
	/**
	 * Player
	 * Abstract base class for player
	 */
	class Player
	{
	public:
		/**
		 * Constructor
		 */
		Player(){}

		/**
		 * Destructor
		 */
		virtual ~Player(){}

		/**
		 * getHealth
		 */
		virtual s16 getHealth() const = 0; // Will you need more than 15-bits for health? (1-bit lost for sign)
										// It's the equivalent to 0x7FFF or 32,767 = quite a bit

		/**
		 * getWeapon
		 * @return Weapon* - current weapon
		 */
		virtual Weapon * getWeapon() const = 0;

		/**
		 * addWeapon
		 * Add a new weapon
		 */
		virtual void addWeapon(std::string id, Weapon* weaponPtr) = 0;

		/**
		 * getWeaponManager
		 * @return WeaponManager* - curent weapon manager
		 */
		virtual WeaponManager * getWeaponManager() const = 0;

		/**
		 * setWeaponManager
		 * @param WeaponManager * mgr - weapon manager
		 *	to change to - note that this will
		 *  _DESTROY_ your current WeaponManager
		 *	if passed a valid new one
		 */
		virtual void setWeaponManager(WeaponManager * mgr) = 0;

		/**
		 * setHealth
		 * @param s16 health - set health
		 */
		virtual void setHealth(s16 health) = 0;

		/**
		 * decreaseHealth
		 * @param u16 amount - amount to decrease
		 *	health by
		 */
		virtual void decreaseHealth(u16 amount) = 0;

		/**
		 * addHealth
		 * @param u16 amount - amount to increase
		 *	health by
		 */
		virtual void addHealth(u16 amount) = 0;

		/**
		 * setCamera
		 * Set the player's current controlling camera
		 */
		virtual void setCamera(camera c) = 0;

		/**
		 * getCamera
		 * Get the player's controlling camera
		 */
		virtual camera getCamera() const = 0;

		/**
		 * getSceneManager
		 * get player's scene manager
		 */
		virtual scenemgr getSceneManager() const = 0;

		/**
		 * setSceneManager
		 * set player's scene manager
		 */
		virtual void setSceneManager(scenemgr sm) = 0;
	};
}

#endif // __MICROFPS_PLAYER_H_
