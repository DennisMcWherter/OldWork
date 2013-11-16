/**
 * GameManager.cpp
 * Manages the game (glue to everything)
 * 
 * Dennis J. McWherter, Jr.
 *
 * 12 August 2011
 */

#include "GameManager.h"
#include "Level1.h"

GameManager::GameManager()
{
  mRoot = new Ogre::Root;

  mRoot->loadPlugin("RenderSystem_Direct3D9_d"); // Load debug DirectX
  mRoot->loadPlugin("Plugin_CgProgramManager_d");

  mRoot->setRenderSystem(mRoot->getAvailableRenderers().front());
  mRoot->initialise(false);

  mWindow = mRoot->createRenderWindow("Land of Ogre (alpha)", 800, 600, false, 0);
}

GameManager::~GameManager()
{
  //delete mWindow; // Need to make sure we're freeing this properly
  mRoot->shutdown();
  delete mRoot;
}

void GameManager::start()
{
  // Start the game loop - temporary
  // static, 1 level
  Level1 level(mRoot, mWindow);
  mRoot->addFrameListener(&level);
  level.createScene();
  mRoot->startRendering();
}
