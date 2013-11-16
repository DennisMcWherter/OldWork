/**
 * Character.h
 * Character class
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "OGRE/OgreSceneNode.h"

class Ogre::Entity;
class Ogre::SceneManager;

class OIS::Keyboard;

class Character
{
public:
  virtual void update(Ogre::Real elapsedTime, OIS::Keyboard * input) = 0;
  virtual void update(Ogre::Real deltaX, Ogre::Real deltaY, int left, int up) = 0;

  Ogre::SceneNode * getSightNode() const { return mSight; }
  Ogre::SceneNode * getCameraNode() const { return mCam; }
  Ogre::Vector3 getWorldPosition() const { return mMain->_getDerivedPosition(); }

protected:
  Ogre::SceneNode * mMain;
  Ogre::SceneNode * mSight;
  Ogre::SceneNode * mCam;
  Ogre::Entity * mEntity;
  Ogre::SceneManager * mSmgr;
};

#endif // CHARACTER_H_
