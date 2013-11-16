/**
 * universal.h
 * This file is a quick include for all new classes.
 *	it is intended to include all files universally required
 *  by much of MicroFPS.
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

#ifndef __MICROFPS_UNIVERSAL_H_
#define __MICROFPS_UNIVERSAL_H_

// Configuration
#include "config.h"

// Necessary items for Win32 DLL Export
#if defined(_WIN32) && defined(MICROFPS_EXPORT)
#define MICROFPSAPI __declspec(dllexport)
#elif !defined(_WIN32)
#define MICROFPSAPI // This is unnecessary for *nix systems
#else
#define MICROFPSAPI __declspec(dllimport)
#endif

// Includes needed by all files
#include <iostream> // Rather important stuff
#include <memory> // auto_ptrs are our friends (soon unique_ptrs when most compilers support :))
#include <stdexcept> // Handle exceptions
#include <cassert> // c-style asserts
#include "typedefs.h"
#include "Core/Array.h"

#ifdef USE_CEGUI
#include <CEGUI.h>
#endif

#endif // __MICROFPS_UNIVERSAL_H_
