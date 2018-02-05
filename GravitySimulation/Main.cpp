#include "Header.h";
#include "GeometryHeader.h";
#include <vector>;
#include "SpaceObjectHeader.h";
#include "Display.h";
#include <ctime>

int Display::height;
int Display::width;
float Display::scale;
int Display::frameRefresh;
bool Display::isPause;

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
	if (!Display::isPause) {
		glutTimerFunc(Display::frameRefresh, update, 0);
	}

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
					if ((*spaceObjects)[i]->Mass > (*spaceObjects)[j]->Mass) {
						(*spaceObjects)[i]->unite((*spaceObjects)[j]);
						(*spaceObjects)[j] = nullptr;
					}
					else {
						(*spaceObjects)[j]->unite((*spaceObjects)[i]);
						(*spaceObjects)[i] = nullptr;
					}
				}
			}
		}
	}

	int iterator = 0;
	while (iterator < spaceObjects->size())
	{
		if ((*spaceObjects)[iterator] == nullptr) {
			(*spaceObjects).erase((*spaceObjects).begin() + iterator);
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
	srand(time(0));
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	Display::height = 1600;
	Display::width = 900;
	Display::scale = 1.0f;
	Display::frameRefresh = 24;
	Display::isPause = false;

	glutInitWindowSize(Display::height, Display::width);
	glutCreateWindow("Gravity simulation");
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutTimerFunc(1, update, 0);

	spaceObjects = new std::vector<SpaceObject*>();

	//spaceObjects->push_back(new SpaceObject(7000, 3, *(new Vector(*(new Point(-800, 50)), *(new Point(2, 0))))));
	//spaceObjects->push_back(new SpaceObject(5000, 2, *(new Vector(*(new Point(800, -100)), *(new Point(-1, 0))))));
	//spaceObjects->push_back(new SpaceObject(6000, 5, *(new Vector(*(new Point(0, 450)), *(new Point(-1, -1))))));
	//spaceObjects->push_back(new SpaceObject(4700, 2, *(new Vector(*(new Point(0, -450)), *(new Point(3, 0))))));
	//spaceObjects->push_back(new SpaceObject(14000, 6, *(new Vector(*(new Point(-800, -100)), *(new Point(0.5f, 0))))));

	//spaceObjects->push_back(new SpaceObject(12000, 12, *(new Vector(*(new Point(500, 100)), *(new Point(-0.1f, 0))))));
	//spaceObjects->push_back(new SpaceObject(3000, 3, *(new Vector(*(new Point(-800, -100)), *(new Point(0.8f, 0.3f))))));

	//spaceObjects->push_back(new SpaceObject(14000, 6, *(new Vector(*(new Point(-800, -100)), *(new Point(0.5f, 0))))));
	//spaceObjects->push_back(new SpaceObject(14000, 6, *(new Vector(*(new Point(800, 100)), *(new Point(-0.6f, 0))))));
	//spaceObjects->push_back(new SpaceObject(14000, 6, *(new Vector(*(new Point(0, 450)), *(new Point(-0.1, -0.5f))))));

	//spaceObjects->push_back(new SpaceObject(20000, 15, *(new Vector(*(new Point(0, 0)), *(new Point(0.0f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-400, -200)), *(new Point(0.0f, 0.9f))))));

	//spaceObjects->push_back(new SpaceObject(20000, 15, *(new Vector(*(new Point(0, 0)), *(new Point(0.0f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, 800)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, 600)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, 400)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, 200)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, 0)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, -200)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, -400)), *(new Point(0.9f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 3, *(new Vector(*(new Point(-800, -600)), *(new Point(0.9f, 0.0f))))));

	//spaceObjects->push_back(new SpaceObject(20000, 15, *(new Vector(*(new Point(300, -200)), *(new Point(-0.1f, 0.05f))))));
	//spaceObjects->push_back(new SpaceObject(16000, 12, *(new Vector(*(new Point(-100, 350)), *(new Point(-0.1f, 0.05f))))));
	//spaceObjects->push_back(new SpaceObject(7000, 7, *(new Vector(*(new Point(-300, -100)), *(new Point(-0.1f, 0.05f))))));
	//spaceObjects->push_back(new SpaceObject(3000, 3, *(new Vector(*(new Point(-400, -200)), *(new Point(0.0f, 0.9f))))));

	//spaceObjects->push_back(new SpaceObject(8000, 8, *(new Vector(*(new Point(100, 0)), *(new Point(1.0f, 0.0f))))));
	//spaceObjects->push_back(new SpaceObject(1000, 2, *(new Vector(*(new Point(-100, 0)), *(new Point(3, 0.0f))))));

	int size = 40;
	int radius;
	for (int i = 0; i < size; ++i) {
		radius = rand() % 8 + 1;
		spaceObjects->push_back(new SpaceObject(radius * 500, radius, *(new Vector(*(new Point(rand() % 1600 - 800, rand() % 900 - 450)), *(new Point(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.6f)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.2f))))))));
	}

	glutMainLoop();
	
	return 0;
}