/**
 * GUIManagerImpl.h
 * Manager for GUI's
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

#ifndef __MICROFPS_GUIMANAGERIMPL_H_
#define __MICROFPS_GUIMANAGERIMPL_H_

#include "../Managers/GUIManager.h"
#include "../GUI/GeneralMenu.h"
#include "../Core/Array.h"

#ifdef USE_CEGUI
namespace MicroFPS
{
	/**
	 * GUIManagerImpl
	 */
	class GUIManagerImpl : public GUIManager
	{
	public:
		/**
		 * Constructor
		 */
		GUIManagerImpl() : current(0) {}

		/**
		 * Destructor
		 */
		virtual ~GUIManagerImpl(){}

		/**
		 * addGUI
		 * add new GUI
		 */
		virtual GUI* addGUI(const std::string& name, GUI* gui);

		/**
		 * removeGUI
		 * remove a GUI
		 */
		virtual void removeGUI(const std::string& name);

		/**
		 * getGUI
		 * retrieve a gui
		 */
		virtual GUI* getGUI(const std::string& name) const;

		/**
		 * addGeneralMenu
		 * Add a general menu
		 */
		virtual GUI* addGeneralMenu(const std::string& name, const renderer dev);

		/**
		 * getCurrent
		 * get the current gui - it is the responsibility
		 *	of the client code to guarantee this is properly
		 *	maintained
		 */
		virtual GUI * getCurrent() const;

		/**
		 * setCurrent
		 * set current gui
		 */
		virtual void setCurrent(const std::string& name);

	private:
		GUI * current;
		MicroFPS::core::Array<GUI*> glist;
	};
}
#endif // USE_CEGUI
#endif // __MICROFPS_GUIMANANGERIMPL_H_
