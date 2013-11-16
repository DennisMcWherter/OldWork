/**
 * Irrlicht_Renderer.cpp
 * Implementation of Irrlicht_Renderer
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
 * Last Update: 23 June 2011
 */

#include "Irrlicht_Renderer.h"

using namespace irr;
using namespace irr::core;

namespace MicroFPS
{
	/**
	 * Constructor
	 * @param irr::video::E_DRIVER_TYPE driver - driver type
	 * @param irr::core::dimension2d<u32> windowSize - window dimensions
	 * @param irr::u32 bits - display bits
	 * @param bool fullscreen - Fullscreen mode?
	 * @param bool stencilbuffer - Enable stencil buffer?
	 * @param bool vsync - Enable vsync?
	 */
	Irrlicht_Renderer::Irrlicht_Renderer(video::E_DRIVER_TYPE driver, const dimension2d<u32>& windowSize,
		u32 bits, bool fullscreen, bool stencilbuffer, bool vsync)
		: device(0)
	{
		device = createDevice(driver, windowSize, bits, fullscreen, vsync);
		if(device == NULL)
			throw std::runtime_error("Could not initialize rendering device!");
	}

	/**
	 * Destructor
	 * Be certain we clean up ;)
	 */
	Irrlicht_Renderer::~Irrlicht_Renderer()
	{
		if(device)
			device->drop();
	}

	/**
	 * getRendererDevice
	 * Simply get the renderer
	 */
	renderer Irrlicht_Renderer::getRendererDevice() const
	{
		return device;
	}

	/**
	 * loop
	 */
	bool Irrlicht_Renderer::loop() const
	{
		// This is the Irrlicht loop condition
		return device->run();
	}

	/**
	 * gameLoop
	 */
	void Irrlicht_Renderer::gameLoop(GameState * state)
	{
		// Need to implement functions to get enemy and physics
		// managers?
		// Perhaps a pointer back to the parent? (i.e. game manager)
		// This is all temporary for better to be certain everything is working!
		device->getVideoDriver()->beginScene(true, true, video::SColor(50,50,50,50));

		if(state != 0)
		{
			state->criticalLoop();
			state->getSceneManager()->drawAll();
		}
		device->getVideoDriver()->endScene();
		if(state != 0)
			state->gameLoop();
	}
}
