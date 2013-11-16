/*
Hud
*/

#ifndef __LOGININTERFACE_H
#define __LOGININTERFACE_H

#include <irrlicht.h>
#include "EventReceiver.h"
#include "InterfaceDefines.h"

class LoginInterface
{
public:
	LoginInterface();
	~LoginInterface();

	bool initialize(irr::IrrlichtDevice *device, EventReceiver *_eventReceiver, int width, int height);

	void update();
	void draw();
	bool isDone();
	void checkInputFields();
	
	const wchar_t* getUsername();
	const wchar_t* getPassword();
	

private:
	
	irr::video::IVideoDriver *_render;
	EventReceiver *_eventReceiver;
	int _width, _height;

	gui::IGUIEnvironment* _gui;

	gui::IGUIEditBox* _userinput;
	gui::IGUIEditBox* _passwordinput;

	gui::IGUIButton* _submit;
	gui::IGUIButton* _exit;

	irr::video::ITexture* loginscreen;

	bool isdone;
	bool validFields; //if user have inserted valid username and password format (prevent mySQL iniejction)

	
};

#endif