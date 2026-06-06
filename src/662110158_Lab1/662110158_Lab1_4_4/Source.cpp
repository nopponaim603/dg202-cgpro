#include <windows.h>
#include <gl/glut.h>

void SetupRC(void);
void RenderScene(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("GLUT Tutorial");
	SetupRC();
	glutDisplayFunc(RenderScene);
	glutMainLoop();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(5.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-20.0f, 60.0f, 0.0f);
	glVertex3f(20.0f, 20.0f, 0.0f);
	glVertex3f(7.0f, 17.0f, 0.0f);
	glVertex3f(40.0f, -20.0f, 0.0f);
	glVertex3f(23.0f, -26.0f, 0.0f);
	glVertex3f(40.0f, -80.0f, 0.0f);
	glVertex3f(-20.0f, -40.0f, 0.0f);
	glVertex3f(-20.0f, 0.0f, 0.0f);
	glVertex3f(-23.0f, 3.0f, 0.0f);
	glVertex3f(-60.0f, 40.0f, 0.0f);
	glVertex3f(-20.0f, 60.0f, 0.0f);
	glEnd();
	glFlush();
}

void SetupRC(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -150.0, 150.0);
}
