#ifndef MENU_INTERFACE_INCLUDED
#define MENU_INTERFACE_INCLUDED

#include <irrlicht.h>
#include "EventReceiver.h"

class MenuInterface
{
public:
	MenuInterface();
	~MenuInterface();

	void draw();
	bool init(irr::IrrlichtDevice *_device, EventReceiver *_event, int _width, int _height);
	void update();
	
private:
	EventReceiver _event;
	gui::IGUIEnvironment* _env;
	video::IVideoDriver* _render;
	bool isOpen;
	int height, width;

	irr::video::ITexture *_menupng;

};

#endif