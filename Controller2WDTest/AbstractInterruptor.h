// AbstractInterruptor.h

#ifndef _ABSTRACTINTERRUPTOR_h
#define _ABSTRACTINTERRUPTOR_h


class AbstractInterruptor
{
private:
	unsigned int checkTime;
public:
	AbstractInterruptor(unsigned int checkTime);
	unsigned int GetCheckTIme();

	virtual bool HasToInterrupt() = 0;
};

#endif

