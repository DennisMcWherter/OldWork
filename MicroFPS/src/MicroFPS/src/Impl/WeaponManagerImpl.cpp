/**
 * WeaponManagerImpl.h
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

#include "WeaponManagerImpl.h"

using namespace std;

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	WeaponManagerImpl::WeaponManagerImpl()
		: current(""), last("")
	{
	}

	/**
	 * Destructor
	 */
	WeaponManagerImpl::~WeaponManagerImpl()
	{
		// Use array
	}

	/**
	 * getCurrentWeapon
	 */
	Weapon * WeaponManagerImpl::getCurrentWeapon() const
	{
		return weapons[current];
	}

	/**
	 * addWeapon
	 */
	void WeaponManagerImpl::addWeapon(std::string id, Weapon* weaponPtr)
	{
		weapons.insert(id, weaponPtr);
	}

	/**
	 * dropCurrentWeapon
	 */
	void WeaponManagerImpl::dropCurrentWeapon()
	{
		if(weapons.getSize() == 1) // Don't drop last weapon!
			return;
		weapons.remove(current); // The array will free the memory
		setCurrentWeapon(last);
	}

	/**
	 * setCurrentWeapon
	 */
	void WeaponManagerImpl::setCurrentWeapon(std::string id)
	{
		if(weapons[id] == 0) // Non-existant/null pointer - don't set
			return;
		current = id;
	}
}
