#include<windows.h>
#include<GL/glut.h>
void init(void);
void RenderScene(void);

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
}

void RenderScene(void)
{
	static GLfloat fElect1 = 0.0f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, 0.0f);
	glColor3ub(255, 0, 0);
	glutWireCube(30.0f);
	glColor3ub(255, 255, 0);

	glPushMatrix();
	glRotatef(fElect1, 0.0f, 0.0f, 0.0f);
	glTranslatef(-40.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 15, 15);
	glPopMatrix();

	/*glPushMatrix();
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(90.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glRotatef(360.0f, -45.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glVertex2f(-5, 5);
	glVertex2f(5, 5);
	glVertex2f(5, -5);
	glVertex2f(-5, -5);*/

	fElect1 += 10.0f;
	if (fElect1 > 360.0f)
		fElect1 = 0.0f;
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("GLUT TUTORIAL");
	init();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}
