// 
// 
// 

#include "AbstractInterruptor.h"

AbstractInterruptor::AbstractInterruptor(unsigned int checkTime)
{
	(*this).checkTime = checkTime;
}

unsigned int AbstractInterruptor::GetCheckTIme()
{
	return checkTime;
}
