/**
 * Irrlicht_Typedef.h
 * Typedefs to use the Irrlicht Rendering Engine with MicroFPS.
 *	You can obtain the Irrlicht engine from http://irrlicht.sf.net
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
 * Last Update: 9 July 2011
 */

#ifndef __MICROFPS_IRRLICHT_TYPEDEF_H_
#define __MICROFPS_IRRLICHT_TYPEDEF_H_

#include "../config.h"
#include "irrlicht.h" // Make sure you have this directory in path!

// Macros - should only need this for windows - MAKE SURE IT'S IN YOUR LIB PATH (or put the full path here)
// link with -lIrrlicht with gcc
#ifdef _WIN32
#define RENDER_ENGINE_LIB "Irrlicht.lib"
#endif

#ifdef USE_CEGUI
#include <CEGUI.h>
#include <RendererModules/Irrlicht/CEGUIIrrlichtRenderer.h>
#endif

namespace MicroFPS
{
	// Required Types
	typedef irr::IrrlichtDevice* renderer;
	typedef irr::scene::ISceneManager* scenemgr;
	typedef irr::scene::ICameraSceneNode* camera;
	typedef irr::scene::ISceneNode scenenode;
	typedef irr::scene::IMesh meshnode;
	typedef irr::scene::IMeshSceneNode meshscenenode;
	typedef irr::IEventReceiver ehandler;

	// Integer types
	typedef irr::s8 s8;
	typedef irr::s16 s16;
	typedef irr::s32 s32;
	typedef irr::u8 u8;
	typedef irr::u16 u16;
	typedef irr::u32 u32;
	typedef irr::f32 f32;

	// String/char types
	typedef irr::c8 c8;
	typedef irr::core::stringc stringc;
	typedef irr::core::stringw stringw;

	// GUI
#ifdef USE_CEGUI
	typedef CEGUI::IrrlichtRenderer guirenderer;
#endif
}
#endif // __MICROFPS_IRRLICHT_TYPEDEF_H_
