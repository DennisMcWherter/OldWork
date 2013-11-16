/**
 * OgreCharacter.cpp
 * Character class
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#ifndef OGRECHARACTER_H_
#define OGRECHARACTER_H_

#include "Character.h"

class OgreCharacter : public Character
{
public:
  OgreCharacter(const Ogre::String& name, Ogre::SceneManager * smgr, const Ogre::String& group);
  virtual ~OgreCharacter();

  virtual void update(Ogre::Real elapsedTime, OIS::Keyboard * input);
  virtual void update(Ogre::Real deltaX, Ogre::Real deltaY, int left, int up);

private:
  bool mSwordDrawn;
  bool mSliceToggle;
  Ogre::Entity * mSword1, * mSword2;
};

#endif OGRECHARACTER_H_ // OGRECHARACTER_H_
