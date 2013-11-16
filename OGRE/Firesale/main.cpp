/**
 * main.cpp
 * Main entry point for "Firesale: Everything Must Go"
 *
 * The plan is to get this done in a week (well at least an
 * alpha) unless we have interested people in continued development
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#include "OGRE/OgreException.h"

#include "GameManager.h"

#pragma comment(lib, "BulletSoftBody.lib")
#pragma comment(lib, "BulletDynamics.lib")
#pragma comment(lib, "BulletCollision.lib")
#pragma comment(lib, "LinearMath.lib")
#pragma comment(lib, "BtOgre.lib")

#ifdef _WIN32
#ifdef _DEBUG
#pragma comment(lib, "OgreMain_d.lib")
#pragma comment(lib, "OIS_d.lib")
#else
#pragma comment(lib, "OgreMain.lib")
#pragma comment(lib, "OIS.lib")
#endif
#endif

int main()
{
  try {
    GameManager game;
    game.run();
  } catch(const Ogre::Exception& e) {
    std::cout<< "Exception caught: "<< e.getDescription() << " at "<< e.getFile() << ":"<< e.getLine()
      << std::endl;
  }
  return 0;
}
