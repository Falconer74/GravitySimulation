#pragma once
#include "Header.h"

struct Point {
public:
	ull X;
	ull Y;
	Point();
	Point(ull x, ull y);
	void operator += (Point point);
	void operator *= (Point point);
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