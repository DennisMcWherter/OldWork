/**
 * WeaponManagerImpl.cpp
 * WeaponManager Implementation
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

#ifndef __MICROFPS_WEAPONMANAGERIMPL_H_
#define __MICROFPS_WEAPONMANAGERIMPL_H_

#include <vector>
#include "../Managers/WeaponManager.h"

namespace MicroFPS
{
	/**
	 * WeaponManagerImpl
	 * Default weapon manager
	 */
	class WeaponManagerImpl : public WeaponManager
	{
	public:
		/**
		 * Constructor
		 */
		WeaponManagerImpl();

		/**
		 * Destructor
		 */
		virtual ~WeaponManagerImpl();

		/**
		 * getCurrentWeapon
		 * @return Weapon * - pointer to the current weapon
		 */
		virtual Weapon * getCurrentWeapon() const;

		/**
		 * addWeapon
		 * Add a new weapon
		 */
		virtual void addWeapon(std::string id, Weapon* weaponPtr);

		/**
		 * dropCurrentWeapon
		 * Get rid of the current weapon
		 */
		virtual void dropCurrentWeapon();

		/**
		 * setCurrentWeapon
		 * Change your weapon
		 */
		virtual void setCurrentWeapon(std::string id);
	private:
		std::string current, last;
		MicroFPS::core::Array<Weapon*> weapons;
	};
}

#endif // __MICROFPS_WEAPONMANAGERIMPL_H_
