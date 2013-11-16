/**
 * Level1.h
 * Demo level
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#ifndef LEVEL1_H_
#define LEVEL1_H_

#include "OGRE/OgreFrameListener.h"
#include "OGRE/OgreRoot.h"

#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

#include "OgreCharacter.h"

class Ogre::Camera;
class Ogre::RenderWindow;
class Ogre::ResourceGroupManager;
class Ogre::SceneNode;
class Ogre::Viewport;
class OIS::InputManager;
class OIS::Keyboard;

class Level1 : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
  Level1(Ogre::Root * root, Ogre::RenderWindow* window);
  virtual ~Level1();

  virtual void loadResources();
  virtual void unloadResources();
  virtual void createScene();
  virtual Ogre::SceneNode * createNode(const Ogre::String& name, const Ogre::String& mesh, const Ogre::String& id);

  // FrameListener
  virtual bool frameStarted(const Ogre::FrameEvent& evt);
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

  // KeyListener
  virtual bool keyPressed(const OIS::KeyEvent& arg);
  virtual bool keyReleased(const OIS::KeyEvent& arg);

  // MouseListener
  virtual bool mouseMoved(const OIS::MouseEvent& arg);
  virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
  virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

private:
  Ogre::Root * mRoot;
  Ogre::RenderWindow * mWindow;
  Ogre::ResourceGroupManager& mRmgr;
  Ogre::SceneManager * pSmgr;
  Ogre::Camera * pCamera;
  Ogre::Viewport * pViewport;
  OIS::InputManager * mInput;
  OIS::Keyboard * mKeyboard;
  OIS::Mouse * mMouse;
  OgreCharacter * player;
  int lastPos[3];
};

#endif // LEVEL1_H_
