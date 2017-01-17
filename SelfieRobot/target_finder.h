#pragma once

#include "libs\geometry\geometry.h"

class TargetFinder {
public:
	float distanceToTarget = 0;
	float targetAngle = 0;

	//returns:
	//0 - successfull
	//1 - some points are equal or all points are on the same line
	//2 - unidentified error
	//result angle - [0:360]
	short computeTargetPoisition(Point* tailPoint, Point* sidePoint1, Point* sidePoint2);
};

short TargetFinder::computeTargetPoisition(Point* tailPoint, Point* sidePoint1, Point* sidePoint2) {
	distanceToTarget = 0;
	targetAngle = 0;
	if ((*tailPoint == *sidePoint1) || (*tailPoint == *sidePoint2) || (*sidePoint1 == *sidePoint2))
		return 1;

	Point* points[] = { tailPoint, sidePoint1, sidePoint2 };
	if (arePointsOnSameLine(points, 3))
		return 1;

	Point centerPoint(0, 0);
	Point* midPoint = midpointOf2Points(sidePoint1, sidePoint2);

	//finds the tail point's prime and its projection line - the main one
	Point* tailPointPrime = pointFrom2Points_90(sidePoint1, midPoint);
	Line* intersectionLine = lineFrom2Points(sidePoint1, sidePoint2);
	float headPointPosition = comparePointAgainstLine(tailPoint, intersectionLine);
	float headPointPrimePosition = comparePointAgainstLine(tailPointPrime, intersectionLine);
	if ((headPointPosition * headPointPrimePosition) < 0) {
		delete(tailPointPrime);
		tailPointPrime = pointFrom2Points_90(sidePoint2, midPoint);
	}
	Line* mainProjectionLine = lineFrom2Points(tailPoint, tailPointPrime);

	delete(intersectionLine);

	//finds center line's prime
	Line* centerLine = lineFrom2Points(&centerPoint, midPoint);
	Line* sideLine = lineFrom2Points(tailPoint, sidePoint1);
	Point* sideIntersectionPoint = intersectionOf2Lines(centerLine, sideLine);
	Line* sideLinePrime = 0;
	if (sideIntersectionPoint != 0) {
		sideLinePrime = lineFrom2Points(tailPointPrime, sidePoint1);
	}
	else {
		delete(sideLine);
		sideLine = lineFrom2Points(tailPoint, sidePoint2);
		sideIntersectionPoint = intersectionOf2Lines(centerLine, sideLine);
		if (sideIntersectionPoint == 0) {
			//T, S1 and S2 form a triangle 
			//=> TS1 and TS2 cannot be both parallel to any line
			//this case will never happen
			return 2;
		}
		sideLinePrime = lineFrom2Points(tailPointPrime, sidePoint2);
	}
	Line* sideIntersectionProjectionLine = parallelLineFromLineAndPoint(mainProjectionLine, sideIntersectionPoint);
	Point* sideIntersectionPointPrime = intersectionOf2Lines(sideLinePrime, sideIntersectionProjectionLine);
	if (sideIntersectionPointPrime == 0) {
		//ToDo
		return 2;
	}
	Line* centerLinePrime = lineFrom2Points(midPoint, sideIntersectionPointPrime);

	delete(centerLine);
	delete(sideLine);
	delete(sideIntersectionPoint);
	delete(sideLinePrime);
	delete(sideIntersectionProjectionLine);
	delete(sideIntersectionPointPrime);

	//computes angle and distance
	Line* centerLineProjection = parallelLineFromLineAndPoint(mainProjectionLine, &centerPoint);
	Point* centerPointPrime = intersectionOf2Lines(centerLineProjection, centerLinePrime);
	if (centerPointPrime == 0) {
		//ToDo
		return 2;
	}
	distanceToTarget = distanceBetweenTwoPoints(centerPointPrime, midPoint) / distanceBetweenTwoPoints(midPoint, tailPointPrime);
	targetAngle = angleFrom3Points(tailPointPrime, midPoint, centerPointPrime);

	delete(midPoint);
	delete(tailPointPrime);
	delete(mainProjectionLine);
	delete(centerLinePrime);
	delete(centerLineProjection);
	delete(centerPointPrime);

	return 0;
}
