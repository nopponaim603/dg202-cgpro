#include<windows.h>
#include <gl/glut.h>

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glRotatef(xRot, 1.0f,0.0f, 0.0f);
	glRotatef(yRot, 0.0f,1.0f, 0.0f);
	glBegin(GL_QUADS);

	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)255);
	glVertex3f(50.0f, 50.0f, 50.0f);
	glColor3ub((GLubyte)255, (GLubyte)255, (GLubyte)0);
	glVertex3f(50.0f, -50.0f, 50.0f);
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(-50.0f, -50.0f, 50.0f);
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)255);
	glVertex3f(-50.0f, 50.0f, 50.0f);

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);//1

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);//2

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);//3

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);//4


	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);//5

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);//6

	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);//7

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);//8


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);//9

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);//10

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);//11

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);//12


	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, 50.0f);//13

	glColor3f(0.0f, 1.0f, 1.0f);
	glVertex3f(50.0f, 50.0f, -50.0f);//14

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, -50.0f);//15

	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(50.0f, -50.0f, 50.0f);//16


	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, 50.0f);//17

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-50.0f, 50.0f, -50.0f);//18

	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, -50.0f);//19

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-50.0f, -50.0f, 50.0f);//20


	glEnd();
	glPopMatrix();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DITHER);
	glShadeModel(GL_SMOOTH);
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
	GLfloat fAspect;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(35.0f, fAspect, 1.0f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -400.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("RGB Cube");
	glutReshapeFunc(ChangeSize);
	glutSpecialFunc(SpecialKeys);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0;
}