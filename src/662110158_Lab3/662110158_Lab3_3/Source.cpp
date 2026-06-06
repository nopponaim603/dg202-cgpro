#include<windows.h>
#include<GL/glut.h>
#include<math.h>

float angle = 0.0, ratio;
float x = 0.0f, y = 0.0f, z = 20.0f;
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

void drawTorus(void)
{
	glColor3f(0.0, 0.0, 1.0);
	glutWireTorus(0.5, 3, 25, 50);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawTorus();
	glutSwapBuffers();
}

void init(void)
{
	glClearColor(1., 1.0, 1.0, 0.0);
}

void reshape(int w, int h)
{
	if (h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void orientMe(float ang)
{
	lx = sin(ang);
	lz = -cos(ang);
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void moveMeFlat(int i)
{
	x = x + i * (lx) * 1;
	z = z + i * (lz) * 1;
	glLoadIdentity();
	gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: angle += 0.2f; orientMe(angle); break;
	case GLUT_KEY_RIGHT: angle -= 0.2f; orientMe(angle); break;
	case GLUT_KEY_UP: moveMeFlat(1); break;
	case GLUT_KEY_DOWN: moveMeFlat(-2); break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("The camera view program");
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
