/**
 * GenericMotionState.h
 * Generic Bullet Motion State for Ogre
 *
 * 17 August 2011
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 */

#ifndef GENERICMOTIONSTATE_H_
#define GENERICMOTIONSTATE_H_

class Ogre::SceneNode;

class GenericMotionState : public btMotionState
{
public:
  GenericMotionState(Ogre::SceneNode * node);
  virtual ~GenericMotionState(){}

  void setNode(Ogre::SceneNode * node);
  virtual void getWorldTransform(btTransform& trans) const;
  virtual void setWorldTransform(const btTransform& trans);

protected:
  Ogre::SceneNode * mNode;
};

#endif // GENERICMOTIONSTATE_H_
