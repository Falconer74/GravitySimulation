#pragma once
#include "GeometryHeader.h";
#include "Header.h";

class SpaceObject
{
public:
	int Mass;
	int Radius;
	int Density;
	Vector ObjectVector;

	SpaceObject();

	SpaceObject(int mass, int radius, Vector vector);

	void SetDensity();

	void DrawFilledCircle();

	void MoveObject();

	bool Interact(SpaceObject *object);
};