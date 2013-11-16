/**
 * Level1.cpp
 * Level 1
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreCamera.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreLight.h"
#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgrePlane.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreResourceGroupManager.h"
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreViewport.h"

#include "Level1.h"
#include "OgreCharacterController.h"

Level1::Level1(LevelManager * Levels)
  : LevelBase(Levels), mSceneMgr(0), mResGroupMgr(Ogre::ResourceGroupManager::getSingleton()), mCamera(0),
  mPlayer(0), initial(true)
{
}

Level1::~Level1()
{
  delete mPlayer;
  if(mSceneMgr)
  {
    mSceneMgr->clearScene();
    mSceneMgr->destroyCamera(mCamera);
    getRoot()->destroySceneManager(mSceneMgr);
  }
  if(mResGroupMgr.resourceGroupExists("Level1"))
    mResGroupMgr.unloadResourceGroup("Level1");
}

void Level1::enter()
{
  // Add this listener
  getRoot()->addFrameListener(this);

  // Set input callbacks here
  getKeyboard()->setEventCallback(this);
  getMouse()->setEventCallback(this);

  // Load resources
  if(!mResGroupMgr.resourceGroupExists("Level1")) {
    mResGroupMgr.addResourceLocation("../../media/packs/Sinbad.zip", "Zip", "Level1");
    mResGroupMgr.addResourceLocation("../../media/models", "FileSystem", "Level1");
    mResGroupMgr.addResourceLocation("../../media/Level1/textures", "FileSystem", "Level1");
    mResGroupMgr.addResourceLocation("../../media/Level1/programs", "FileSystem", "Level1");
    mResGroupMgr.addResourceLocation("../../media/Level1/scripts", "FileSystem", "Level1");
    mResGroupMgr.initialiseResourceGroup("Level1");
  }

  // Create scene manager if it does not exist
  if(!mSceneMgr)
    mSceneMgr = getRoot()->createSceneManager(Ogre::ST_GENERIC, "Level1SceneMgr");

  if(!mCamera)
    mCamera = mSceneMgr->createCamera("PlayerCam");

  // Shoud always have a viewport?
  Ogre::Viewport * vp = getWindow()->getViewport(0);
  vp->setCamera(mCamera);
  
  // Reset camera aspect ratio (Width : Height)
  mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth())/Ogre::Real(vp->getActualHeight()));

  if(initial) {
    mCamera->setPosition(Ogre::Vector3(0,0,70));
    mCamera->lookAt(0, 0, 0);
    mCamera->setNearClipDistance(5);
    initial = false;
  }

  // Create player
  mPlayer = new OgreCharacterController(mCamera, "OgrePlayer", Ogre::Vector3(0, 15, 0));

  // Create the scene
  createScene();
}

void Level1::createScene()
{
  Ogre::MeshManager& mmgr = Ogre::MeshManager::getSingleton();

  mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  mSceneMgr->setSkyDome(true, "Examples/CloudySky", 10.0f, 10.0f, 10000.0f, true,
    Ogre::Quaternion::IDENTITY, 16, 16, -1, "Level1");

  // Add a light
  Ogre::Light * light = mSceneMgr->createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(Ogre::ColourValue::White);
  light->setDirection(Ogre::Vector3(0, -1, 1));
  
  // Add a surface for debugging (so we can see things happen!)
  Ogre::Plane gplane(Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0));
  mmgr.createPlane("Ground", "Level1", gplane, 3000, 3000, 16, 16, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
  Ogre::Entity * groundEnt = mSceneMgr->createEntity("GroundEntity", "Ground");
  Ogre::SceneNode * ground = mSceneMgr->getRootSceneNode()->createChildSceneNode("GroundNode");
  ground->attachObject(groundEnt);
  groundEnt->setMaterialName("Ocean2_Cg");
  ground->setPosition(0, 0, 0);

  // Random penguin cuz I think penguins are funny.. lol
  Ogre::Entity * pent = mSceneMgr->createEntity("Penguin", "penguin.mesh");
  Ogre::SceneNode * penguin = mSceneMgr->getRootSceneNode()->createChildSceneNode("Penguin");
  penguin->attachObject(pent);
  penguin->setPosition(0, 10, 50);
}

void Level1::exit()
{
  getRoot()->removeFrameListener(this);
}

bool Level1::frameStarted(const Ogre::FrameEvent& evt)
{
  // Use default frameStarted(...) for now
  bool capture = LevelBase::frameStarted(evt);

  mPlayer->update(evt.timeSinceLastFrame, getKeyboard());

  return capture;
}

bool Level1::keyPressed(const OIS::KeyEvent& arg)
{
  return true;
}

bool Level1::keyReleased(const OIS::KeyEvent& arg)
{
  return true;
}

bool Level1::mouseMoved(const OIS::MouseEvent& arg)
{
  if(arg.state.buttonDown(OIS::MB_Left))
    mPlayer->updateCamera(arg);
  return true;
}

bool Level1::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
  return true;
}

bool Level1::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
  return true;
}
