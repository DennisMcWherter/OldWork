/**
 * CharacterController.h
 * Character Controller
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreCamera.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreSceneManager.h"

#include "CharacterController.h"

CharacterController::CharacterController(Ogre::Camera * Camera, const Ogre::Vector3& position,
  const Ogre::String& name, const Ogre::String& mesh, const Ogre::Vector3& scale, const Ogre::Real& rotMult, const Ogre::Real& transMult, const Ogre::Real& transUp, const Ogre::Real& transLower)
  : mSceneMgr(Camera->getSceneManager()), mCamera(Camera), mName(name), rotationMultiplier(rotMult),
  translateMultiplier(transMult), translateUpperBound(transUp), translateLowerBound(transLower)
{
  mEntity = mSceneMgr->createEntity(mName, mesh);
  mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);
  mTargetNode = mMainNode->createChildSceneNode(mName + "_target");
  mCameraNode = mTargetNode->createChildSceneNode(mName + "_camera", Ogre::Vector3(0, 10, -50));
  mMainNode->setPosition(position);
  mMainNode->scale(scale);

  mMainNode->attachObject(mEntity);
  mCameraNode->attachObject(mCamera);
  mCamera->lookAt(mMainNode->_getDerivedPosition());
}

CharacterController::~CharacterController()
{
  mMainNode->detachAllObjects();
  mCameraNode->detachAllObjects();
  mTargetNode->detachAllObjects();

  mSceneMgr->destroyEntity(mEntity);
  mSceneMgr->destroySceneNode(mMainNode);
}

void CharacterController::updateCamera(const OIS::MouseEvent& arg)
{
  // Store OIS output for how much we have moved our mouse
  const Ogre::Real x(1.f*(arg.state.X.rel));
  const Ogre::Real y(1.f*(arg.state.Y.rel));

  // w values for quaternion rotations
  const Ogre::Real wY(-0.5f*Ogre::Math::ACos(rotationMultiplier*x).valueDegrees());

  // Quaternion rotation
  Ogre::Quaternion rotY(wY, 0, x, 0);

  // Quaternion rotation
  mTargetNode->rotate(rotY, Ogre::Node::TS_LOCAL);

  // Move camera up/down and out/in respectively
  Ogre::Real transY(translateMultiplier*y);
  Ogre::Real dist(mCameraNode->getPosition().distance(mTargetNode->getPosition()));
  if((dist < translateUpperBound && dist > translateLowerBound) || (dist >= translateUpperBound && transY < 0) ||
    (dist <= translateLowerBound && transY > 0)) {
      mCameraNode->translate(0, transY, -2*transY, Ogre::Node::TS_LOCAL);
  }
}