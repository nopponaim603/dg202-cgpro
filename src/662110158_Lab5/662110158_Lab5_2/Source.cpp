#include <windows.h>
#include <GL/glut.h>
#include <math.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.5);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	GLfloat ambient[] = { 0.24725, 0.1995, 0.0745, 1.0 };
	GLfloat diffuse[] = { 0.75164, 0.60648, 0.22648, 1.0 };
	GLfloat specular[] = { 0.628281, 0.555802, 0.366065, 1.0 };
	GLfloat position0[] = { 150.0, 150.0, 150.0, 0.0 };
	GLfloat specref[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 50);
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glColor3ub(255, 255, 255);
	glBegin(GL_TRIANGLES);

	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(15.0f, 0.0f, 30.0f);

	glColor3ub(0, 0, 0);
	glVertex3f(15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, 60.0f);

	glColor3ub(255, 0, 0);
	glVertex3f(0.0f, 0.0f, 60.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);

	glColor3ub(0, 255, 0);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);

	glColor3ub(255, 255, 0);
	glVertex3f(0.0f, 0.0f, -56.0f);
	glVertex3f(0.0f, 15.0f, 30.0f);
	glVertex3f(15.0f, 0.0f, 30.0f);

	glColor3ub(0, 255, 255);
	glVertex3f(15.0f, 0.0f, 30.0f);
	glVertex3f(-15.0f, 0.0f, 30.0f);
	glVertex3f(0.0f, 0.0f, -56.0f);

	glColor3ub(128, 128, 128);
	glVertex3f(0.0f, 2.0f, 27.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);
	glVertex3f(60.0f, 2.0f, -8.0f);

	glColor3ub(64, 64, 64);
	glVertex3f(60.0f, 2.0f, -8.0f);
	glVertex3f(0.0f, 7.0f, -8.0f);
	glVertex3f(0.0f, 2.0f, 27.0f);

	glColor3ub(192, 192, 192);
	glVertex3f(60.0f, 2.0f, -8.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);
	glVertex3f(0.0f, 7.0f, -8.0f);

	glColor3ub(64, 64, 64);
	glVertex3f(0.0f, 2.0f, 27.0f);
	glVertex3f(0.0f, 7.0f, -8.0f);
	glVertex3f(-60.0f, 2.0f, -8.0f);

	glColor3ub(255, 128, 255);
	glVertex3f(-30.0f, -0.50f, -57.0f);
	glVertex3f(30.0f, -0.50f, -57.0f);
	glVertex3f(0.0f, -0.50f, -40.0f);

	glColor3ub(255, 128, 0);
	glVertex3f(0.0f, -0.5f, -40.0f);
	glVertex3f(30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f, 4.0f, -57.0f);

	glColor3ub(255, 128, 0);
	glVertex3f(0.0f, 4.0f, -57.0f);
	glVertex3f(-30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f, -0.5f, -40.0f);

	glColor3ub(255, 255, 255);
	glVertex3f(30.0f, -0.5f, -57.0f);
	glVertex3f(-30.0f, -0.5f, -57.0f);
	glVertex3f(0.0f, 4.0f, -57.0f);

	glColor3ub(255, 0, 0);
	glVertex3f(0.0f, 0.5f, -40.0f);
	glVertex3f(3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f, 25.0f, -65.0f);

	glColor3ub(255, 0, 0);
	glVertex3f(0.0f, 25.0f, -65.0f);
	glVertex3f(-3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f, 0.5f, -40.0f);

	glColor3ub(128, 128, 128);
	glVertex3f(3.0f, 0.5f, -57.0f);
	glVertex3f(-3.0f, 0.5f, -57.0f);
	glVertex3f(0.0f, 25.0f, -65.0f);
	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void SpecialKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
		xRot -= 5.0f;
	if (key == GLUT_KEY_DOWN)
		xRot += 5.0f;
	if (key == GLUT_KEY_LEFT)
		yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
	if (key > 356.0f)
		xRot = 0.0f;
	if (key < -1.0f)
		xRot = 355.0f;
	if (key > 356.0f)
		yRot = 0.0f;
	if (key < -1.0f)
		yRot = 355.0f;
	glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
	GLfloat nRange = 80.0f;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
	else
		glOrtho(-nRange*w/h, nRange*w/h, -nRange , nRange, -nRange, nRange);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Jet");
	init();
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}