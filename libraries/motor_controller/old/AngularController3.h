#pragma once

#include "Abstract2WDController.h"
#include "compass.h"

#define STATISTIC_SIZE 10

class AngularController3 : public Abstract2WDController
{
	float statistics[STATISTIC_SIZE];

public:
	AngularController3(Compass* compass);
	~AngularController3();

	float turn(float angle);
};

