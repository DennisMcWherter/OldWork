// Test MicroFPS

#include <iostream>
#include "../src/MicroFPS.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include <crtdbg.h>
#include <utility>

//#pragma comment(lib, "../../MicroFPS/src/libs/irrlicht-1.7.2/lib/win32-visualstudio/Irrlicht.lib")
#pragma comment(lib, "../../MicroFPS/bin/Debug/MicroFPS_d.lib")
#pragma comment(lib, "../../MicroFPS/src/libs/CEGUI-0.7.5/lib/CEGUIBase.lib")

// Only if using bullet directly
#pragma comment(lib, "../../MicroFPS/src/libs/bullet-2.78/lib/Debug/BulletCollision.lib")
#pragma comment(lib, "../../MicroFPS/src/libs/bullet-2.78/lib/Debug/BulletDynamics.lib")
#pragma comment(lib, "../../MicroFPS/src/libs/bullet-2.78/lib/Debug/BulletSoftBody.lib")
#pragma comment(lib, "../../MicroFPS/src/libs/bullet-2.78/lib/Debug/LinearMath.lib")
//#pragma comment(lib, "../../MicroFPS/src/libs/CEGUI-0.7.5/lib/CEGUIIrrlichtRenderer.lib")
//#pragma comment(lib, "../Debug/MicroFPS_DLL_Test.lib")

using namespace MicroFPS;
using namespace std;
using MicroFPS::core::Array;

/** Weapon Implementation */
class Pistol : public MicroFPS::Weapon
{
protected:
	// Pistol effects
	class PistolEffects : public Effects
	{
	public:
		PistolEffects(){}
		virtual ~PistolEffects(){}

		virtual std::pair<u32,u32> getAnimation(std::string name) const { return animations[name]; }
		virtual void getSound() const{} // not implemented
		virtual void addAnimation(std::string name, u32 start, u32 end) { animations.insert(name,std::pair<u32,u32>(start,end)); }
		virtual void addSound() {} // not implemented
		virtual void shoot() {} // not implemented
	private:
		MicroFPS::core::Array<std::pair<u32,u32> > animations;
	};

public:
	Pistol()
		: ammo(64), clip(32), capacity(64), maxclip(32), damage(10), effects(new PistolEffects)
	{
	}

	virtual ~Pistol()
	{
		if(effects)
			delete effects;
	}

	// "getter" functions
	virtual s16 getDamage() const { return damage; }
	virtual u16 getAmmo() const { return ammo; }
	virtual u16 getMaxClipSize() const { return maxclip; }
	virtual u16 getMaxCapacity() const { return capacity; }
	virtual stringw getWeaponName() const { return "Pistol"; }

	// Modifying functions
	virtual void setAmmo(u16 a) { ammo = a; }
	virtual void addAmmo(u16 a) { ammo += a; }
	virtual void decreaseAmmo(u16 a) { ammo -= a; }
	virtual Effects * getEffects() const { return effects; }

private:
	u16 ammo, clip, capacity, maxclip;
	s16 damage;
	Effects * effects;
};

class Camera
{
public:
	Camera(MicroFPS::GameManager * game)
		: physics(game->getPhysicsManager())
	{
		camera = game->getPlayerManager()->getPlayer()->getCamera();
		const irr::core::aabbox3df& box = camera->getTransformedBoundingBox();
		const irr::core::vector3df& d = box.MaxEdge-box.getCenter();
		const f32 rad(d.getLength()*0.5f);

		// Create shape with radius appropriate for camera
		/*shape = new btSphereShape(rad);

		shape->calculateLocalInertia(1.0,btVector3(0,0,0));

		body = new btRigidBody(1.0, 0, shape, btVector3(0,0,0));

		// Setup physics
		body->setRestitution(-0.5f); // Try to avoid bouncing xD
		body->setFriction(1.0f);
		body->setDamping(0.2f, 0.1f);
		body->setActivationState(4); // Never disable
		body->setCollisionFlags(16); // Character flags
		body->setGravity(btVector3(0,-9.81,0));
		body->setUserPointer((void*)camera); // Attach to camera

		physics->getWorld()->addRigidBody(body);
		// Check: http://www.irrlicht3d.org/wiki/index.php?n=Main.GettingStartedWithBullet
		irr::scene::ICameraSceneNode * c = static_cast<irr::scene::ICameraSceneNode*>(body->getUserPointer());
		// This works :) now to automagically do it <3
		if(c)
		{
			std::cout<< "w00t" << std::endl;
			c->setPosition(irr::core::vector3df(30,30,30));
		}*/
		camera->getAbsolutePosition();
		camera->setPosition(camera->getPosition()+irr::core::vector3df(0,20,0));
		irr::scene::IMeshSceneNode * ground = camera->getSceneManager()->addCubeSceneNode(50.0f);
		camera->getAbsolutePosition();
		ground->setPosition(camera->getPosition()+irr::core::vector3df(0,-20,0));
		ground->setMaterialFlag(irr::video::EMF_LIGHTING, 1);
		ground->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
		physics->addCollisionMap(ground);
		body = physics->addCollisionObject(camera);
	}
	virtual ~Camera(){}

