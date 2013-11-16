/*
@authors:		Rosália Galiazzi Schneider
				Soulmen

@dateCreated:	31-12-2010
@lastUpdated:	7-1-2011

@filename:		client.h
@description:	Basic client console

*/

#include <Windows.h>
#include <irrlicht.h>
#include <irrKlang.h>


#include "SceneManager.h"
#include "LoginInterface.h"


#ifndef CLIENT_H
#define CLIENT_H

class SClient
{
public:
	SClient();
	~SClient();

	bool initialize();
	void run();
	void exit();

private:
	irr::IrrlichtDevice *device;
	

	EventReceiver _eventReceiver;
	SceneManager sceneManager;
	

	int _screenWidth, _screenHeight;
};

#endif // __SClient_H 