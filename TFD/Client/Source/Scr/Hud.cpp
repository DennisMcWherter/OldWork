#include <irrlicht.h>
#include "include/Hud.h"

using namespace irr;

Hud::Hud()
: _showInventory(false) 
{
	_InventoryIsOpen =false;
}

Hud::~Hud()
{
}

bool Hud::initialize(IrrlichtDevice *device, EventReceiver *eventReceiver, int width, int height)
{
	
	_eventReceiver = eventReceiver;
	_width = width;
	_height = height;

	_render = device->getVideoDriver();
	if(_render == NULL)
		return false;

	image = _render->getTexture("Data/Hud.png");
	_render->makeColorKeyTexture(image, core::position2d<s32>(0,0));
	
	inventory = _render->getTexture("Data/Inventory.png");
	
	return true;
}

void Hud::update()
{ bool pressed;
	if(_eventReceiver->IsKeyDown(KEY_KEY_I))
	{
		_showInventory = !_showInventory;
		pressed =true;
	}else
	{
		pressed =false;
	}
}
void Hud::draw()
{
	_render->draw2DImage(image, core::position2d<s32>((_width-800)/2,_height-145),
				core::rect<s32>(0,0,800,145), 0,
				video::SColor(255,255,255,255), true);

	if(_showInventory){
		_render->draw2DImage(inventory, core::position2d<s32>(_width-373, 0 ),
				core::rect<s32>(0,0,373,636), 0,
				video::SColor(255,255,255,255), true);
	_InventoryIsOpen = true;
	}
	else
	{
		_InventoryIsOpen =false;
	}
} 


