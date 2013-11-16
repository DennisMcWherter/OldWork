/**
 * GeneralMenu.h
 * General Menu
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

#ifndef __MICROFPS_GENERALMENU_H_
#define __MICROFPS_GENERALMENU_H_

#include "../universal.h"
#include "GUI.h"

#ifdef USE_CEGUI
#ifdef USE_IRRLICHT_ENGINE
#include <RendererModules/Irrlicht/CEGUIIrrlichtRenderer.h>
#elif USE_OGRE3D_ENGINE
#endif
namespace MicroFPS
{
namespace Menus
{
	/**
	 * General Menu class
	 */
	class GeneralMenu : public GUI
	{
	public:
		/**
		 * Constructor
		 */
		GeneralMenu(renderer device, const std::string& name);

		/**
		 * Destructor
		 */
		virtual ~GeneralMenu();

		/**
		 * retrieve gui
		 */
		virtual guirenderer& getGUIRenderer() const;

		/**
		 * drop
		 */
		virtual void drop();
		
		/**
		 * renderGUI
		 */
		virtual void renderGUI();

		/**
		 * loadResources
		 * Load resources - these are default
		 */
		virtual void loadResources(const std::string& name, const std::string& path, MENUR_TYPE type);

		/**
		 * loadBackground
		 * load background
		 */
		virtual void loadBackground(const std::string& name);

		/**
		 * loadScheme
		 * Load a scheme
		 */
		virtual void loadScheme(const std::string& path);

		/**
		 * loadLayout
		 */
		virtual void loadLayout(const std::string& path);

		/**
		 * addWindowMapping
		 * Add mapping to system
		 */
		virtual void addWindowMapping(const std::string& type, const std::string& base,
			const std::string& look, const std::string& renderer, const std::string& effect);

		/**
		 * getWindowManager
		 * Get the window manager
		 */
		virtual CEGUI::WindowManager& getWindowManager();

		/**
		 * getName
		 * Get GUI name
		 */
		virtual std::string getName() const;

		/**
		 * addEvent
		 * Add an event to a GUI object
		 */
		virtual void addEvent(const std::string& object, u32 oid, const CEGUI::String& event, EventHandler * subscriber);

		/**
		 * injectTimePulse
		 * Sync CEGUI with the rendering
		 *   engine
		 */
		virtual void injectTimePulse(f32 delta);

		/**
		 * getWindowID
		 * Get a window id from a pointer
		 */
		virtual u32 getWindowID(CEGUI::Window* window) const;

		/**
		 * injectEvent
		 * Inject an input event to GUI
		 */
#ifdef USE_IRRLICHT_ENGINE // Irrlicht version
		virtual void injectEvent(const irr::SEvent& event);
#endif

	private:
		guirenderer& gui;
		CEGUI::Window* background;
		CEGUI::WindowManager& wmgr;
		std::string name;
	};
}
}

#endif // USE_CEGUI
#endif // __MICROFPS_GENERALMENU_H_
