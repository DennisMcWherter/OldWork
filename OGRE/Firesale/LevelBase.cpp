/**
 * LevelBase.cpp
 * Level Base - abstract base class for all levels
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreException.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreWindowEventUtilities.h"

#include "BtOgreGP.h"

#include "LevelManager.h"
#include "LevelBase.h"

LevelBase::LevelBase(LevelManager * Levels)
{
  if(Levels == 0)
    throw Ogre::Exception(997, "Null level manager passed to LevelBase::LevelBase()", "", "", __FILE__, __LINE__);
  mManager = Levels;
  mStatus = RUNNING;

  // physics setup
}

LevelBase::~LevelBase()
{
  // Clean up physics
}

LEVEL_STATUS LevelBase::getStatus() const
{
  return mStatus;
}

Ogre::Root * LevelBase::getRoot() const
{
  return mManager->getRoot();
}

Ogre::RenderWindow * LevelBase::getWindow() const
{
  return mManager->getWindow();
}

OIS::InputManager * LevelBase::getInputManager() const
{
  return mManager->getInputManager();
}

OIS::Keyboard * LevelBase::getKeyboard() const
{
  return mManager->getKeyboard();
}

OIS::Mouse * LevelBase::getMouse() const
{
  return mManager->getMouse();
}

LevelManager * LevelBase::getLevelManager() const
{
  return mManager;
}

void LevelBase::setStatus(LEVEL_STATUS status)
{
  mStatus = status;
}

bool LevelBase::frameStarted(const Ogre::FrameEvent& evt)
{
  // OIS for mouse/keyboard input
  getKeyboard()->capture();
  getMouse()->capture();

  return !getKeyboard()->isKeyDown(OIS::KC_ESCAPE);
}

bool LevelBase::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  return true;
}

bool LevelBase::frameEnded(const Ogre::FrameEvent& evt)
{
  Ogre::WindowEventUtilities::messagePump();
  return !getWindow()->isClosed();
}
