#pragma once

#include "libs\compass\compass.h"
#include "libs\tools\Range.h"
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

