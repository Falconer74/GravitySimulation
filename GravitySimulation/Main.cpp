#include "Header.h";
#include "GeometryHeader.h";
#include <vector>;
#include "SpaceObjectHeader.h";

GLint scale = 1.0f;
std::vector<SpaceObject*> *spaceObjects;

void DrawFilledCircle(GLint x, GLint y, GLint radius) {
	int i;
	int triangleAmount = 50;

	GLfloat twicePi = 2.0f * M_PI;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2i(
			x + (radius * cos(i *  twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void DrawRectangle() {
	glBegin(GL_QUADS);
	glVertex2i(-5, 5);
	glVertex2i(-5, -5);
	glVertex2i(5, -5);
	glVertex2i(5, 5);
	glEnd();
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-(width / 2), width / 2, -(height / 2), height / 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw() {
	int size = spaceObjects->size();

	glClear(GL_COLOR_BUFFER_BIT);
	for (int i = 0; i < size; ++i) {
		(*spaceObjects)[i]->DrawFilledCircle();
	}
	glutSwapBuffers();
}

void update(int) {
	glutTimerFunc(1, update, 0);

	int size = spaceObjects->size();

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i == j) {
				continue;
			}
			else {
				if ((*spaceObjects)[i] == nullptr || (*spaceObjects)[j] == nullptr) {
					continue;
				}
				if ((*spaceObjects)[i]->Interact((*spaceObjects)[j])) {
					(*spaceObjects)[j] = nullptr;
				}
			}
		}
	}

	for (int i = 0; i < size; i++)
	{
		if ((*spaceObjects)[i] == nullptr) {
			(*spaceObjects).erase((*spaceObjects).begin() + i);
		}
	}

	for (int i = 0; i < (*spaceObjects).size(); ++i) {
		(*spaceObjects)[i]->MoveObject();
	}

	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("Gravity simulation");
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutTimerFunc(1, update, 0);

	spaceObjects = new std::vector<SpaceObject*>();

	spaceObjects->push_back(new SpaceObject(10000, 4, *(new Vector(*(new Point(-250, 50)), *(new Point(2, 0))))));
	spaceObjects->push_back(new SpaceObject(5000, 2, *(new Vector(*(new Point(250, -100)), *(new Point(-1, 0))))));

	glutMainLoop();
	
	return 0;
}