#include "include/AIBasic.h"

AI::AI()
{

}

void AI::setState(long state)
{

	m_state = state;
}

bool AI::isInRange(Object obj){

	
	
	if(position().X+30 > obj.position().X && position().X-30 < obj.position().X && position().Y+30 > obj.position().Y && position().Y-30 < obj.position().Y)
	{
		
	return true;
	}
	return false;
	

}
bool AI::isClicked()
{

	return false;
}






void AI::walk()
{
	

}

 AI::~AI()
{

}