#include <Windows.h>
#include <gl/glut.h>

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glBegin(GL_TRIANGLES);
	
	glColor3ub((GLubyte)255, (GLubyte)0, (GLubyte)0);
	glVertex3f(0.0f, 200.0f, 0.0f);
	glColor3ub((GLubyte)0, (GLubyte)255, (GLubyte)0);
	glVertex3f(200.0f, -70.0f, 0.0f);
	glColor3ub((GLubyte)0, (GLubyte)0, (GLubyte)255);
	glVertex3f(-200.0f, -70.0f, 0.0f);

	glEnd();
	glutSwapBuffers();
}

void SetupRC()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}
void ChangeSize(int w, int h)
{
	GLfloat windowHeight, windowWidth;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glLoadIdentity();
	if (w <= h)
	{
		windowHeight = 250.0f * h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f * w / h;
		windowHeight = 250.0f;
	}
	glOrtho(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.0f, -1.0f);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("RGB Triangle");
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutMainLoop();
	return 0 ;
}