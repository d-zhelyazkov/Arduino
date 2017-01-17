#include "Range.h"


void Range::checkParameters()
{
	if (lowerBound > higherBound) {
		float buff = lowerBound;
		lowerBound = higherBound;
		higherBound = buff;
	}
}

Range::Range(float lowerBound, float higherBound)
{
	this->lowerBound = lowerBound;
	this->higherBound = higherBound;
	checkParameters();
}

void Range::setLowerBound(float lowerBound)
{
	this->lowerBound = lowerBound;
	checkParameters();
}

void Range::setHigherBound(float higherBound)
{
	this->higherBound = higherBound;
	checkParameters();
}

bool Range::isInRange(float value)
{
	return ((lowerBound <= value) && (value <= higherBound));
}

bool Range::isOutOfRange(float value)
{
	return !isInRange(value);
}

bool Range::checkValue(float value)
{
	switch (checkType)
	{
	case CheckType::INNER:
		return isInRange(value);
	case CheckType::OUTER:
		return isOutOfRange(value);
	}
}

Range::~Range()
{
}

const char * getCheckTypeStr(const CheckType chtype)
{
	switch (chtype) {
	case CheckType::INNER:
		return "Inner";
	case CheckType::OUTER:
		return "Outer";
	}
}
