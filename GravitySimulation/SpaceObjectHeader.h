#pragma once
#include "GeometryHeader.h";
#include "Header.h";

class SpaceObject
{
public:
	ull Mass;
	ull Radius;
	ull Density;
	Vector ObjectVector;

	SpaceObject();

	SpaceObject(ull mass, ull radius, Vector vector);

	void SetDensity();

	void DrawFilledCircle();

	void MoveObject();

	bool Interact(SpaceObject *object);
};