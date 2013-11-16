/**
 * typedefs.h
 * Basically makes the software modular
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
 * Last Update: 15 June 2011
 */

#ifndef __MICROFPS_TYPEDEFS_H_
#define __MICROFPS_TYPEDEFS_H_

// Determine which typedefs to use 
#ifdef USE_IRRLICHT_ENGINE
#include "typedefs/Irrlicht_Typedef.h"
#elif USE_OGRE3D_ENGINE
#include "typedefs/Ogre3D_Typedef.h"
#endif

// Determine physics
#ifdef USE_BULLET_PHYSICS
#include "typedefs/Bullet_Typedefs.h"
#elif USE_HAVOK_PHYSICS
#include "typedefs/Havok_Typedefs.h"
#endif

#endif // __MICROFPS_TYPEDEFS_H_
