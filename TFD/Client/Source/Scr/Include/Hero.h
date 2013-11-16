#ifndef __HERO_H
#define __HERO_H

#include "Object.h"
#include "Stats.h"

class Hero : public Object
{
public:
	Hero();
	~Hero();

	// Draw stats on screen
	void drawStats(gui::IGUIFont* font);

	// Load hero stats from file
	void loadStats(std::string filename);
	void saveStats(std::string filename);

	// Actions
	void turnLeft();
	void turnRight();
	void walk();
	void stop();

	// Sets

	// Gets


private:
	EMD2_ANIMATION_TYPE currentAnim;

	Stats _heroStats;

};

#endif // __HERO_H