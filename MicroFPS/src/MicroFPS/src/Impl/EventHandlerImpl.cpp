/**
 * EventManagerImpl.cpp
 * Manager our Event handlers
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
 * Last Update: 23 June 2011
 */

#include "EventManagerImpl.h"
#include "../EventHandler/GenericHandler.h"

namespace MicroFPS
{
	/**
	 * Constructor
	 */
	EventManagerImpl::EventManagerImpl(renderer device)
		: genericHandler(new GenericHandler(device))
	{
	}

	/**
	 * Destructor
	 */
	EventManagerImpl::~EventManagerImpl()
	{
		if(genericHandler)
			delete genericHandler;
	}

	/**
	 * getHandler
	 */
	EventHandler * EventManagerImpl::getHandler(const std::string& name) const
	{
		return handlers[name];
	}

	/**
	 * addHandler
	 */
	EventHandler * EventManagerImpl::addHandler(const std::string& name, EventHandler * handler)
	{
		handlers.insert(name, handler);
		return handler;
	}

	/**
	 * removeHandler
	 */
	void EventManagerImpl::removeHandler(const std::string& name)
	{
		handlers.remove(name);
	}

	/**
	 * getGenericHandler
	 */
	EventHandler * EventManagerImpl::getGenericHandler() const
	{
		return genericHandler;
	}
}
