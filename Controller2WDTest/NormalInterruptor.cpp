// 
// 
// 

#include "NormalInterruptor.h"

NormalInterruptor::NormalInterruptor()
	:AbstractInterruptor(500)
{
}

bool NormalInterruptor::HasToInterrupt()
{
	return false;
}
