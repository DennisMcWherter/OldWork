/*
@authors:		Soulmen (Jordan Daubinet),

@dateCreated:	7-1-2011
@lastUpdated:	7-1-2011

@filename:		BassicStats.h
*/
#ifndef __BASICSTATS_H
#define __BASICSTATS_H

#include <irrlicht.h>



using namespace irr;

class BasicStats{
public:
	BasicStats();
	~BasicStats();

	//set
	void setHealth(int health);
	

	// get
	int getHealth(){return m_health;};
	
	bool isDeath();

	//show
	
	
	//members
protected:
	int m_health;
	
};
#endif