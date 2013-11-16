/**
 * GenericHandler.h
 * Generic event handler
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
 * Last Update: 24 June 2011
 */

#ifndef __MICROFPS_GENERICHANDLER_H_
#define __MICROFPS_GENERICHANDLER_H_

#include "EventHandler.h"

namespace MicroFPS
{
	/**
	 * GenericHandler
	 */
	class GenericHandler : public EventHandler
	{
	public:
		/**
		 * Constructor
		 */
		GenericHandler(renderer dev) : device(dev) {}

		/**
		 * Destructor
		 */
		virtual ~GenericHandler(){}

		/**
		 * OnGUIEvent
		 * Needed for GUI handling
		 */
#ifdef USE_CEGUI
		virtual bool operator()(const CEGUI::EventArgs& event){ return true; }
		virtual bool OnGUIEvent(const CEGUI::EventArgs& event){ return true; }
#endif // USE_CEGUI

		/**
		 * OnEvent
		 * Irrlicht virtual function
		 */
#ifdef USE_IRRLICHT_ENGINE
		virtual bool OnEvent(const irr::SEvent& event);
#endif
	private:
		renderer device;
	};
}

#endif // __MICROFPS_GENERICHANDLER_H_
