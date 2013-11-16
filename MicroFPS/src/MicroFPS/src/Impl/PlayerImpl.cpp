/**
 * PlayerImpl.cpp
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

#include "PlayerImpl.h"
#include "WeaponManagerImpl.h"

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	PlayerImpl::PlayerImpl()
		: health(100), weapons(new WeaponManagerImpl), smgr(0), cam(0)
	{
		// Don't forget to manually set
		//	scene manager and camera!
	}

	/**
	 * Destructor
	 */
	PlayerImpl::~PlayerImpl()
	{
		if(weapons)
			delete weapons;
	}

	/**
	 * getHealth
	 */
	s16 PlayerImpl::getHealth() const
	{
		return health;
	}

	/**
	 * setHealth
	 */
	void PlayerImpl::setHealth(s16 h)
	{
		health = h;
	}

	/**
	 * addHealth
	 */
	void PlayerImpl::addHealth(u16 amount)
	{
		health += amount;
	}

	/**
	 * decreaseHealth
	 */
	void PlayerImpl::decreaseHealth(u16 amount)
	{
		health -= amount;
	}

	/**
	 * getWeapon
	 */
	Weapon * PlayerImpl::getWeapon() const
	{
		return weapons->getCurrentWeapon();
	}

	/**
	 * addWeapon
	 */
	void PlayerImpl::addWeapon(std::string id, Weapon* weaponPtr)
	{
		if(weapons == 0)
			return;
		weapons->addWeapon(id, weaponPtr);
	}

	/**
	 * getWeaponManager
	 */
	WeaponManager * PlayerImpl::getWeaponManager() const
	{
		return weapons;
	}

	/**
	 * setWeaponManager
	 */
	void PlayerImpl::setWeaponManager(WeaponManager * mgr)
	{
		if(mgr == 0) // NULL ptr
			return;
		WeaponManager * tmp = weapons;
		weapons = mgr;
		delete tmp;
	}

	/**
	 * setCamera
	 */
	void PlayerImpl::setCamera(camera c)
	{
		if(c) // Make sure it's not NULL
			cam = c;
	}

	/**
	 * getCamera
	 */
	camera PlayerImpl::getCamera() const
	{
		return cam;
	}

	/**
	 * setSceneManager
	 */
	void PlayerImpl::setSceneManager(scenemgr sm)
	{
		if(sm)
			smgr = sm;
	}

	/**
	 * getSceneManager
	 */
	scenemgr PlayerImpl::getSceneManager() const
	{
		return smgr;
	}
}
