 /*
@authors:		Rosália Galiazzi Schneider
				Soulmen

@dateCreated:	6-1-2011
@lastUpdated:	6-1-2011

@filename:		client.h
@description:	Basic client console

NOTICE
SClient has problems with 64x bits systems to connect with the server
*/

#include "include/Client.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace scene;
using namespace video;

SClient::SClient()
: device(NULL)
{
	_screenWidth =500;
	_screenHeight = 400;
}

//WARNING: this code is absolutely bugged
//the destructor must appen after the device
//is closed since the main game loop run into
//this class. That's mean
//1) the desctructor will never be called
//since you are in a infinite loop

/*i comment out this code. for exit the game just call "exit"
method*/
SClient::~SClient()
{ 
	/*device->closeDevice();
	device->drop();*/
}

bool SClient::initialize()
{
	// create device
	device = irr::createDevice(video::EDT_DIRECT3D9, core::dimension2d<u32>(_screenWidth, _screenHeight), 16, false, false, false, &_eventReceiver);
	if(device == NULL)
		return false;
	

	device->setWindowCaption(L"The Forgotten Darkness v0.1");
	
	
	return sceneManager.initialize(device, &_eventReceiver, _screenWidth, _screenHeight);
}
void SClient::exit()
{
	device->closeDevice();
}
void SClient::run()
{
	while(device->run())
	{
		
		sceneManager.update();
		sceneManager.draw();
		
			
			

		
	}
	device->drop();
}

