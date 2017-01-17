#include "compass.h"

float Compass::getDirectionInDegrees()
{
	float radians = this->getDirectionInRadians();
	float degrees = radians * PI_DEG / PI;
	degrees = fmod(degrees, PI_DEGx2);
	if (degrees < 0)
		degrees += (PI_DEGx2);
	return degrees;
}
