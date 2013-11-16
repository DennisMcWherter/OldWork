/**
 * Level1.cpp
 * Demo level
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#include "OGRE/OgreCamera.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreLight.h"
#include "OGRE/OgreMeshManager.h"
#include "OGRE/OgrePlane.h"
#include "OGRE/OgreRoot.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreViewport.h"

#include "OIS/OISException.h"
#include "OIS/OISInputManager.h"
#include "OIS/OISKeyboard.h"

#include "Level1.h"

#define PI Ogre::Math::PI

Level1::Level1(Ogre::Root * root, Ogre::RenderWindow * window)
  : mRoot(root), mWindow(window), mRmgr(Ogre::ResourceGroupManager::getSingleton()),
  pSmgr(root->createSceneManager(0)), pCamera(pSmgr->createCamera("PlayerCam")), pViewport(0),
  mInput(0), mKeyboard(0), mMouse(0), player(0)
{
  pViewport = mWindow->addViewport(pCamera);
  pCamera->setAspectRatio(Ogre::Real(pViewport->getActualWidth())/Ogre::Real(pViewport->getActualHeight()));

  // Init input system
  OIS::ParamList pl;
  int hwnd = 0;
  std::ostringstream wnd;
  mWindow->getCustomAttribute("WINDOW", &hwnd);
  wnd << hwnd;
  pl.insert(std::make_pair(std::string("WINDOW"), wnd.str()));

  mInput = OIS::InputManager::createInputSystem(pl);
  mKeyboard = static_cast<OIS::Keyboard*>(mInput->createInputObject(OIS::OISKeyboard, true));
  mMouse = static_cast<OIS::Mouse*>(mInput->createInputObject(OIS::OISMouse, true));
  mKeyboard->setEventCallback(this);
  mMouse->setEventCallback(this);

  loadResources();

  player = new OgreCharacter("OgrePlayer", pSmgr, "Level1");

  pCamera->setPosition(Ogre::Vector3(0, 0, 70));
  pCamera->lookAt(Ogre::Vector3(0,0,0));
  pCamera->setNearClipDistance(5);
  pCamera->yaw(Ogre::Radian(PI));
  player->getCameraNode()->attachObject(pCamera);
}

Level1::~Level1()
{
  pSmgr->clearScene();

  pSmgr->destroyCamera(pCamera);
  mRoot->destroySceneManager(pSmgr);
  mWindow->removeViewport(0);

  // Unload input system
  mInput->destroyInputObject(mKeyboard);
  mInput->destroyInputObject(mMouse);
  OIS::InputManager::destroyInputSystem(mInput);

  unloadResources();

  //delete player;
}

void Level1::loadResources()
{
  mRmgr.addResourceLocation("../../media", "FileSystem", "Level1");
  mRmgr.addResourceLocation("../../media/models", "FileSystem", "Level1");
  mRmgr.addResourceLocation("../../media/materials/textures", "FileSystem", "Level1");
  mRmgr.addResourceLocation("../../media/materials/scripts", "FileSystem", "Level1");
  //mRmgr.addResourceLocation("../../media/materials/programs", "FileSystem", "Level1");
  mRmgr.addResourceLocation("../../media/packs/Sinbad.zip", "Zip", "Level1");

  mRmgr.initialiseResourceGroup("Level1");
}

void Level1::unloadResources()
{
  mRmgr.unloadResourceGroup("Level1");
}

Ogre::SceneNode * Level1::createNode(const Ogre::String& name, const Ogre::String& mesh, const Ogre::String& id)
{
  Ogre::Entity * entity  = pSmgr->createEntity(name, mesh);
  Ogre::SceneNode * node = pSmgr->getRootSceneNode()->createChildSceneNode(id);
  node->attachObject(entity);
  entity->setCastShadows(true);
  return node;
}

void Level1::createScene()
{
  pSmgr->setAmbientLight(Ogre::ColourValue::White);
 // pSmgr->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.9, 0.9, 0.9), 0.00100000047f, 0.0f, 100.0f);
  pSmgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

  Ogre::SceneNode * penguin = createNode("Penguin", "penguin.mesh", "Penguin");
  penguin->setPosition(0, 20, 100);
  penguin->yaw(Ogre::Degree(180.0f));

  Ogre::SceneNode * ninja = createNode("Ninja", "ninja.mesh", "Ninja");
  ninja->scale(0.25, 0.25, 0.25);
  ninja->setPosition(-50, 10, 100);

  // Light
  Ogre::Light * light = pSmgr->createLight("MainLight");
  light->setType(Ogre::Light::LT_DIRECTIONAL);
  light->setDiffuseColour(Ogre::ColourValue::White);
  light->setDirection(Ogre::Vector3(0, -1, 1));

  // Ground
  Ogre::Plane gplane(Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, 0));
  Ogre::MeshManager::getSingleton().createPlane("Ground", "Level1", gplane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
  Ogre::Entity * gent = pSmgr->createEntity("ground", "Ground");
  Ogre::SceneNode * ground = pSmgr->getRootSceneNode()->createChildSceneNode("GroundNode");
  ground->attachObject(gent);
  gent->setMaterialName("Examples/Rockwall");

  pSmgr->setSkyDome(true, "Examples/CloudySky", 7, 8, 4000.0f, true, Ogre::Quaternion::IDENTITY, 16, 16, -1, "Level1");
}

bool Level1::frameStarted(const Ogre::FrameEvent& evt)
{
  mKeyboard->capture();
  mMouse->capture();
  player->update(evt.timeSinceLastFrame, mKeyboard);
  // TODO: X, Y, Z comparison for rotation about axis w/ mouse
  return !mKeyboard->isKeyDown(OIS::KC_ESCAPE);
}

bool Level1::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  return true;
}

bool Level1::keyPressed(const OIS::KeyEvent& arg)
{
  return true;
}

bool Level1::keyReleased(const OIS::KeyEvent& arg)
{
  return true;
}

// 0 = Disabled
// 1 = Direction
// 2 = Reverse direction
bool Level1::mouseMoved(const OIS::MouseEvent& arg)
{
  if(arg.state.buttonDown(OIS::MB_Left)) {
    const int cPos[3] = {arg.state.X.rel, arg.state.Y.rel, arg.state.Z.rel};
    int left = 0, up = 0;

    if(cPos[0] < lastPos[0])
      left = 1;
    else if(cPos[0] > lastPos[0])
      left = 2;
    if(cPos[1] < lastPos[1])
      up = 1;
    else if(cPos[1] > lastPos[1])
      up = 2;

    const int dx = cPos[0] - lastPos[0];
    const int dy = cPos[1] - lastPos[1];
    const Ogre::Real x = (dx == 0) ? 0 : 100/dx;
    const Ogre::Real y = (dy == 0) ? 0 : 100/dy;
    player->update(x, y, left, up);

    *lastPos = *cPos;
  }
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
