
#include "Include/SceneManager.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	_soundengine->drop();
	_sound.drop();
}

bool SceneManager::initialize(IrrlichtDevice *device, EventReceiver *eventReceiver, int width, int height)
{
	// initialize scene manager
	_device = device;
	_eventReceiver = eventReceiver;

	_render = _device->getVideoDriver();
	if(_render == NULL)
		return false;

	//setup login window
	

	_soundengine = irrklang::createIrrKlangDevice();

	_sceneManager = _device->getSceneManager();

	//
	


	


	// load resources
	///_ground.setMesh(_sceneManager->getMesh("Data/Ground.obj"));
	//_ground.setNode(_sceneManager->addAnimatedMeshSceneNode(_ground.mesh(), 0, 1, vector3df(0, -150, 0), vector3df(0, 0, 0), vector3df(30, 30, 30)));
	//_ground.setMaterial(_render->getTexture("Data/terrain-texture.jpg"));

	//nodes
	
		playernode = _sceneManager->addSceneNode("Player");

	_hero.setMesh(_sceneManager->getMesh("Data/Sydney.md2"));
	_hero.setNode(_sceneManager->addAnimatedMeshSceneNode(_hero.mesh(),playernode));
	_hero.setMaterial(_render->getTexture("Data/Sydney.bmp"));
	_hero.mesh()->setMaterialFlag(irr::video::EMF_GOURAUD_SHADING, true);
	_hero.mesh()->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	
	_hero.setPosition(vector3df(750, 30 , 0));

	//node



	scene::ISceneNode* skybox=_sceneManager->addSkyBoxSceneNode(
		_render->getTexture("Data/irrlicht2_up.jpg"),
		_render->getTexture("Data/irrlicht2_dn.jpg"),
		_render->getTexture("Data/irrlicht2_lf.jpg"),
		_render->getTexture("Data/irrlicht2_rt.jpg"),
		_render->getTexture("Data/irrlicht2_ft.jpg"),
		_render->getTexture("Data/irrlicht2_bk.jpg"));

	
	// initialize hud
	_hud.initialize(_device, _eventReceiver, width, height);
	
	_mainscreen.initialize(device,_eventReceiver, width, height);


	//position of bob
	/*_mob.setMesh(_sceneManager->getMesh("Data/Sydney.md2"));
	_mob.setNode(_sceneManager->addAnimatedMeshSceneNode(_hero.mesh(),0, 2));
	_mob.setMaterial(_render->getTexture("Data/Sydney2.bmp"));
    _mob.setPosition(vector3df(-0, -0, -0));
	*/

	//terrain

	ITerrainSceneNode* terrain[4];
	ISceneNode* map = _sceneManager->addSceneNode("LIGHTING",0);
	
	
	 terrain[1] =_sceneManager->addTerrainSceneNode("Data/Terrain/mainmap.bmp",map);
	terrain[1]->setPosition(vector3df(0, -127.5, -496));
	terrain[1]->setScale(vector3df(1, 1, 1));
	terrain[1]->setMaterialFlag(video::EMF_LIGHTING, false);
	terrain[1]->setMaterialTexture(0, _render->getTexture("Data/Terrain/mainmaptext.bmp"));
	terrain[1]->setMaterialFlag(video::EMF_GOURAUD_SHADING, true);
	
	//node
	
	
	//trees
	_tree.setMesh(_sceneManager->getMesh("Data/GameObjects/Models/tree.md2"));
	_tree.setNode(_sceneManager->addAnimatedMeshSceneNode(_tree.mesh()));
	_tree.setMaterial(_render->getTexture("Data/GameObjects/Texture/tree.png"));
	_tree.setPosition(vector3df(750, 0, 50));

	///end trees
	
  font = _device->getGUIEnvironment()->getBuiltInFont();

  _sound.PlaySound(_soundengine);
	
	return true;
}

void SceneManager::update()
{	
	// get from network
	// provisory = getting from a file

	_hero.loadStats("Data/Character.txt");


// set camera
	_camera =_sceneManager->addCameraSceneNode(playernode, _hero.position() + vector3df(0, 30, 50),_hero.position() + vector3df(0, 10, 0));
	
	
	bool stop = true;
	if(_eventReceiver->IsKeyDown(irr::KEY_KEY_W)) {
		_hero.walk();
		stop = false;
	}
	if(_eventReceiver->IsKeyDown(irr::KEY_KEY_A)) {
		_hero.turnLeft();
		stop = false;
	}
	if(_eventReceiver->IsKeyDown(irr::KEY_KEY_D)) {
		_hero.turnRight();
		stop = false;
	}
	if(stop)
		_hero.stop();

	_hud.update();
	//STAY OUT OF BOB AREA
	//_mob.isInRange(_hero);


	// SHE SAID STAY OUT
	
	// send through network
	// provisory = send to a file
	_hero.saveStats("Data/Character.txt");
}

void SceneManager::draw()
{
	_render->beginScene(true, true, video::SColor(255, 0, 0, 255));
	

	if(_mainscreen.isDone()){
	_sceneManager->drawAll();

	 gui::IGUIFont* font = _device->getGUIEnvironment()->getBuiltInFont();
	_hero.drawStats(font);
	
	_hud.draw();

	}
	else
	{
		_mainscreen.update();
		_mainscreen.draw();
	}

	_render->endScene();

	

}