#include <irrlicht.h>
#include "include/LoginInterface.h"

using namespace irr;

LoginInterface::LoginInterface() : isdone(false)
{
	validFields = false;
}

LoginInterface::~LoginInterface()
{
}

bool LoginInterface::initialize(IrrlichtDevice *device, EventReceiver *eventReceiver, int width, int height)
{
        
        _eventReceiver = eventReceiver;
        _width = width;
        _height = height;

        _render = device->getVideoDriver();
        if(_render == NULL)
                return false;

        loginscreen = _render->getTexture("Data/Interface/Maintitle/main.png");
        _render->makeColorKeyTexture(loginscreen, core::position2d<s32>(0,0));
        
        _gui = device->getGUIEnvironment();
        return true;
}

//TODO: this code is potentially not safe.
/*
	check here for more infos:
	http://tfddev.freeforums.org/relevant-gui-events-user-input-t105.html
*/
void LoginInterface::update()
{ 
        if(_eventReceiver->IsKeyDown(irr::KEY_RETURN))
        {
                isdone =true;
        }

        if(_eventReceiver->getBoolean())
        {
                isdone =true;
        }
        

}

bool LoginInterface::isDone()
{

        return isdone;
}
void LoginInterface::draw()
{
        
        _render->draw2DImage(loginscreen, core::position2d<s32>((_width-500)/2,(_height-400)/2),
                
		//username field
                core::rect<s32>(0,0,500,400), 0,
                                video::SColor(255,255,255,255), true);
        _userinput = _gui->addEditBox(NULL, core::rect<s32>((_width/2),_height/2,(_width/2)+100,(_height/2)+25),false, 0, 1);
        _userinput->setMaxSize(core::dimension2du(100,25));
		
		//RETURN event may not be catched if multiline is enabled
		_userinput->setMultiLine(false); 
        _render->draw2DRectangle(core::rect<s32>((_width/2),_height/2,(_width/2)+100,(_height/2)+25),video::SColor(255,255,255,255),video::SColor(255,255,255,255), video::SColor(255,255,255,255),video::SColor(255,255,255,255));
        
        //end field

        //the static tekst
        _gui->addStaticText(L"Usename",core::rect<s32>(core::rect<s32>((_width/2)-60,_height/2,(_width/2)-10,(_height/2)+25)));
        _gui->addStaticText(L"Password",core::rect<s32>((_width/2)-60,_height/2+30,(_width/2)-10,(_height/2)+55));
        

        //password field
        _render->draw2DRectangle(core::rect<s32>((_width/2),(_height/2)+30,(_width/2)+100,(_height/2)+55),video::SColor(255,255,255,255),video::SColor(255,255,255,255), video::SColor(255,255,255,255),video::SColor(255,255,255,255));
        _passwordinput = _gui->addEditBox(NULL, core::rect<s32>((_width/2),(_height/2)+30,(_width/2)+100,(_height/2)+55),false, 0, 1);
        _passwordinput->setPasswordBox(true,L'*');
		_passwordinput->setMultiLine(false);  //multiline
        _passwordinput->setMaxSize(core::dimension2du(100,25));
        //end field
        

        _submit  =_gui->addButton(core::rect<s32>((_width/2)+35, (_height/2)+70,(_width/2)+95, (_height/2)+90), 0, BUTTON_LOGIN, L"Login"); 
        _exit  =_gui->addButton(core::rect<s32>((_width/2)-60, (_height/2)+70,(_width/2)-35, (_height/2)+90), 0, BUTTON_EXIT, L"Quit"); 

        
        
        _gui->drawAll();
} 


const wchar_t* LoginInterface::getUsername()
{
		if(validFields)
		{
			return _userinput->getText();
		}
		return 0;
}
const wchar_t* LoginInterface::getPassword()
{
		if(validFields)
		{
			return _passwordinput->getText();
		}
		return 0;
}


void LoginInterface::checkInputFields()
{
	//TODO:
	/*
		Check if the password is at least 6 characters and no more than 16
		Check if the username is at least 4 Characters and no more than 16
		Check if username or password contains invalid characters
		or invalid words ( parentesis, new lines, spaces, comas, are not
		admitted)
		There musn't be words as " WHERE " (also white spaces included
		"WHEREAREYOU" is valid
		"WHERE" is valid
		" WHERE " is not valid
		(this will prevent mySQL code injections)
	*/
	
	validFields=true;
}