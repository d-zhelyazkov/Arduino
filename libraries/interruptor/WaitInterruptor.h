// WaitInterruptor.h

#ifndef _WAITINTERRUPTOR_h
#define _WAITINTERRUPTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "AbstractInterruptor.h"

class WaitInterruptor : public AbstractInterruptor
{
private:
	bool interrupt = false;
public:
	WaitInterruptor(unsigned int waitTime);
	bool HasToInterrupt();
};

#endif

