/**
 * GenericMotionState.cpp
 * Generic Bullet Motion State for Ogre
 *
 * 17 August 2011
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 */

#include "OGRE/OgreException.h"
#include "OGRE/OgreSceneNode.h"

#include "GenericMotionState.h"

GenericMotionState::GenericMotionState(Ogre::SceneNode * node)
  : mNode(node), mCM(btTransform::getIdentity())
{
  if(mNode == 0)
    throw Ogre::Exception(996, "NULL Pointer", "", "", __FILE__, __LINE__);
  Ogre::Quaternion rot(mNode->getOrientation());
  Ogre::Vector3 pos(mNode->getPosition());
  mTransform = btTransform(btQuaternion(rot.x, rot.y, rot.z, rot.w), btVector3(pos.x, pos.y, pos.z));
}

void GenericMotionState::setNode(Ogre::SceneNode * node)
{
  mNode = node;
}

void GenericMotionState::getWorldTransform(btTransform& trans) const
{
  trans = mCM.inverse() * mTransform;
}

void GenericMotionState::setWorldTransform(const btTransform& trans)
{
  if(mNode == 0)
    throw Ogre::Exception(996, "NULL Pointer", "", "", __FILE__, __LINE__);

  mTransform = trans;

  btTransform transform(trans*mCM.inverse());
  btQuaternion rot(transform.getRotation());
  btVector3 pos(transform.getOrigin());

  mNode->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
  mNode->setPosition(pos.x(), pos.y(), pos.z());
}
