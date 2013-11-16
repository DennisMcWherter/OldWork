/**
 * GUI.h
 * Basic GUI object
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

// Currently only support CEGUI
#ifndef __MICROFPS_GUI_H_
#define __MICROFPS_GUI_H_

#include "../universal.h"
#include "../EventHandler/EventHandler.h"

#ifdef USE_CEGUI
#include <CEGUI.h>
namespace MicroFPS
{
	/**
	 * GUI Base Class
	 */
	class GUI
	{
	public:
		/**
		 * enum ResourceType
		 * Type of resource being loaded
		 */
		enum MENUR_TYPE
		{
			SCHEMES,
			IMAGESETS,
			FONTS,
			LAYOUTS,
			LOOKNFEELS,
			LUA_SCRIPTS,
			SCHEMAS
		};

		/**
		 * Constructor
		 */
		GUI(){}

		/**
		 * Destructor
		 */
		virtual ~GUI(){}

		/**
		 * getGUIRenderer
		 * Retrieve CEGUI object
		 */
		virtual guirenderer& getGUIRenderer() const = 0;

		/**
		 * Drop
		 * Delete object
		 */
		virtual void drop() = 0;

		/**
		 * renderGUI
		 * Render the gui
		 */
		virtual void renderGUI() = 0;

		/**
		 * loadResources
		 * Load resources - these are default
		 */
		virtual void loadResources(const std::string& name, const std::string& path, MENUR_TYPE type) = 0;

		/**
		 * loadScheme
		 * Load a scheme
		 */
		virtual void loadScheme(const std::string& scheme) = 0;

		/**
		 * loadBackground
		 * load background
		 */
		virtual void loadBackground(const std::string& name) = 0;

		/**
		 * loadLayout
		 * Load a layout
		 */
		virtual void loadLayout(const std::string& layout) = 0;

		/**
		 * addWindowMapping
		 * Add mapping to system
		 */
		virtual void addWindowMapping(const std::string& type, const std::string& base,
			const std::string& look, const std::string& renderer, const std::string& effect) = 0;

		/**
		 * getWindowManager
		 * Get the window manager
		 */
		virtual CEGUI::WindowManager& getWindowManager() = 0;

		/**
		 * getName
		 * Get GUI name
		 */
		virtual std::string getName() const = 0;

		/**
		 * addEvent
		 * Add an event to a GUI object
		 *	this takes a FUNCTOR
		 */
		virtual void addEvent(const std::string& object, u32 oid, const CEGUI::String& event, EventHandler * subscriber) = 0;

		/**
		 * injectTimePulse
		 * Sync CEGUI with the rendering
		 *   engine
		 */
		virtual void injectTimePulse(f32 delta) = 0;

		/**
		 * getWindowID
		 * Get a window id from a pointer
		 */
		virtual u32 getWindowID(CEGUI::Window* window) const = 0;

		/**
		 * injectEvent
		 * Inject an input event to GUI
		 */
#ifdef USE_IRRLICHT_ENGINE // Irrlicht version
		virtual void injectEvent(const irr::SEvent& event) = 0;
#endif

	};
}

#endif // USE_CEGUI
#endif // __MICROFPS_GUI_H_
