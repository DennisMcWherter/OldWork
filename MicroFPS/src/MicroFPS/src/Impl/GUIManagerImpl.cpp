/**
 * GUIManagerImpl.cpp
 * Implementation of Manager for GUI's
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

#include "GUIManagerImpl.h"

#ifdef USE_CEGUI

namespace MicroFPS
{
	/**
	 * addGUI
	 */
	GUI* GUIManagerImpl::addGUI(const std::string& name, GUI* gui)
	{
		glist.insert(name, gui);
		return gui;
	}

	/**
	 * removeGUI
	 */
	void GUIManagerImpl::removeGUI(const std::string& name)
	{
		glist.remove(name);
	}

	/**
	 * getGUI
	 */
	GUI* GUIManagerImpl::getGUI(const std::string& name) const
	{
		return glist[name];
	}

	/**
	 * addGeneralMenu
	 */
	GUI* GUIManagerImpl::addGeneralMenu(const std::string& name, const renderer dev)
	{
		GUI * menu = new MicroFPS::Menus::GeneralMenu(dev, name);
		glist.insert(name, menu);
		return menu;
	}

	/**
	 * getCurrent
	 */
	GUI * GUIManagerImpl::getCurrent() const
	{
		return current;
	}

	/**
	 * setCurrent
	 */
	void GUIManagerImpl::setCurrent(const std::string& name)
	{
		current = glist[name];
	}
}

#endif // USE_CEGUI
