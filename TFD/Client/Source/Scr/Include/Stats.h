/*
@authors:		Soulmen (Jordan Daubinet),

@dateCreated:	7-1-2011
@lastUpdated:	7-1-2011

@filename:		Stats.h
*/

#ifndef __STATS_H
#define __STATS_H

#include <string>
#include <vector>
#include <irrlicht.h>


using namespace irr;
using namespace core;

class Stats
{
public:
	Stats();
	~Stats();

	// From/to file (network)
	void loadFromFile(std::string filename);
	void saveToFile(std::string filename);

	std::string toString();

	// Sets
	void setHealth(int health) { m_health = health; }
	
	// Gets
	int health() { return m_health; }
	std::string name() { return m_name; }

	bool isDead() { return m_health <= 0; }

protected:
	std::string m_name;
	int m_level, m_experience;
	int m_health;
	int m_shield, m_weapon, m_gloves, m_boots, m_ring1, m_ring2, m_necklace;
	std::vector<int> m_otherItems;

	vector3df m_position;
	vector3df m_rotation;
};

#endif