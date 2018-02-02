#include "Header.h";
#include "GeometryHeader.h";
#include "SpaceObjectHeader.h";


SpaceObject::SpaceObject()
{
	ObjectVector;
}

SpaceObject::SpaceObject(ull mass, GLfloat radius, Vector vector)
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
	int triangleAmount = 8;

	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_TRIANGLE_FAN);

	GLfloat x = (GLfloat)ObjectVector.StartPoint.X;
	GLfloat y = (GLfloat)ObjectVector.StartPoint.Y;
	GLfloat r = (GLfloat)Radius;

	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (r * cos(i *  twicePi / triangleAmount)),
			y + (r * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void SpaceObject::MoveObject() {
	ObjectVector.Move();
}

bool SpaceObject::Interact(SpaceObject *object)
{
	int xDistance = pow(abs((long long)object->ObjectVector.StartPoint.X) - abs((long long)this->ObjectVector.StartPoint.X), 2);
	int yDistance = pow(abs((long long)object->ObjectVector.StartPoint.Y) - abs((long long)this->ObjectVector.StartPoint.Y), 2);
	int distance = sqrt(xDistance + yDistance);
	if (distance >= object->Radius + this->Radius) {
		this->Radius += object->Radius;
		this->Mass = object->Mass;
		SetDensity();
		this->ObjectVector.AddAcceleration(object->ObjectVector.Acceleration);
		return true;
	}
	else 
	{
		ull forceGravity = (this->Mass * object->Mass) / pow(distance, 2);
		ull acceleration = (this->Mass / object->Mass) * forceGravity;

		Point direction;
		if (object->ObjectVector.StartPoint.X > this->ObjectVector.StartPoint.X) 
		{
			direction.X = 1 * acceleration;
		}
		else 
		{
			direction.X = -1 * acceleration;
		}
		if (object->ObjectVector.StartPoint.Y > this->ObjectVector.StartPoint.Y)
		{
			direction.Y = 1 * acceleration;
		}
		else
		{
			direction.Y = -1 * acceleration;
		}
		this->ObjectVector.AddAcceleration(direction);
	}
}