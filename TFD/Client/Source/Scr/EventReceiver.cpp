#include "include/EventReceiver.h"

using namespace irr;

EventReceiver::EventReceiver() 
{ 
	
	_boolean =false;

	for(u32 i = 0; i < KEY_KEY_CODES_COUNT; ++i)
		_keyIsDown[i] = false;

}
bool EventReceiver::getBoolean()
{

	return _boolean;
}

// This is the one method that we have to implement
bool EventReceiver::OnEvent(const SEvent& event)
{
	// Remember whether each key is down or up
	if(event.EventType == irr::EET_KEY_INPUT_EVENT)
		_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	if(event.EventType == irr::EET_GUI_EVENT)
	{
		s32 _id =event.GUIEvent.Caller->getID();

		switch(event.GUIEvent.EventType)
		{

		case gui::EGET_BUTTON_CLICKED:
		switch(_id)
		{
		case BUTTON_EXIT:
			exit(255);
			break;
		case BUTTON_LOGIN:
			_boolean =true;
			break;
		
		}

	

			break;

		}

	}
	
    return false;
}

// This is used to check whether a key is being held down
bool EventReceiver::IsKeyDown(EKEY_CODE keyCode) const
{  
	
	return _keyIsDown[keyCode];	
	
return false;
}


