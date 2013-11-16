/**
 * Renderer.cpp
 * Base class for all renderer connectors
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

#ifndef __MICROFPS_RENDERER_H_
#define __MICROFPS_RENDERER_H_

#include "../universal.h"
#include "../States/GameState.h"

namespace MicroFPS
{
	/**
	 * Renderer
	 * Base class for all renderer connectors
	 */
	class Renderer
	{
	public:
		/**
		 * Constructor
		 */
		Renderer(){}

		/**
		 * Destructor
		 */
		virtual ~Renderer(){}

		/**
		 * getRendererDevice
		 * Create the render device for this engine
		 */
		virtual renderer getRendererDevice() const = 0;

		/**
		 * loop
		 * Determine whether to continue looping or not
		 */
		virtual bool loop() const = 0;

		/**
		 * gameLoop
		 * Define the game loop method for this engine
		 */
		virtual void gameLoop(GameState * state=0) = 0;
	};
}

#endif // __MICROFPS_RENDERER_H_
