/**
 * OgreCharacterController.cpp
 * Ogre Character Controller
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreAnimationState.h"
#include "OGRE/OgreEntity.h"
#include "OGRE/OgreQuaternion.h"
#include "OGRE/OgreSceneManager.h"
#include "OGRE/OgreSceneNode.h"
#include "OGRE/OgreSkeletonInstance.h"

#include "OIS/OISMouse.h"

#include "OgreCharacterController.h"

OgreCharacterController::OgreCharacterController(Ogre::Camera * Camera, const Ogre::String& name, const Ogre::Vector3& position)
  : CharacterController(Camera, position, name, "Sinbad.mesh", Ogre::Vector3(3, 3, 3)), lastTop(0), lastBase(0), 
  mSword1(0), mSword2(0), swordsOut(false), sliceDir(false), animTimer(0)
{
  Ogre::SceneManager * smgr = Camera->getSceneManager();
  Ogre::Entity * ent = getEntity();

  ent->getSkeleton()->setBlendMode(Ogre::ANIMBLEND_CUMULATIVE);

  mSword1 = smgr->createEntity("Sword1", "Sword.mesh");
  mSword2 = smgr->createEntity("Sword2", "Sword.mesh");
  ent->attachObjectToBone("Sheath.L", mSword1);
  ent->attachObjectToBone("Sheath.R", mSword2);

  getTargetNode()->setFixedYawAxis(true);
}

OgreCharacterController::~OgreCharacterController()
{
}

void OgreCharacterController::update(Ogre::Real elapsedTime, OIS::Keyboard * input)
{
  Ogre::SceneNode * node = getMainNode();
  OGRE_ANIMATION_STATE state = IDLE;

  if(input->isKeyDown(OIS::KC_W)) {
    node->translate(node->getOrientation() * Ogre::Vector3(0, 0, elapsedTime*100));
    state = RUN;
  }
  if(input->isKeyDown(OIS::KC_S)) {
    node->translate(node->getOrientation() * Ogre::Vector3(0, 0, elapsedTime*-50));
    state = RUN;
  }
  if(input->isKeyDown(OIS::KC_A)) {
    node->yaw(Ogre::Radian(2*elapsedTime));
  }
  if(input->isKeyDown(OIS::KC_D))
    node->yaw(Ogre::Radian(-2*elapsedTime));

  if(input->isKeyDown(OIS::KC_RETURN)) {
    state = DRAWSWORDS;
  }

  if(input->isKeyDown(OIS::KC_SPACE)) {
    state = SLICE;
  }

  if(input->isKeyDown(OIS::KC_PGUP)) {
    //mRigidBody->setLinearVelocity(btVector3(0, 50, 0));
  }

  animate(elapsedTime, state);
}

void OgreCharacterController::animate(Ogre::Real elapsedTime, OGRE_ANIMATION_STATE state)
{
  Ogre::Entity * ent = getEntity();
  Ogre::AnimationState * animTop = 0;
  Ogre::AnimationState * animBase = 0;

  if(animTimer > 0) {
    if(lastTop != 0)
      lastTop->addTime(elapsedTime);
    if(lastBase != 0)
      lastBase->addTime(elapsedTime);
    animTimer -= elapsedTime;
    return;
  }
  
  switch(state)
  {
  case IDLE:
    animTop  = ent->getAnimationState("IdleTop");
    animBase = ent->getAnimationState("IdleBase");
    break;
  case RUN:
    animTop = ent->getAnimationState("RunTop");
    animBase = ent->getAnimationState("RunBase");
    break;
  case DRAWSWORDS:
    drawSwords(animTop, ent);
    animBase = lastBase;
    break;
  case SLICE:
    animTop = lastTop;
    if(swordsOut)
      slice(animTop, ent);
    animBase = lastBase;
    break;
  }

  // Disable last set of animations
  if(animTop != lastTop) {
    if(lastTop != 0)
      lastTop->setEnabled(false);
  }

  if(animBase != lastBase) {
    if(lastBase != 0)
      lastBase->setEnabled(false);
  }

  // Enable next set
  if(animTop) {
    animTop->setEnabled(true);
    animTop->setLoop(true);
    animTop->addTime(elapsedTime);
  }

  if(animBase) {
    animBase->setEnabled(true);
    animBase->setLoop(true);
    animBase->addTime(elapsedTime);
  }

  // Book keeping
  lastTop = animTop;
  lastBase = animBase;
}

void OgreCharacterController::drawSwords(Ogre::AnimationState *& animTop, Ogre::Entity * ent)
{
  animTop = ent->getAnimationState("DrawSwords");
  animTimer = 0.1f; // 0.1f count animation

  // Change sword position
  ent->detachAllObjectsFromBone();
  ent->attachObjectToBone((swordsOut) ? "Sheath.L" : "Handle.L", mSword1);
  ent->attachObjectToBone((swordsOut) ? "Sheath.R" : "Handle.R", mSword2);

  // Hand positioning
  ent->getAnimationState("HandsClosed")->setEnabled(!swordsOut);
  ent->getAnimationState("HandsRelaxed")->setEnabled(swordsOut);

  // Toggle
  swordsOut = !swordsOut;
}

void OgreCharacterController::slice(Ogre::AnimationState *& animTop, Ogre::Entity * ent)
{
  animTop = ent->getAnimationState((sliceDir) ? "SliceVertical" : "SliceHorizontal");
  animTimer = 0.45f; // 0.45f count animation
  sliceDir = !sliceDir;
}
