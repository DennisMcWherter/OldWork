/**
 * OgreCharacter.cpp
 * Character class
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#include "OGRE/OgreEntity.h"
#include "OGRE/OgreSceneManager.h"

#include "OIS/OISKeyboard.h"
#include "OIS/OISMouse.h"

#include "OgreCharacter.h"


// NOTE: Should really use some sort of controller for all of this (i.e. look at SinbadCharacterController.h)
OgreCharacter::OgreCharacter(const Ogre::String& name, Ogre::SceneManager * smgr, const Ogre::String& group)
{
  mSmgr = smgr;

  mMain  = mSmgr->getRootSceneNode()->createChildSceneNode(name);
  mSight = mMain->createChildSceneNode(name + "_sight", Ogre::Vector3(0, 0, 100));
  mCam   = mMain->createChildSceneNode(name + "_cam", Ogre::Vector3(0, 5, -50));

  mEntity = mSmgr->createEntity(name, "Sinbad.mesh", group);
  mSword1 = mSmgr->createEntity("Sword1", "Sword.mesh");
  mSword2 = mSmgr->createEntity("Sword2", "Sword.mesh");
  mEntity->attachObjectToBone("Sheath.L", mSword1);
  mEntity->attachObjectToBone("Sheath.R", mSword2);
  mEntity->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

  mMain->attachObject(mEntity);
  mMain->scale(3, 3, 3);
  mMain->setPosition(0, 15, 0);

  mSwordDrawn = false;
  mSliceToggle = false;
}

OgreCharacter::~OgreCharacter()
{
  mMain->detachAllObjects();
  delete mEntity;
  mMain->removeAndDestroyAllChildren();
  mSmgr->destroySceneNode(mMain);
}

// This is hacky - will need to create a character controller in reality
void OgreCharacter::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
  Ogre::AnimationState * animTop = 0, * animBot = 0;
  if(input->isKeyDown(OIS::KC_W)) {
    animTop = mEntity->getAnimationState("RunTop");
    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->addTime(elapsedTime);

    animBot = mEntity->getAnimationState("RunBase");
    animBot->setEnabled(true);
    animBot->setLoop(true);
    animBot->addTime(elapsedTime);

    mMain->translate(mMain->getOrientation() * Ogre::Vector3(0, 0, 100 * elapsedTime));
  } else if(input->isKeyDown(OIS::KC_S)) {
    animTop = mEntity->getAnimationState("RunTop");
    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->addTime(elapsedTime);

    animBot = mEntity->getAnimationState("RunBase");
    animBot->setEnabled(true);
    animBot->setLoop(true);
    animBot->addTime(elapsedTime);

    mMain->translate(mMain->getOrientation() * Ogre::Vector3(0, 0, -50 * elapsedTime));
  } else {
    mEntity->getAnimationState("RunTop")->setEnabled(false);
    mEntity->getAnimationState("RunBase")->setEnabled(false);
  }

  if(input->isKeyDown(OIS::KC_A))
    mMain->yaw(Ogre::Radian(2*elapsedTime));
  if(input->isKeyDown(OIS::KC_D))
    mMain->yaw(Ogre::Radian(-2*elapsedTime));

  if(input->isKeyDown(OIS::KC_RETURN)) {
    animTop = mEntity->getAnimationState("DrawSwords");

    mEntity->detachAllObjectsFromBone();
    mEntity->attachObjectToBone((mSwordDrawn) ? "Sheath.L" : "Handle.L", mSword1);
    mEntity->attachObjectToBone((mSwordDrawn) ? "Sheath.R" : "Handle.R", mSword2);

    mEntity->getAnimationState("HandsClosed")->setEnabled(!mSwordDrawn);
    mEntity->getAnimationState("HandsRelaxed")->setEnabled(mSwordDrawn);

    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->setLength(Ogre::Real(1));
    animTop->addTime(elapsedTime);

    mSwordDrawn = !mSwordDrawn;
  } else {
    mEntity->getAnimationState("DrawSwords")->setEnabled(false);
  }

  if(input->isKeyDown(OIS::KC_SPACE)) {
    animTop = mEntity->getAnimationState((mSliceToggle) ? "SliceVertical" : "SliceHorizontal");
    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->setLength(Ogre::Real(1));
    animTop->addTime(elapsedTime);

    mSliceToggle = !mSliceToggle;
  } else {
    mEntity->getAnimationState("SliceVertical")->setEnabled(false);
    mEntity->getAnimationState("SliceHorizontal")->setEnabled(false);
  }

  if(input->isKeyDown(OIS::KC_E)) {
    animTop = mEntity->getAnimationState("Dance");
    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->addTime(elapsedTime);
  } else {
    mEntity->getAnimationState("Dance")->setEnabled(false);
  }

  // default animations
  if(animTop == 0 && animBot == 0)
  {
    animTop = mEntity->getAnimationState("IdleTop");
    animBot = mEntity->getAnimationState("IdleBase");

    animTop->setEnabled(true);
    animBot->setEnabled(true);

    animTop->setLoop(true);
    animBot->setLoop(true);

    animTop->addTime(elapsedTime);
    animBot->addTime(elapsedTime);
  }
}

void OgreCharacter::update(Ogre::Real deltaX, Ogre::Real deltaY, int left, int up)
{
  // This code is crumby - need to find a way to detect direction
  // and change accordingly
 if(left == 1)
    mCam->yaw(Ogre::Radian(2*deltaY));
 else if(left == 2)
    mCam->yaw(Ogre::Radian(-2*deltaY));
 /*if(up == 1)
   mCam->pitch(Ogre::Radian(2*elapsedTime));
 else if(up == 2)
   mCam->pitch(Ogre::Radian(-2*elapsedTime));*/
}
