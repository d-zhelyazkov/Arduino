#include "geometry.h"
#include <math.h>



void computeLineCFromPoint(Line* line, Point* point);

Line* lineFrom2Points(Point* point1, Point* point2) {
	Line* line = new Line();
	line->k = (point2->y - point1->y) / (point2->x - point1->x);
	computeLineCFromPoint(line, point1);
	return line;
}

float distanceBetweenTwoPoints(Point* point1, Point* point2) {
	return sqrtf(powf((point1->x - point2->x), 2) + powf((point1->y - point2->y), 2));
}

Line* parallelLineFromLineAndPoint(Line* line, Point* point) {
	Line* resultLine = new Line();
	resultLine->k = line->k;
	computeLineCFromPoint(resultLine, point);
	return resultLine;
}

Point* intersectionOf2Lines(Line* line1, Line* line2) {
	if (line1->k == line2->k)
		return 0;

	Point* point = new Point();
	if (isinf(line1->k)) {
		point->x = line1->c;
		point->y = line2->f(point->x);
	}
	else if (isinf(line2->k)) {
		point->x = line2->c;
		point->y = line1->f(point->x);
	}
	else {
		point->x = (line2->c - line1->c) / (line1->k - line2->k);
		point->y = point->x * line1->k + line1->c;
	}
	return point;
}

Point* midpointOf2Points(Point* point1, Point* point2) {
	Point* point = new Point();
	point->x = (point1->x + point2->x) / 2;
	point->y = (point1->y + point2->y) / 2;
	return point;
}

float angleFrom3PointsInRadians(Point* a, Point* o, Point* b) {
	Point aCopy(*a);
	Point bCopy(*b);
	aCopy.x -= o->x;
	aCopy.y -= o->y;
	bCopy.x -= o->x;
	bCopy.y -= o->y;
	return atan2f(aCopy.y, aCopy.x) - atan2f(bCopy.y, bCopy.x);
}

float angleFrom3Points(Point* a, Point* o, Point* b) {
	float angleInRadians = angleFrom3PointsInRadians(a, o, b);
	return radiansToDegrees(angleInRadians);
}

Point* pointFrom2Points_90(Point* a, Point* o) {
	Point* point = new Point();
	point->x = o->x - a->y + o->y;
	point->y = a->x - o->x + o->y;
	return point;
}

//[0;2PI]
float radiansToDegrees(float radians) {
	float degrees = radians * PI_DEG / PI;
	degrees = fmod(degrees, PI_DEGx2);
	if (degrees < 0)
		degrees += (PI_DEGx2);

	return degrees;
}

float comparePointAgainstLine(Point* point, Line* line) {
	Line* parallelLine = parallelLineFromLineAndPoint(line, point);
	float cDiff = parallelLine->c - line->c;
	delete(parallelLine);
	return cDiff;
}

bool arePointsOnSameLine(Point** points, unsigned int count) {
	if (count < 3)
		return false;

	Line* line = lineFrom2Points(*points, *(points + 1));
	bool result = true;
	for (int i = 2; i < count; i++) {
		if (comparePointAgainstLine(*(points + i), line)) {
			result = false;
			break;
		}

	}
	delete(line);
	return result;
}

void computeLineCFromPoint(Line* line, Point* point) {
	if (isinf(line->k)) {
		line->c = point->x;
	}
	else {
		line->c = point->y - point->x * line->k;
	}
}

bool Point::operator==(const Point & point)
{
	return (x == point.x && y == point.y);
}

float Line::f(float x)
{
	return (isinf(k)) ? 0 : (x * k + c);
}
