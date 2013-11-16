/**
 * main.cpp
 * This is the entry point for the engine
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
 * Last Update: 22 June 2011
 */

// Make sure we export the lib
#define MICROFPS_EXPORT
//#define RELEASE // Release version?

// Required includes
#include "universal.h"

// Windows library
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

// Make sure we link properly
#ifdef _WIN32
#pragma comment(lib, RENDER_ENGINE_LIB)

#ifdef USE_CEGUI
#ifdef RELEASE
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIBase.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIIrrlichtRenderer.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIExpatParser.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIFalagardWRBase.lib")
#else
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIBase_d.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIIrrlichtRenderer_d.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIExpatParser_d.lib")
#pragma comment(lib, "../../libs/CEGUI-0.7.5/lib/CEGUIFalagardWRBase_d.lib")
#endif
#endif

#ifdef USE_BULLET_PHYSICS // Important Bullet libraries
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "LinearMath.lib")
#endif

#endif

// This to export Win32 DLL files; unnecessary for *nix .so files
#ifdef _WIN32
bool APIENTRY DllMain(HINSTANCE hInst, DWORD reason, LPVOID lpRes)
{
	switch(reason)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return true;
}
#endif
