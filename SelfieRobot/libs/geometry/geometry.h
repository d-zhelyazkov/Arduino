#pragma once

#define PI 3.1415926535897932384626433832795
#define PI_DEG 180
#define PI_DEGx2 360

struct Point {
	float x = 0;
	float y = 0;

	Point() {}
	Point(float x, float y)
		: x(x), y(y){}

	bool operator==(const Point& point);
};

struct Line {
	float k = 0;
	float c = 0;

	Line() {}

	float f(float x);
};


Line* lineFrom2Points(Point* point1, Point* point2);

float distanceBetweenTwoPoints(Point* point1, Point* point2);

Line* parallelLineFromLineAndPoint(Line* line, Point* point);

Point* intersectionOf2Lines(Line* line1, Line* line2);

Point* midpointOf2Points(Point* point1, Point* point2);

float angleFrom3PointsInRadians(Point* a, Point* o, Point* b);
float angleFrom3Points(Point* a, Point* o, Point* b);

Point* pointFrom2Points_90(Point* a, Point* o);

float radiansToDegrees(float radians);

float comparePointAgainstLine(Point* point, Line* line);

bool arePointsOnSameLine(Point** points, unsigned int count);
