#include<windows.h>
#include<GL/glut.h>
#include<math.h>

#define PI 3.14159265358979324
using namespace std;

static int p = 6;
static int q = 4;
static float* vertices = NULL;
static float Xangle = 150.0, Yangle = 60.0, Zangle = 0.0;

float f(int i, int j)
{
	return (cos((-1 + 2 * (float)i / p) * PI));
}

float g(int i, int j)
{
	return (sin((-1 + 2 * (float)i / p) * PI));
}

float h(int i, int j)
{
	return (-1 + 2 * (float)j / q);
}

void fillVertexArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0;j <= q; j++)
		for (i = 0;i <= p; i++)
		{
			vertices[k++] = f(i, j);
			vertices[k++] = g(i, j);
			vertices[k++] = h(i, j);
		}
}

void setup(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void drawScene(void)
{
	int i, j;
	vertices = new float[3 * (p + 1) * (q + 1)];

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0,0.0, 1.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0, 0.0, 1.0);

	glRotatef(Zangle, 0.0, 0.0, 1.0);
	glRotatef(Yangle, 0.0, 1.0, 0.0);
	glRotatef(Xangle, 1.0, 0.0, 0.0);

	fillVertexArray();

	for (j = 0; j < q; j++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0;i <= p; i++)
		{
			glArrayElement((j + 1) * (p + 1) + i);
			glArrayElement(j * (p + 1) + i);
		}
		glEnd();
	}
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 50.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;

	case'x':
		Xangle += 5.0;
		if (Xangle > 360.0) Xangle -= 360.0;
		glutPostRedisplay();
		break;

	case 'X':
		Xangle -= 5.0;
		if (Xangle < 360.0) Xangle += 360.0;
		glutPostRedisplay();
		break;

	case 'y':
		Yangle += 5.0;
		if (Yangle > 360.0) Yangle -= 360.0;
		glutPostRedisplay();
		break;

	case 'Y':
		Yangle -= 5.0;
		if (Yangle < 360.0) Yangle += 360.0;
		glutPostRedisplay();
		break;

	case 'z':
		Zangle += 5.0;
		if (Zangle > 360.0) Zangle -= 360.0;
		glutPostRedisplay();
		break;

	case 'Z':
		Zangle -= 5.0;
		if (Zangle < 360.0) Zangle += 360.0;
		glutPostRedisplay();
		break;

	default:
		break;
	}
}

void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT) if (p > 3) p -= 1;
	if (key == GLUT_KEY_RIGHT)  p += 1;
	if (key == GLUT_KEY_DOWN) if (p > 3) q -= 1;
	if (key == GLUT_KEY_UP) q += 1;

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("cylinder.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);
	setup();
	glutMainLoop();
}