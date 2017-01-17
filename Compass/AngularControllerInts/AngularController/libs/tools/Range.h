#pragma once

enum CheckType {
	INNER,
	OUTER
};

class Range
{
private:
	int lowerBound = 0.0;
	int higherBound = 0.0;
	CheckType defaultCheckType = INNER;

	void checkParameters();
public:
	Range(int lowerBound, int higherBound);
	void setLowerBound(int lowerBound);
	void setHigherBound(int higherBound);
	bool isInRange(int value);
	bool isOutOfRange(int value);
	bool checkValue(int value);

	void setDefaultCheckType(CheckType defaultCheckType);
	~Range();
};