	virtual void moveForward(const f32& speed)
	{
		// Irrlicht specific
		irr::core::matrix4 mat;
		body->getWorldTransform().getOpenGLMatrix(mat.pointer());

		// Actually do transformation
		mat.setRotationDegrees(camera->getRotation());
		mat.setTranslation(mat.getTranslation()+irr::core::vector3df(mat[8]*speed*10, mat[9]*speed*10,
			mat[10]*speed*10));

		// Do the transformation back to bullet system
		btTransform trans;
		trans.setIdentity();
		trans.setFromOpenGLMatrix(mat.pointer());
		body->setWorldTransform(trans);
	}

private:
	PhysicsManager * physics;
	irr::scene::ICameraSceneNode * camera;
	btCollisionShape * shape;
	btRigidBody * body;
};

/** In-game event handler */
class GameHandler : public MicroFPS::EventHandler
{
public:
	GameHandler(MicroFPS::GameManager* g)
		: game(g), player(g->getPlayerManager()->getPlayer()), cam(new Camera(g))
	{
		// Scratch work
		/*btCollisionShape * t = new btSphereShape(11.0f);
		btRigidBody * y = new btRigidBody(1.0, 0, t, btVector3(0,0,0));
		btSimpleDynamicsWorld * x = new btSimpleDynamicsWorld(0,0,0,0);
		x->addRigidBody(y);
		x->removeRigidBody(y);*/
	}

	virtual ~GameHandler()
	{
		if(cam)
			delete cam;
	}

	virtual bool OnEvent(const irr::SEvent& event)
	{
		game->getGUIManager()->getCurrent()->injectEvent(event);
		if(event.EventType == irr::EET_KEY_INPUT_EVENT) // Keys
		{
			switch(event.KeyInput.Key)
			{
			case irr::KEY_ESCAPE: // Quit
				game->getStateManager()->setCurrentState("MainMenu");
				break;
			case irr::KEY_KEY_W:
				cam->moveForward(10.0f);
			default:
				break;
			}
		}

		if(event.EventType == irr::EET_MOUSE_INPUT_EVENT) // Mouse
		{
			switch(event.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				break;
			default:
				break;
			}
		}
		return true;
	}

	virtual bool operator()(const CEGUI::EventArgs& e)
	{
		return OnGUIEvent(e);
	}

	// No GUI
	virtual bool OnGUIEvent(const CEGUI::EventArgs& e)
	{
		return true;
	}
private:
	MicroFPS::GameManager * game;
	MicroFPS::Player * player;
	Camera * cam;
};

/** Level Implementation */
class Level1 : public MicroFPS::GameState
{
public:
	Level1(MicroFPS::GameManager * g) : game(g)
	{
		// Note: Will need to create a setGravity function to take 3 doubles
		//	to abstract this
		game->getPhysicsManager()->getWorld()->setGravity(btVector3(0,-9.81,0));
		device = game->getRenderManager()->getRenderDevice();
		smgr = device->getSceneManager()->createNewSceneManager();
		camera cam = smgr->addCameraSceneNodeFPS(0, 50.0f, 0.1f);
		smgr->setActiveCamera(cam);
		game->getPlayerManager()->getPlayer()->setSceneManager(smgr);
		game->getPlayerManager()->getPlayer()->setCamera(cam);
		smgr->loadScene("./media/microfps.irr");
		game->getEventManager()->addHandler("GameHandler", new GameHandler(game));
		meshscenenode * node = static_cast<meshscenenode*>(smgr->getSceneNodeFromName("Map"));
		game->getPhysicsManager()->addCollisionMap(node);
	}
	virtual ~Level1()
	{
		if(smgr) smgr->drop();
	}

