/*
@authors:		Soulmen (Jordan Daubinet),

@dateCreated:	7-1-2011
@lastUpdated:	7-1-2011

@filename:		AI.h
*/
#ifndef __AI_H
#define __AI_H

#include <irrlicht.h>

#include "BasicStats.h"
#include "Object.h"

using namespace irr;
using namespace core;

class AI : public  BasicStats, public Object
{
	
public:

	AI();
	~AI();

	//set
	void setState(long state);

	void walk();

	
	//get
	long getState() {return m_state;};

	
	bool isInRange(Object obj);
	
	vector3df getPosition();
	
	bool isClicked();



	//methodes
protected:

	enum STATES {
		NONE =0,  //If the ai dont have a state
		SEARCH,  // seaching for something
		FOUND, // found the task
		FOLLOWPATH // following hes path

	};

	//Members
protected:
	long m_state;
	vector3df m_pos;
	SEvent::SMouseInput mouse;

};
#endif