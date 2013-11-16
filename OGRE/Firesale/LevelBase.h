/**
 * LevelBase.h
 * Level Base - abstract base class for all levels
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef LEVELBASE_H_
#define LEVELBASE_H_

#include "OGRE/OgreFrameListener.h"

#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

class Ogre::RenderWindow;
class Ogre::Root;
class OIS::InputManager;
class LevelManager;

enum LEVEL_STATUS
{
  RUNNING,
  NEXT_LEVEL,
  SHUTDOWN
};

class LevelBase : public Ogre::FrameListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
  LevelBase(LevelManager * Levels);
  virtual ~LevelBase();

  // For scene
  virtual void enter() = 0;
  virtual void createScene() = 0;
  virtual void exit() = 0;

  // FrameListener
  virtual bool frameStarted(const Ogre::FrameEvent& evt);
  virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
  virtual bool frameEnded(const Ogre::FrameEvent& evt);

  // KeyListener
  virtual bool keyPressed(const OIS::KeyEvent& arg) = 0;
  virtual bool keyReleased(const OIS::KeyEvent& arg) = 0;

  // MouseListener
  virtual bool mouseMoved(const OIS::MouseEvent& arg) = 0;
  virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id) = 0;
  virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id) = 0;
  
  virtual LEVEL_STATUS getStatus() const;

protected:
  virtual void setStatus(LEVEL_STATUS status);
  virtual Ogre::Root * getRoot() const;
  virtual Ogre::RenderWindow * getWindow() const;
  virtual OIS::InputManager * getInputManager() const;
  virtual OIS::Keyboard * getKeyboard() const;
  virtual OIS::Mouse * getMouse() const;
  virtual LevelManager * getLevelManager() const;

  // We'll give direct access to inheriting class for our physics members

private:
  LevelManager * mManager;
  LEVEL_STATUS mStatus;
};

#endif // LEVELBASE_H_
