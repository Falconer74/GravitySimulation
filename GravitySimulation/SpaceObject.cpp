#include "Header.h";
#include "GeometryHeader.h";

class SpaceObject
{
public:
	ull Mass;
	ull Radius;
	ull Density;
	Vector ObjectVector;

	SpaceObject()
	{
		ObjectVector;
	}

	SpaceObject(ull mass, ull radius, Vector vector)
	{
		Mass = mass;
		Radius = radius;
		SetDensity();
		ObjectVector = vector;
	}

	void SetDensity() 
	{
		Density = Mass / M_PI * Radius * Radius;
	}

	void DrawFilledCircle(GLfloat x, GLfloat y) {
		int i;
		int triangleAmount = 30;

		GLfloat twicePi = 2.0f * M_PI;

		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y);
		for (i = 0; i <= triangleAmount; i++) {
			glVertex2f(
				x + ((GLfloat)Radius * cos(i *  twicePi / triangleAmount)),
				y + ((GLfloat)Radius * sin(i * twicePi / triangleAmount))
			);
		}
		glEnd();
	}

	void MoveObject() {
		ObjectVector.Move();
	}

	bool Interact(SpaceObject *object) 
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

			this->ObjectVector.AddAcceleration(acceleration);
		}
	}
};