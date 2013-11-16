/**
 * Irrlicht_Renderer.h
 * Irrlicht Renderer connector
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

#ifndef __MICROFPS_IRRLICHT_RENDERER_H_
#define __MICROFPS_IRRLICHT_RENDERER_H_

#include "Renderer.h"
// This is _the_ irrlicht connector - we probably don't need to
// but explicitly include it anyway --- Again, make sure it's in path
#include "irrlicht.h"

namespace MicroFPS
{
	/**
	 * Irrlicht_Renderer
	 * Irrlicht renderer connector
	 */
	class Irrlicht_Renderer : public Renderer
	{
	public:
		/**
		 * Constructor
		 * @param irr::video::E_DRIVER_TYPE driver - driver type
		 * @param irr::core::dimension2d<u32> windowSize - window dimensions
		 * @param irr::u32 bits - display bits
		 * @param bool fullscreen - Fullscreen mode?
		 * @param bool stencilbuffer - Enable stencil buffer?
		 * @param bool vsync - Enable vsync?
		 */
		Irrlicht_Renderer(irr::video::E_DRIVER_TYPE driver=irr::video::EDT_OPENGL,
			const irr::core::dimension2d<irr::u32>& windowSize=irr::core::dimension2d<irr::u32>(800,600), irr::u32 bits=16,
			bool fullscreen=false, bool stencilbuffer=false, bool vsync=false);

		/**
		 * Destructor
		 */
		virtual ~Irrlicht_Renderer();

		/**
		 * getRendererDevice
		 * get an irr::IrrlichtDevice
		 */
		virtual renderer getRendererDevice() const;

		/**
		 * loop
		 * Determine whether to continue looping or not
		 */
		virtual bool loop() const;

		/**
		 * gameLoop
		 */
		virtual void gameLoop(GameState * state=0);
	private:
		renderer device;
	};
}

#endif // __MICROFPS_IRRLICHT_RENDERER_H_
