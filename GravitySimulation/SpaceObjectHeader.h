#pragma once
#include "GeometryHeader.h";
#include "Header.h";

class SpaceObject
{
public:
	ull Mass;
	GLfloat Radius;
	ull Density;
	Vector ObjectVector;

	SpaceObject();

	SpaceObject(ull mass, GLfloat radius, Vector vector);

	void SetDensity();

	void DrawFilledCircle();

	void MoveObject();

	bool Interact(SpaceObject *object);
};