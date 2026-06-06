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
	GLfloat fSizes[2];
	GLfloat fCurrSize;
	GLint factor = 3;
	GLushort pattern = 0x5555;
	glGetFloatv(GL_LINE_WIDTH_RANGE, fSizes);
	fCurrSize = fSizes[0];
	fCurrSize = 1;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(5.0f);
	glLineWidth(fCurrSize);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(factor, pattern);
	glBegin(GL_LINE_LOOP);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(80.0f, 50.0f, 0.0f);
	glVertex3f(50.0f, 90.0f, 0.0f);
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
