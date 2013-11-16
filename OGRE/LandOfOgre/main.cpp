/**
 * main.cpp
 * Entry point to the Land Of Ogre >:)
 *
 * Dennis J. McWherter, Jr.
 * 12 August 2011
 */

#include "GameManager.h"

#include "OGRE/OgreException.h"

#pragma comment(lib, "OgreMain_d.lib")
//#pragma comment(lib, "OgrePaging_d.lib")
//#pragma comment(lib, "OgreRTShaderSystem_d.lib")
//#pragma comment(lib, "OgreTerrain_d.lib")
#pragma comment(lib, "OIS_d.lib")

int main()
{
  try
  {
    GameManager game;
    game.start();
  } catch(const Ogre::Exception& e) {
    std::cout<< e.getFullDescription();
  }
  std::cin.get();
  return 0;
}
