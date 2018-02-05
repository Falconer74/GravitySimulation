#pragma once
#include "Header.h"

struct Point {
public:
	double X;
	double Y;
	Point();
	Point(double x, double y);
	void operator += (Point point);
	Point operator *= (double impulse);
};
struct Vector {
public:
	Point StartPoint;
	Point Acceleration;
	Vector();
	Vector(Point startPoint, Point finishPoint);
	void Move();
	void AddAcceleration(Point acceleration);
};