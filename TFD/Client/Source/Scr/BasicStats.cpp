#include "include/BasicStats.h"

BasicStats::BasicStats()
{

	m_health =0;
}

void BasicStats::setHealth(int health)
{
	m_health = health;
}
bool BasicStats::isDeath()
{
	return (m_health <= 0) ? true : false;
}
BasicStats::~BasicStats()
{

}
