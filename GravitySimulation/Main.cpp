#include "Header.h";
#include "GeometryHeader.h";
#include <vector>;
#include "SpaceObjectHeader.h";

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

void Update() 
{

}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	GLint scale = 1.0f;

	//glClearColor(0.5f, 0.5f, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, -500, 500, 0, 0);
	glMatrixMode(GL_MODELVIEW);

	
	std::vector<SpaceObject*> spaceObjects;// = new std::vector<SpaceObject*>();

	spaceObjects.push_back(new SpaceObject(10000, 0.9f, *(new Vector(*(new Point(0, 0)), *(new Point(0, 0))))));
	//spaceObjects.push_back(new SpaceObject(5000, 150, *(new Vector(*(new Point(80, 50)), *(new Point(3, 4))))));
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */

		int size = spaceObjects.size();

		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (i == j) {
					continue;
				}
				else {
					if (spaceObjects[i] == nullptr || spaceObjects[j] == nullptr) {
						continue;
					}
					spaceObjects[i]->Interact(spaceObjects[j]);
				}
			}
		}

		for (int i = 0; i < size; ++i) {
			spaceObjects[i]->MoveObject();
		}

		for (int i = 0; i < size; ++i) {
			//spaceObjects[i]->DrawFilledCircle();
			DrawFilledCircle(0, 0, 3);
		}

		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}