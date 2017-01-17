// 
// 
// 

#include "WaitInterruptor.h"

WaitInterruptor::WaitInterruptor(unsigned int waitTime) : AbstractInterruptor(waitTime) {}

bool WaitInterruptor::HasToInterrupt()
{
	return true;
}

