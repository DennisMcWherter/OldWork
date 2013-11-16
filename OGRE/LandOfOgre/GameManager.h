/**
 * GameManager.h
 * Game manager - this is the glue to everything
 *
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreRoot.h"

class GameManager
{
public:
  GameManager();
  virtual ~GameManager();

  virtual void start();

private:
  Ogre::Root * mRoot;
  Ogre::RenderWindow * mWindow;
};

#endif // GAMEMANAGER_H_
