#include "CompassRangeInterruptor.h"


CompassRangeInterruptor::CompassRangeInterruptor(Compass* compass, Range* range) : AbstractInterruptor(DEF_CHECKTIME)
{
	this->compass = compass;
	this->range = range;
}

bool CompassRangeInterruptor::HasToInterrupt()
{
	bool isInRange = this->range->checkValue(compass->getDirectionInDegrees());
	return !(isInRange);
}

CompassRangeInterruptor::~CompassRangeInterruptor()
{
}
