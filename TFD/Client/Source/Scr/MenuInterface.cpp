#include "include/MenuInterface.h"


MenuInterface::MenuInterface()  : isOpen(false)
{
}

bool MenuInterface::init(irr::IrrlichtDevice *_device, EventReceiver *_event, int _width, int _height)
{
	_event =_event;
	_render = _device->getVideoDriver();
	_env = _device->getGUIEnvironment();
	width =  _width;
	height =_height;
	if(!_render)
		return false;

	_menupng = _render->getTexture("Data/Interface/Ingame/menu.png");

	return true;


}
void MenuInterface::update()
{
	
	if(_event.IsKeyDown(irr::KEY_ESCAPE))
	{
		isOpen = true;
	}
	else
	{
		isOpen =false;
	}

}
void MenuInterface::draw()
{

	if(isOpen)
	{

		_render->draw2DImage(_menupng, irr::core::vector2d<s32>(width/2, height-40));
	}


}
MenuInterface::~MenuInterface()
{


	_env->drop();

	delete _render;
	delete _env;
}