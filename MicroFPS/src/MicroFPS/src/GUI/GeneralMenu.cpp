/**
 * GeneralMenu.cpp
 * General Menu implementation
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

#include "GeneralMenu.h"

namespace MicroFPS
{
namespace Menus
{
	/**
	 * Constructor
	 */
	GeneralMenu::GeneralMenu(renderer device, const std::string& n)
		: gui(CEGUI::IrrlichtRenderer::bootstrapSystem(*device)), background(0), wmgr(CEGUI::WindowManager::getSingleton()),
		name(n)
	{
	}

	/**
	 * Destructor
	 */
	GeneralMenu::~GeneralMenu()
	{
		CEGUI::IrrlichtRenderer::destroySystem();
	}

	/**
	 * getGUIRenderer
	 */
	guirenderer& GeneralMenu::getGUIRenderer() const
	{
		return gui;
	}

	/**
	 * drop
	 */
	void GeneralMenu::drop()
	{
		delete this;
	}

	/**
	 * renderGUI
	 */
	void GeneralMenu::renderGUI()
	{
		CEGUI::System::getSingleton().renderGUI();
	}

	/**
	 * loadResources
	 */
	void GeneralMenu::loadResources(const std::string& name, const std::string& path, GUI::MENUR_TYPE type)
	{
		CEGUI::DefaultResourceProvider * rp = (CEGUI::DefaultResourceProvider*)CEGUI::System::getSingleton().getResourceProvider();
		rp->setResourceGroupDirectory(name, path); // Load resource

		// Load resource as default
		switch(type)
		{
		case GUI::SCHEMES:
			CEGUI::Scheme::setDefaultResourceGroup(name);
			break;
		case GUI::IMAGESETS:
			CEGUI::Imageset::setDefaultResourceGroup(name);
			break;
		case GUI::FONTS:
			CEGUI::Font::setDefaultResourceGroup(name);
			break;
		case GUI::LOOKNFEELS:
			CEGUI::WidgetLookManager::setDefaultResourceGroup(name);
			break;
		case GUI::LAYOUTS:
			CEGUI::WindowManager::setDefaultResourceGroup(name);
			break;
		case GUI::LUA_SCRIPTS:
			CEGUI::ScriptModule::setDefaultResourceGroup(name);
			break;
		case GUI::SCHEMAS:
			// This will have to go through an XML parser?
			break;
		}
	}

	/**
	 * loadScheme
	 */
	void GeneralMenu::loadScheme(const std::string& scheme)
	{
		CEGUI::SchemeManager::getSingleton().create(scheme);
	}

	/**
	 * loadBackground
	 */
	void GeneralMenu::loadBackground(const std::string& bg)
	{
		// Not yet implemented
	}

	/**
	 * loadLayout
	 */
	void GeneralMenu::loadLayout(const std::string& layout)
	{
		// Need to make this run through game manager later
		// Schemes, etc. should already be loaded at this point or it will crash :)
		//	it will be some ms_singleton() error
		CEGUI::Window* root = wmgr.loadWindowLayout(layout);
		CEGUI::System::getSingleton().setGUISheet(root);
	}

	/**
	 * addWindowMapping
	 * Add mapping to system
	 */
	void GeneralMenu::addWindowMapping(const std::string& type, const std::string& base, const std::string& look, const std::string& wRenderer,
		const std::string& effect)
	{
		CEGUI::WindowFactoryManager::getSingleton().addFalagardWindowMapping(type, base, look, wRenderer, effect);
	}

	/**
	 * getWindowManager
	 */
	CEGUI::WindowManager& GeneralMenu::getWindowManager()
	{
		return wmgr;
	}

	/**
	 * getName
	 */
	std::string GeneralMenu::getName() const
	{
		return name;
	}

	/**
	 * addEvent
	 */
	void GeneralMenu::addEvent(const std::string& object, u32 oid, const CEGUI::String& event, EventHandler * subscriber)
	{
		CEGUI::Window * window = 0;
		if(wmgr.getSingleton().isWindowPresent(object)) // Make sure it exists or we'll crash
			window = wmgr.getSingleton().getWindow(object);
		if(window == 0 || subscriber == 0) // Avoid null pointers if window not found!
			return;
		window->subscribeEvent(event, CEGUI::Event::Subscriber(subscriber));
		window->setID(oid);
	}

	/**
	 * getWindowID
	 * Get a window id from a pointer
	 */
	u32 GeneralMenu::getWindowID(CEGUI::Window* window) const
	{
		return window->getID();
	}

	/**
	 * injectTimePulse
	 */
	void GeneralMenu::injectTimePulse(f32 delta)
	{
		CEGUI::System::getSingleton().injectTimePulse(delta);
	}

	/**
	 * injectEvent
	 *	- For Irrlicht
	 */
#ifdef USE_IRRLICHT_ENGINE
	void GeneralMenu::injectEvent(const irr::SEvent& event)
	{
		gui.injectEvent(event);
	}
#endif
}
}

