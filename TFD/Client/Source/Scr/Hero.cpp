#include "include/Hero.h"

Hero::Hero()
{
}

Hero::~Hero()
{
}

// Load hero stats from file
void Hero::loadStats(std::string filename)
{
	_heroStats.loadFromFile(filename);
}
void Hero::saveStats(std::string filename)
{
	_heroStats.saveToFile(filename);
}

void Hero::drawStats(gui::IGUIFont* font)
{

	font->draw(_heroStats.toString().c_str(),
		       core::rect<s32>(10,10,300,50),
			   video::SColor(255,0,0,0));
	
}

void Hero::turnLeft()
{
	_node->setRotation(_node->getRotation() - vector3df(0.0f, 0.05f, 0.0f));
	/*
	if(currentAnim != scene::EMAT_STAND) {
		currentAnim = scene::EMAT_STAND;
		_node->setMD2Animation(scene::EMAT_STAND);
	}
	*/
}

void Hero::turnRight()
{
	_node->setRotation(_node->getRotation() + vector3df(0.0f, 0.05f, 0.0f));
	/*
	if(currentAnim != scene::EMAT_STAND) {
		currentAnim = scene::EMAT_STAND;
		_node->setMD2Animation(scene::EMAT_STAND);
	}
	*/
} 

void Hero::walk()
{ 
	matrix4 transf = _node->getAbsoluteTransformation();
	vector3df offset = vector3df(0.05f, 0.0f, 0.0f);
	transf.rotateVect(offset);

	_node->setPosition(_node->getPosition() + offset);
	if(_heroStats.isDead() && currentAnim != scene::EMAT_DEATH_FALLBACK)
	{
		currentAnim = scene::EMAT_DEATH_FALLBACK;
		_node->setMD2Animation(scene::EMAT_RUN);
	}
	
	if(currentAnim != scene::EMAT_RUN && !_heroStats.isDead()) {
		currentAnim = scene::EMAT_RUN;
		_node->setMD2Animation(scene::EMAT_RUN);
	}
	
}

void Hero::stop()
{
	if(currentAnim != scene::EMAT_STAND) {
		currentAnim = scene::EMAT_STAND;
		_node->setMD2Animation(scene::EMAT_STAND);
	}
}