	virtual void criticalLoop()
	{
		// Update physics
		game->getPhysicsManager()->updateTimeStep(game->getRenderManager()->getRenderDevice()->getTimer()->getTime());
		game->getPhysicsManager()->updateCollisions();
	}

	virtual void gameLoop()
	{
		stringw caption = L"MicroFPS v0.1.0 Demo - Tech Demo [FPS: ";
		caption += device->getVideoDriver()->getFPS();
		caption += "]";
		device->setWindowCaption(caption.c_str());
	}

	virtual void leave()
	{
	}

	virtual void change()
	{
		device->setInputReceivingSceneManager(smgr);
		device->setEventReceiver(game->getEventManager()->getHandler("GameHandler"));
	}

	virtual MicroFPS::scenemgr getSceneManager() const
	{
		return smgr;
	}

	virtual MicroFPS::GUI* getGUI() const
	{
		return 0;
	}
private:
	MicroFPS::renderer device;
	MicroFPS::scenemgr smgr;
	MicroFPS::camera cam;
	MicroFPS::GameManager * game;
};

/** Menu eventhandler for Irrlicht */
class MenuHandler : public MicroFPS::EventHandler
{
public:
	MenuHandler(MicroFPS::GameManager* g)
		: game(g)
	{
	}

	virtual ~MenuHandler()
	{
	}

	virtual bool OnEvent(const irr::SEvent& event)
	{
		game->getGUIManager()->getCurrent()->injectEvent(event);
		if(event.EventType == irr::EET_KEY_INPUT_EVENT) // Keys
		{
			switch(event.KeyInput.Key)
			{
			case irr::KEY_ESCAPE:
				// Do nothing
				break;
			default:
				break;
			}
		}

		if(event.EventType == irr::EET_MOUSE_INPUT_EVENT) // Mouse
		{
			switch(event.MouseInput.Event)
			{
			case irr::EMIE_LMOUSE_PRESSED_DOWN:
				break;
			default:
				break;
			}
		}
		return true;
	}

	virtual bool operator()(const CEGUI::EventArgs& e)
	{
		// I don't like upcasting.. But this comes from CEGUI docs
		return OnGUIEvent(e);
	}

	virtual bool OnGUIEvent(const CEGUI::EventArgs& e)
	{
		// I don't like upcasting.. But this comes from CEGUI docs
		//const CEGUI::KeyEventArgs key = static_cast<const CEGUI::KeyEventArgs&>(e);
		const CEGUI::MouseEventArgs mouse = static_cast<const CEGUI::MouseEventArgs&>(e);
		if(mouse.window != 0) // Mouse event
		{
			switch(game->getGUIManager()->getCurrent()->getWindowID(mouse.window)) // Switch assigned ID
			{
			case 0: // Exit game button - these are arbitrary indices
				game->getRenderManager()->getRenderDevice()->closeDevice();
				break;
			case 12: // PlayGame button :)
				game->getStateManager()->setCurrentState("Level1");
				break;
			default:
				break;
			}
		}
		return true;
	}

	bool test()
	{
		cout<< "Testing..." << std::endl;
		return true;
	}
private:
	MicroFPS::GameManager * game;
};

template<class T>
void test(bool (T::*func)(), T* ptr)
{
	(ptr->*func)();
}

