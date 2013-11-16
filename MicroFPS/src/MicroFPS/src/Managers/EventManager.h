/**
 * EventManager.h
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

#ifndef __MICROFPS_EVENTMANAGER_H_
#define __MICROFPS_EVENTMANAGER_H_

#include "../EventHandler/EventHandler.h"

namespace MicroFPS
{
	/**
	 * EventManager
	 * Base class
	 */
	class EventManager
	{
	public:
		/**
		 * Constructor
		 */
		EventManager(){}

		/**
		 * Destructor
		 */
		virtual ~EventManager(){}

		/**
		 * getHandler
		 * get a specified handler
		 */
		virtual EventHandler * getHandler(const std::string& name) const = 0;

		/**
		 * addHandler
		 * Add a handler
		 */
		virtual EventHandler * addHandler(const std::string& name, EventHandler * handler) = 0;

		/**
		 * removeHandler
		 * Remove a handler
		 */
		virtual void removeHandler(const std::string& name) = 0;

		/**
		 * getGenericHandler
	     * get the generic handler
		 */
		virtual EventHandler * getGenericHandler() const = 0;
	};
}

#endif // __MICROFPS_EVENTHANDLER_H_
