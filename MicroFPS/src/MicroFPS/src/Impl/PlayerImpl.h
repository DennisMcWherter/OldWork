/**
 * PlayerImpl.h
 * Player Implementation
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

#ifndef __MICROFPS_PLAYERIMPL_H_
#define __MICROFPS_PLAYERIMPL_H_

#include "../Managers/PhysicsManager.h"
#include "../Player/Player.h"

namespace MicroFPS
{
	/**
	 * PlayerImpl
	 * Implementation of Player Class
	 */
	class PlayerImpl : public Player
	{
	public:
		/**
		 * Constructor
		 */
		PlayerImpl();

		/**
		 * Destructor
		 */
		virtual ~PlayerImpl();

		/**
		 * getHealth
		 */
		virtual s16 getHealth() const; // Will you need more than 15-bits for health? (1-bit lost for sign)
										// It's the equivalent to 0x7FFF or 32,767 = quite a bit

		/**
		 * addWeapon
		 * Add a new weapon
		 */
		virtual void addWeapon(std::string id, Weapon* weaponPtr);

		/**
		 * getWeapon
		 * @return Weapon* - current weapon
		 */
		virtual Weapon * getWeapon() const;

		/**
		 * getWeaponManager
		 * @return WeaponManager* - curent weapon manager
		 */
		virtual WeaponManager * getWeaponManager() const;

		/**
		 * setWeaponManager
		 * @param WeaponManager * mgr - weapon manager
		 *	to change to - note that this will
		 *  _DESTROY_ your current WeaponManager
		 *	if passed a valid new one
		 */
		virtual void setWeaponManager(WeaponManager * mgr);

		/**
		 * setHealth
		 * @param s16 health - set health
		 */
		virtual void setHealth(s16 health);

		/**
		 * decreaseHealth
		 * @param u16 amount - amount to decrease
		 *	health by
		 */
		virtual void decreaseHealth(u16 amount);

		/**
		 * addHealth
		 * @param u16 amount - amount to increase
		 *	health by
		 */
		virtual void addHealth(u16 amount);

		/**
		 * setCamera
		 * Set the player's current controlling camera
		 */
		virtual void setCamera(camera c);

		/**
		 * getCamera
		 * Get the player's controlling camera
		 */
		virtual camera getCamera() const;

		/**
		 * getSceneManager
		 * get player's scene manager
		 */
		virtual scenemgr getSceneManager() const;

		/**
		 * setSceneManager
		 * set player's scene manager
		 */
		virtual void setSceneManager(scenemgr sm);

	private:
		s16 health;
		WeaponManager * weapons;
		scenemgr smgr;
		camera cam;
	};
}

#endif // __MICROFPS_PLAYERIMPL_H_
