#include "Header.h";
#include "GeometryHeader.h";
#include <vector>;
#include "SpaceObjectHeader.h";
#include "Display.h";

int Display::height;
int Display::width;
float Display::scale;
float Display::speed;

std::vector<SpaceObject*> *spaceObjects;

void DrawFilledCircle(GLint x, GLint y, GLint radius) {
	int i;
	int triangleAmount = 20;

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
	glutTimerFunc(Display::speed, update, 0);

	int size = spaceObjects->size();

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (i == j) {
				continue;
			}
			else {
				if ((*spaceObjects)[i] == nullptr) {
					break;
				}
				else if ((*spaceObjects)[j] == nullptr) {
					continue;
				}
				if ((*spaceObjects)[i]->Interact((*spaceObjects)[j])) {
					(*spaceObjects)[j] = nullptr;
				}
			}
		}
	}

	int iterator = 0;
	while (iterator < spaceObjects->size())
	{
		if ((*spaceObjects)[iterator] == nullptr) {
			(*spaceObjects).erase((*spaceObjects).begin() + iterator);
			++iterator;
		}
		else {
			++iterator;
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

	Display::height = 1600;
	Display::width = 900;
	Display::scale = 1.0f;
	Display::speed = 1.0f;

	glutInitWindowSize(Display::height, Display::width);
	glutCreateWindow("Gravity simulation");
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutTimerFunc(1, update, 0);

	spaceObjects = new std::vector<SpaceObject*>();

	spaceObjects->push_back(new SpaceObject(5200, 3, *(new Vector(*(new Point(-800, 50)), *(new Point(2, 0))))));
	spaceObjects->push_back(new SpaceObject(5000, 2, *(new Vector(*(new Point(800, -100)), *(new Point(-1, 0))))));
	spaceObjects->push_back(new SpaceObject(6000, 5, *(new Vector(*(new Point(0, 450)), *(new Point(-1, -1))))));
	spaceObjects->push_back(new SpaceObject(4700, 2, *(new Vector(*(new Point(0, -450)), *(new Point(3, 0))))));

	//spaceObjects->push_back(new SpaceObject(9000, 6, *(new Vector(*(new Point(-800, -100)), *(new Point(0.5f, 0))))));
	//spaceObjects->push_back(new SpaceObject(9000, 6, *(new Vector(*(new Point(800, 100)), *(new Point(-0.6f, 0))))));
	//spaceObjects->push_back(new SpaceObject(9000, 6, *(new Vector(*(new Point(0, 450)), *(new Point(-0.1, -0.5f))))));

	glutMainLoop();
	
	return 0;
}