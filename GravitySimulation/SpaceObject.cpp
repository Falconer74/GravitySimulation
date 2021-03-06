#include "Header.h";
#include "GeometryHeader.h";
#include "SpaceObjectHeader.h";


SpaceObject::SpaceObject()
{
	ObjectVector;
}

SpaceObject::SpaceObject(int mass, int radius, Vector vector)
{
	Mass = mass;
	Radius = radius;
	SetDensity();
	ObjectVector = vector;
}

void SpaceObject::SetDensity()
{
	Density = Mass / M_PI * Radius * Radius;
}

void SpaceObject::DrawFilledCircle() {
	int i;
	int triangleAmount = 50;

	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_TRIANGLE_FAN);

	GLint x = ObjectVector.StartPoint.X;
	GLint y = ObjectVector.StartPoint.Y;

	glVertex2i(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2i(
			x + (Radius * cos(i *  twicePi / triangleAmount)),
			y + (Radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void SpaceObject::MoveObject() {
	ObjectVector.Move();
}

void SpaceObject::unite(SpaceObject *object) {
	float ratio = (float((float)object->Mass / (float)this->Mass));
	this->ObjectVector.AddAcceleration((object->ObjectVector.Acceleration *= ratio));
	this->Radius += object->Radius * ratio;
	this->Mass += object->Mass;
	SetDensity();
	delete object;
}

bool SpaceObject::Interact(SpaceObject *object)
{
	int xDistance = pow(object->ObjectVector.StartPoint.X - this->ObjectVector.StartPoint.X, 2);
	int yDistance = pow(object->ObjectVector.StartPoint.Y - this->ObjectVector.StartPoint.Y, 2);
	int distance = sqrt(xDistance + yDistance);
	if (distance <= object->Radius + this->Radius) {
		return true;
	}
	else 
	{
		float forceGravity = (this->Mass * object->Mass) / pow(distance, 2) / 300000;
		float acceleration = (float(object->Mass / this->Mass)) * forceGravity;

		Point direction;
		if (object->ObjectVector.StartPoint.X > this->ObjectVector.StartPoint.X) 
		{
			direction.X = 1 * acceleration;
		}
		else if(object->ObjectVector.StartPoint.X < this->ObjectVector.StartPoint.X)
		{
			direction.X = -1 * acceleration;
		}
		else 
		{
			direction.X = 0;
		}
		if (object->ObjectVector.StartPoint.Y > this->ObjectVector.StartPoint.Y)
		{
			direction.Y = 1 * acceleration;
		}
		else if(object->ObjectVector.StartPoint.Y < this->ObjectVector.StartPoint.Y)
		{
			direction.Y = -1 * acceleration;
		}
		else 
		{
			direction.Y = 0;
		}
		this->ObjectVector.AddAcceleration(direction);
		return false;
	}
}