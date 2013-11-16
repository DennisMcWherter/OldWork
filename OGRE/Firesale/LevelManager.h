/**
 * LevelManager.h
 * Level Manager
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

#include <map>
#include <string>

#include "OIS/OISInputManager.h"

class Ogre::RenderWindow;
class Ogre::Root;
class OIS::Keyboard;
class OIS::Mouse;
class LevelBase;

class LevelManager
{
public:
  LevelManager(Ogre::Root * Root, Ogre::RenderWindow * Window);
  virtual ~LevelManager();

  Ogre::Root * getRoot() const;
  Ogre::RenderWindow * getWindow() const;
  OIS::InputManager * getInputManager() const;
  OIS::Keyboard * getKeyboard() const;
  OIS::Mouse * getMouse() const;
  LevelBase * getCurrentLevel() const;

  void setCurrentLevel(const std::string& name);

  void run();

protected:
  std::string getWindowHandle() const;
  void addLevels();

private:
  Ogre::Root * mRoot;
  Ogre::RenderWindow * mWindow;
  OIS::InputManager * mInput;
  OIS::Keyboard * mKey;
  OIS::Mouse * mMouse;
  LevelBase * mCurrent;
  std::map<std::string, LevelBase*> mLevels;
};

#endif // LEVELMANAGER_H_
