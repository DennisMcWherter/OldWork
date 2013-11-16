/**
 * OgreCharacterController.h
 * Ogre Character Controller
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef OGRECHARACTERCONTROLLER_H_
#define OGRECHARACTERCONTROLLER_H_

#define CAMERA_ALLOWANCE 0.1f

#include "CharacterController.h"

class Ogre::AnimationState;
class Ogre::Entity;

enum OGRE_ANIMATION_STATE
{
  IDLE,
  RUN,
  DRAWSWORDS,
  SLICE
};

class OgreCharacterController : public CharacterController
{
public:
  OgreCharacterController(Ogre::Camera * Camera, const Ogre::String& name, const Ogre::Vector3& position=Ogre::Vector3(0,0,0));
  virtual ~OgreCharacterController();

  virtual void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
  virtual void animate(Ogre::Real elapsedTime, OGRE_ANIMATION_STATE state);

private:
  // !! Important: Methods to abstract certain animations
  virtual void drawSwords(Ogre::AnimationState *& animTop, Ogre::Entity * ent);
  virtual void slice(Ogre::AnimationState *& animTop, Ogre::Entity * ent);

  Ogre::AnimationState * lastTop, * lastBase;
  Ogre::Entity * mSword1, * mSword2;
  bool swordsOut;
  bool sliceDir;
  Ogre::Real animTimer;
};

#endif // OGRECHARACTERCONTROLLER_H_
