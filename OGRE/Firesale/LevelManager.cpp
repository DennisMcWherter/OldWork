/**
 * LevelManager.cpp
 * Level Manager
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreException.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreRoot.h"

#include "OIS/OISException.h"
#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

#include "LevelManager.h"
#include "LevelBase.h"

#include "Level1.h"

LevelManager::LevelManager(Ogre::Root * Root, Ogre::RenderWindow * Window)
{
  if(Root == 0 || Window == 0)
    throw Ogre::Exception(998, "Null parameters passed to LevelManager::LevelManager()", "", "", __FILE__, __LINE__);
  mRoot = Root;
  mWindow = Window;
  mCurrent = 0;
  // OIS stuff
  try {
    OIS::ParamList pl;
    pl.insert(std::make_pair(std::string("WINDOW"), getWindowHandle()));

    mInput = OIS::InputManager::createInputSystem(pl);
    mKey   = static_cast<OIS::Keyboard*>(mInput->createInputObject(OIS::OISKeyboard, true));
    mMouse = static_cast<OIS::Mouse*>(mInput->createInputObject(OIS::OISMouse, true));

    addLevels();

  } catch(const OIS::Exception& e) {
    // Convert OIS::Exception to Ogre::Exception
    throw Ogre::Exception(999, e.what(), "", "", __FILE__, __LINE__);
  }
}

LevelManager::~LevelManager()
{
  // Free memory allocated for levels
  std::map<std::string, LevelBase*>::iterator it;
  for(it=mLevels.begin();it!=mLevels.end();it++)
    delete it->second;

  // Destroy input system
  mInput->destroyInputObject(mKey);
  mInput->destroyInputObject(mMouse);
  OIS::InputManager::destroyInputSystem(mInput);
}

void LevelManager::run()
{
  if(mCurrent == 0)
    return;
  mRoot->startRendering();
}

Ogre::Root * LevelManager::getRoot() const
{
  return mRoot;
}

Ogre::RenderWindow * LevelManager::getWindow() const
{
  return mWindow;
}

LevelBase * LevelManager::getCurrentLevel() const
{
  return mCurrent;
}

OIS::InputManager * LevelManager::getInputManager() const
{
  return mInput;
}

OIS::Keyboard * LevelManager::getKeyboard() const
{
  return mKey;
}

OIS::Mouse * LevelManager::getMouse() const
{
  return mMouse;
}

std::string LevelManager::getWindowHandle() const
{
  int hwnd = 0;
  std::ostringstream stream;
  mWindow->getCustomAttribute("WINDOW", &hwnd);
  stream << hwnd;
  return stream.str();
}

void LevelManager::setCurrentLevel(const std::string& name)
{
  LevelBase * level = mLevels[name], * old = mCurrent;
  if(!level || mCurrent == level)
    return;
  mCurrent = level;
  mCurrent->enter();
  if(old)
    old->exit();
}

void LevelManager::addLevels()
{
  try {
    mLevels["Level1"] = new Level1(this);
    setCurrentLevel("Level1");
  } catch(const Ogre::Exception& e) {
    throw e;
  }
}
