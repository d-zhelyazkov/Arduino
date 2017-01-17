#include "Range.h"


void Range::checkParameters()
{
	if (lowerBound > higherBound) {
		int buff = lowerBound;
		lowerBound = higherBound;
		higherBound = buff;
		switch (this->defaultCheckType) {
		case CheckType::INNER:
			this->defaultCheckType = CheckType::OUTER;
			break;
		case CheckType::OUTER:
			this->defaultCheckType = CheckType::INNER;
			break;
		}
	}
}

Range::Range(int lowerBound, int higherBound)
{
	this->lowerBound = lowerBound;
	this->higherBound = higherBound;
	checkParameters();
}

void Range::setLowerBound(int lowerBound)
{
	this->lowerBound = lowerBound;
	checkParameters();
}

void Range::setHigherBound(int higherBound)
{
	this->higherBound = higherBound;
	checkParameters();
}

bool Range::isInRange(int value)
{
	return ((lowerBound <= value) && (value <= higherBound));
}

bool Range::isOutOfRange(int value)
{
	return !isInRange(value);
}

bool Range::checkValue(int value)
{
	switch (defaultCheckType)
	{
	case CheckType::INNER:
		return isInRange(value);
	case CheckType::OUTER:
		return isOutOfRange(value);
	}
}

void Range::setDefaultCheckType(CheckType defaultCheckType)
{
	this->defaultCheckType = defaultCheckType;
}

Range::~Range()
{
}
