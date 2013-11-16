/**
 * RenderManagerImpl.h
 * Determines which rendering engine to use
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
 * Last Update: 16 June 2011
 */

#ifndef __MICROFPS_RENDERMANAGERIMPL_H_
#define __MICROFPS_RENDERMANAGERIMPL_H_

#include "../Managers/RenderManager.h"
#include "../RenderEngines/Renderer.h"

namespace MicroFPS
{
	class RenderManagerImpl : public RenderManager
	{
	public:

		/**
		 * Constructor
		 */
		RenderManagerImpl();

		/**
		 * Destructor
		 * - Don't leak <3
		 */
		virtual ~RenderManagerImpl();

		/**
		 * getRenderDevice
		 * Get the current rendering device
		 * @return renderer device (renderer varies based on specific configuration)
		 */
		virtual renderer getRenderDevice() const;

		/**
		 * loop
		 * Determine whether to continue looping or not
		 */
		virtual bool loop() const;

		/**
		 * gameLoop
		 * Run the game loop
		 */
		virtual void gameLoop(GameState * state=0);

	private:
		Renderer * renderengine;
	};
}

#endif // __MICROFPS_RENDERMANAGERIMPL_H_
