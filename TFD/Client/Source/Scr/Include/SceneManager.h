/*
@authors:		Rosália Galiazzi Schneider,
				Soulmen (Jordan Daubinet)

@dateCreated:	6-1-2011
@lastUpdated:	7-1-2011

@filename:		scenemanager.h
*/

#include <list>
#include <irrlicht.h>



#include "EventReceiver.h"
#include "Hero.h"
#include "Hud.h"
#include "AIBasic.h"
#include "Tree.h"
#include "Sound.h"

//interface headers
#include"LoginInterface.h"

//TEST NPC BOB
#include "TestNpc.h"


#ifndef __SCENEMANAGER_H
#define __SCENEMANAGER_H

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool initialize(irr::IrrlichtDevice *device, EventReceiver *eventReceiver, int width, int height);
	void deinitialize();
	
	void update();
	void draw();

private:
	// basic stuff
	irr::IrrlichtDevice *_device;
	irr::video::IVideoDriver *_render; 
	EventReceiver *_eventReceiver;
	
	// head-up display
	Hud _hud;

	// scene
	irr::scene::ISceneManager *_sceneManager;
	
	// camera
	ICameraSceneNode *_camera;

	//Soundengine
	irrklang::ISoundEngine* _soundengine;
	Sound _sound;

	// resources
	Hero _hero;	
	Object _ground;
	BOB _mob;
	ISceneNode* rootnode;
	ISceneNode* playernode;
	Trees _tree;

	//gui
	gui::IGUIFont* font;
	LoginInterface _mainscreen;
	

};

#endif // __SCENEMANAGER_H