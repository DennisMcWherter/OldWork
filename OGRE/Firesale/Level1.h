/**
 * Level1.h
 * Level 1
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef LEVEL1_H_
#define LEVEl1_H_

#include "LevelBase.h"

class Ogre::Camera;
class Ogre::ResourceGroupManager;
class Ogre::SceneManager;
class CharacterController;

class Level1 : public LevelBase
{
public:
  Level1(LevelManager * Levels);
  virtual ~Level1();

  // For scene
  virtual void enter();
  virtual void createScene();
  virtual void exit();

  // FrameListener
  virtual bool frameStarted(const Ogre::FrameEvent& evt);

  // KeyListener
  virtual bool keyPressed(const OIS::KeyEvent& arg);
  virtual bool keyReleased(const OIS::KeyEvent& arg);

  // MouseListener
  virtual bool mouseMoved(const OIS::MouseEvent& arg);
  virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
  virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

private:
  Ogre::SceneManager * mSceneMgr;
  Ogre::ResourceGroupManager& mResGroupMgr;
  Ogre::Camera * mCamera;
  CharacterController * mPlayer;
  bool initial;
};

#endif // LEVEL1_H_
