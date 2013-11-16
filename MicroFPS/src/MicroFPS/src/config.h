/**
 * config.h
 * Compiler configuration for library
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

#ifndef __MICROFPS_CONFIG_H_
#define __MICROFPS_CONFIG_H_

// Only use this when compiling the library!
#define MICROFPS_EXPORT

// Define rendering engine
#define USE_IRRLICHT_ENGINE // Use Irrlicht Rendering Engine
//#define USE_OGRE3D_ENGINE // Use Ogre3D Rendering Engine (Not yet supported)

// Define physics engine
#define USE_BULLET_PHYSICS // Use bullet physics
//#define USE_HAVOK_PHYSICS // Use HAVOK physics (Not yet supported)

// Define gui engine
#define USE_CEGUI // Only gui currently supported

#endif
