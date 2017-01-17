// NormalInterruptor.h

#ifndef _NORMALINTERRUPTOR_h
#define _NORMALINTERRUPTOR_h

#include "AbstractInterruptor.h"


class NormalInterruptor : public AbstractInterruptor
{
public:
	NormalInterruptor();
	bool HasToInterrupt();
};

#endif

