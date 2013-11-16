#ifndef __EVENTRECEIVER_H
#define __EVENTRECEIVER_H

#include <irrlicht.h>
#include "InterfaceDefines.h"
using namespace irr;

class EventReceiver : public IEventReceiver
{
public:
	EventReceiver();

    virtual bool OnEvent(const SEvent& event);
    
	 bool IsKeyDown(EKEY_CODE keyCode) const;

	 bool IsKeyUp(EKEY_CODE keyCode) const;

	
	bool getBoolean();
   
private:
	bool _boolean;
    bool _keyIsDown[KEY_KEY_CODES_COUNT];

};

#endif