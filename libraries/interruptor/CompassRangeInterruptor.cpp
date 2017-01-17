#include "CompassRangeInterruptor.h"
#include "ExStream.h"

CompassRangeInterruptor::CompassRangeInterruptor(Compass* compass, Range* range) : AbstractInterruptor(DEF_CHECKTIME)
{
	this->compass = compass;
	this->range = range;
}

bool CompassRangeInterruptor::HasToInterrupt()
{
	ExStream* stream = ExStream::getInstance(0);
	float direction = compass->getDirectionInDegrees();
	bool result = !(this->range->checkValue(direction));

	if (stream) {
		stream->print("direction: "); stream->println(direction);
		stream->print("result: "); stream->println(result);
	}

	return result;
}

CompassRangeInterruptor::~CompassRangeInterruptor()
{
}
