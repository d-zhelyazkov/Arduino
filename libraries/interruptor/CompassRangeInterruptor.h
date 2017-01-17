#pragma once

#include "compass.h"
#include "Range.h"
#include "AbstractInterruptor.h"

#define DEF_CHECKTIME 0

class CompassRangeInterruptor : public AbstractInterruptor {
private:
	Compass* compass;
	Range* range;

public:
	CompassRangeInterruptor(Compass* compass, Range* range);
	bool HasToInterrupt();

	~CompassRangeInterruptor();

};

