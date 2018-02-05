#include "Header.h";
#include "GeometryHeader.h";

Point::Point()
{
	X = 0;
	Y = 0;
}
Point::Point(double x, double y)
{
	X = x;
	Y = y;
}

void Point::operator += (Point point) {
	this->X += point.X;
	this->Y += point.Y;
}

Point Point::operator *= (double impulse) {
	this->X *= impulse;
	this->Y *= impulse;
	return *this;
}

Vector::Vector()
{
}

Vector::Vector(Point startPoint, Point acceleration)
{
	StartPoint = startPoint;
	Acceleration = acceleration;
}

void Vector::Move()
{
	StartPoint += Acceleration;
}

void Vector::AddAcceleration(Point acceleration)
{
	Acceleration += acceleration;
}