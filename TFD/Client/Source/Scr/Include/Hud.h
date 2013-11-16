/*
Hud
*/

#ifndef __HUD_H
#define __HUD_H

#include <irrlicht.h>
#include "EventReceiver.h"

class Hud
{
public:
	Hud();
	~Hud();

	bool initialize(irr::IrrlichtDevice *device, EventReceiver *_eventReceiver, int width, int height);

	void update();
	void draw();
	
	

private:
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_render;
	EventReceiver *_eventReceiver;
	int _width, _height;

	irr::video::ITexture* image;
	irr::video::ITexture* inventory;

	bool _showInventory;
	bool _InventoryIsOpen;
};

#endif