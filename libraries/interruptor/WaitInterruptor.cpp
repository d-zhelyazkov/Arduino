// 
// 
// 

#include "WaitInterruptor.h"

WaitInterruptor::WaitInterruptor(unsigned int waitTime) : AbstractInterruptor(waitTime) {}

bool WaitInterruptor::HasToInterrupt()
{
	bool result = interrupt;
	interrupt = !interrupt;
	return result;
}

