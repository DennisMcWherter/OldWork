/**
 * GameManager.cpp
 * Game Manager
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreException.h"
#include "OGRE/OgreRenderWindow.h"
#include "OGRE/OgreRoot.h"

#include "GameManager.h"
#include "LevelManager.h"

GameManager::GameManager()
{
  try {
    mRoot = new Ogre::Root;
    loadPlugins();
    mRoot->setRenderSystem(mRoot->getAvailableRenderers().front());
    mRoot->initialise(false);

    mWindow = mRoot->createRenderWindow("Firesale: Everything Must Go (alpha version)", 800, 600, false);

    mWindow->addViewport(0);

    mLevels = new LevelManager(mRoot, mWindow);

  } catch(const Ogre::Exception& e) {
    throw e;
  }
}

GameManager::~GameManager()
{
  delete mLevels;
  mWindow->removeAllListeners();
  mWindow->removeAllViewports();
  delete mRoot;
}

void GameManager::run()
{
  // Run through our level manager
  mLevels->run();
}

void GameManager::loadPlugins()
{
  try {
    mRoot->loadPlugin("RenderSystem_Direct3D9_d"); // DirectX Debug Renderer
    mRoot->loadPlugin("Plugin_CgProgramManager_d"); // Cg script manager
  } catch(const Ogre::Exception& e) {
    throw e;
  }
}
