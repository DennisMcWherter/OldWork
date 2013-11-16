/**
 * PlayerManager.cpp
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

#include "PlayerManagerImpl.h"
#include "PlayerImpl.h"

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	PlayerManagerImpl::PlayerManagerImpl()
		: player(new PlayerImpl)
	{
		if(player == NULL)
			throw std::runtime_error("Could not initialize player!");
	}

	/**
	 * Destructor
	 */
	PlayerManagerImpl::~PlayerManagerImpl()
	{
		if(player)
			delete player;
	}

	/**
	 * getPlayer
	 */
	Player * PlayerManagerImpl::getPlayer() const
	{
		return player;
	}

	/**
	 * setPlayer
	 */
	bool PlayerManagerImpl::setPlayer(Player * p)
	{
		if(p == NULL)
			return false;
		player = p;
		return true;
	}
}
