#pragma once

enum CheckType {
	INNER,
	OUTER
};

const char* getCheckTypeStr(const CheckType chtype);

class Range
{
private:
	float lowerBound = 0.0;
	float higherBound = 0.0;
	CheckType checkType = INNER;

	void checkParameters();
public:
	Range(float lowerBound, float higherBound);

	void setLowerBound(float lowerBound);
	float getLowerBound() { return lowerBound; }
	void setHigherBound(float higherBound);
	float getHigherBound() { return higherBound; }
	void setCheckType(CheckType checkType) { this->checkType = checkType; }
	CheckType getCheckType() { return checkType; }

	bool isInRange(float value);
	bool isOutOfRange(float value);
	bool checkValue(float value);

	~Range();
};

