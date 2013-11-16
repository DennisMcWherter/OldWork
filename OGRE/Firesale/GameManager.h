/**
 * GameManager.h
 * Game Manager
 *
 * Developer: Dennis J. McWherter, Jr.
 * Artist: Peter J. McWherter
 *
 * 14 August 2011
 */

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

class Ogre::RenderWindow;
class Ogre::Root;
class LevelManager;

class GameManager
{
public:
  GameManager();
  virtual ~GameManager();

  virtual void run();

protected:
  virtual void loadPlugins();

private:
  Ogre::Root * mRoot;
  Ogre::RenderWindow * mWindow;
  LevelManager * mLevels;
};

#endif // GAMEMANAGER_H_