/** Menu Implementation */
class MainMenu : public MicroFPS::GameState
{
public:
	MainMenu(MicroFPS::GameManager* g)
		: game(g), device(game->getRenderManager()->getRenderDevice())
	{
		smgr = device->getSceneManager()->createNewSceneManager();
		camera cam = smgr->addCameraSceneNode();
		smgr->setActiveCamera(cam);
		gui = game->getGUIManager()->addGeneralMenu("MainMenu", device);
		first = true;

		// Load resources
		gui->loadResources("schemes", "../../datafiles/schemes", GUI::SCHEMES);
		gui->loadResources("imagesets", "../../datafiles/imagesets", GUI::IMAGESETS);
		gui->loadResources("fonts", "../../datafiles/fonts", GUI::FONTS);
		gui->loadResources("looknfeels", "../../datafiles/looknfeel", GUI::LOOKNFEELS);
		gui->loadResources("layouts", "../../datafiles/layouts", GUI::LAYOUTS);
		gui->loadResources("lua_scripts", "../../datafiles/lua_scripts", GUI::LUA_SCRIPTS);

		// Load the scheme data
		//gui->loadScheme("Demo8.scheme");
		gui->loadScheme("OgreTray.scheme");

		// Map window
		//gui->addWindowMapping("WindowsLook/FrameWindow", "CEGUI/FrameWindow", "WindowsLook/FrameWindow",
			//"Falagard/FrameWindow", "WindowsLook/FrameWindow");

		// Load the menu layout :)
		gui->loadLayout("MicroFPS.layout");
		//CEGUI::System::setDefaultMouseCursor("imagesets",
		time = device->getTimer()->getTime();

		game->getEventManager()->addHandler("MainMenuHandler", new MenuHandler(game));
	}
	virtual ~MainMenu()
	{
		//if(gui) game->getGUIManager()->removeGUI(gui->getName());
		if(smgr) smgr->drop();
	}

	virtual inline void criticalLoop()
	{
		MicroFPS::f32 delta = device->getTimer()->getTime()-time;
		time = device->getTimer()->getTime();
		gui->injectTimePulse(delta);
		gui->renderGUI();
	}

	virtual inline void gameLoop()
	{
		stringw caption = L"MicroFPS v0.1.0 Demo - Main Menu [FPS: ";
		caption += device->getVideoDriver()->getFPS();
		caption += "]";
		device->setWindowCaption(caption.c_str());
		//if(device->getTimer()->getTime() >= time+12000)
			//game->getStateManager()->setCurrentState("Level1");
	}

	virtual void leave()
	{
		//device->getCursorControl()->setVisible(false);
	}
	bool w00t(){ cout<<"cool";return true; }

	virtual void change()
	{
		EventHandler * handler = game->getEventManager()->getHandler("MainMenuHandler");
		device->setEventReceiver(handler);
		device->setInputReceivingSceneManager(smgr);
		device->getCursorControl()->setVisible(true);
		game->getGUIManager()->setCurrent("MainMenu");
		// Add event clicks, etc.
		// !! Causes _TERRIBLE_ memory leak upon termination on *nix
		//		related to CEGUI::String double free?
		if(first)
		{
			gui->addEvent("MicroFPS/MainWindow/PlayGame", 12, CEGUI::PushButton::EventClicked, handler);
			gui->addEvent("MicroFPS/MainWindow/ExitGame", 0, CEGUI::PushButton::EventClicked, handler);
			first = false;
		}
	}

	virtual MicroFPS::scenemgr getSceneManager() const
	{
		return smgr;
	}

	virtual MicroFPS::GUI* getGUI() const
	{
		return gui;
	}
private:
	MicroFPS::GameManager* game;
	MicroFPS::renderer device;
	MicroFPS::scenemgr smgr;
	MicroFPS::GUI* gui;
	irr::u32 time;
	bool first;
};

void checkLeaks()
{
	try
	{
		GameManager * game = createGameManager();
		MicroFPS::renderer device = game->getRenderManager()->getRenderDevice();
		game->getStateManager()->addState("Level1", new Level1(game));
		game->getStateManager()->addState("MainMenu", new MainMenu(game));
		game->getStateManager()->setCurrentState("MainMenu");
		game->start();
		game->destroy();
	} catch(const std::runtime_error & e) {
		cout<< "Error: "<< e.what() << std::endl;
	}
}

int main()
{
	checkLeaks();
	::_CrtDumpMemoryLeaks();
	cin.get();
}
