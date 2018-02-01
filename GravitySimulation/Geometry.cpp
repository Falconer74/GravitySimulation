#include "Header.h";

struct Point {
public:
	ull X;
	ull Y;
	Point()
	{
		X = 0;
		Y = 0;
	}
	Point(ull x, ull y)
	{
		X = x;
		Y = y;
	}

	void operator += (Point point) {
		this->X += point.X;
		this->Y += point.Y;
	}

	void operator *= (Point point) {
		this->X *= point.X;
		this->Y *= point.Y;
	}
};

struct Vector {
public:
	Point StartPoint;
	Point Acceleration;

	Vector()
	{
	}

	Vector(Point startPoint, Point acceleration)
	{
		StartPoint = startPoint;
		Acceleration = acceleration;
	}

	void Move()
	{
		StartPoint = Acceleration;
	}

	void AddAcceleration(Point acceleration) 
	{
		Acceleration += acceleration;
	}
};