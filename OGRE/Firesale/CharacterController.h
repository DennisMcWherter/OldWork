/**
 * CharacterController.h
 * Character Controller
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef CHARACTERCONTROLLER_H_
#define CHARACTERCONTROLLER_H_

#include "OGRE/OgreString.h"

#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

class Ogre::Camera;
class Ogre::Entity;
class Ogre::SceneManager;
class Ogre::SceneNode;

class CharacterController
{
public:
  CharacterController(Ogre::Camera * Camera, const Ogre::Vector3& position, const Ogre::String& name,
    const Ogre::String& mesh, const Ogre::Vector3& scale, const Ogre::Real& rotMult=0.01f, const Ogre::Real& transMult=0.1f,
    const Ogre::Real& transUp=65.0f, const Ogre::Real& transLower=40.0f);
  virtual ~CharacterController();

  virtual void update(Ogre::Real elapsedTime, OIS::Keyboard * input) = 0;
  virtual void updateCamera(const OIS::MouseEvent& arg);

  Ogre::SceneNode * getMainNode() const { return mMainNode; }
  Ogre::SceneNode * getCameraNode() const { return mCameraNode; }
  Ogre::SceneNode * getTargetNode() const { return mTargetNode; }
  Ogre::Entity * getEntity() const { return mEntity; }

private:
  Ogre::SceneManager * mSceneMgr;
  Ogre::Camera * mCamera;
  Ogre::String mName;
  Ogre::Entity * mEntity;
  Ogre::SceneNode * mMainNode, * mTargetNode, * mCameraNode;
  const Ogre::Real rotationMultiplier, translateMultiplier, translateUpperBound, translateLowerBound;

protected: /** Give inheriting class access to physics */

};

#endif // CHARACTERCONTROLLER_H_
