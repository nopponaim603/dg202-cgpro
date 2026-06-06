#include <windows.h>
#include <GL/glut.h>
float angle = 0.0;
float red = 0.0, green = 0.0, blue = 1.0;
float x_axis = 0.0, y_axis = 0.0, z_axis = 0.0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(x_axis, y_axis, z_axis);
	glRotatef(angle, 0.0, 1.0, 0.0);

	glColor3f(red, green, blue);
	glBegin(GL_QUADS);

	glVertex3f(-2.0, -2.0, 0.0);
	glVertex3f(-2.0, 2.0, 0.0);
	glVertex3f(2.0, 2.0, 0.0);
	glVertex3f(2.0, -2.0, 0.0);
	glVertex3f(-2.0, -2.0, 0.0);

	glEnd();
	glPopMatrix();
	angle++;
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) 
{
	switch (key) 
	{
	case 27: exit(0); break;
	case 'w': x_axis += 0.0; y_axis += 1.0; z_axis += 0.0; break;
	case 's': x_axis -= 0.0; y_axis += -1.0; z_axis += 0.0; break;
	case 'a': x_axis -= 1.0; y_axis += 0.0; z_axis += 0.0; break;
	case 'd': x_axis += 1.0; y_axis -= 0.0; z_axis += 0.0; break;

	case 'i': x_axis += 0.0; y_axis += 1.0; z_axis += 0.0; break;
	case 'k': x_axis -= 0.0; y_axis += -1.0; z_axis += 0.0; break;
	case 'j': x_axis -= 1.0; y_axis += 0.0; z_axis += 0.0; break;
	case 'l': x_axis += 1.0; y_axis -= 0.0; z_axis += 0.0; break;
	}
}

void processSpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1: red = 1.0; green = 1.0; blue = 0.0; break; //yellow
	case GLUT_KEY_F2: red = 0.0; green = 1.0; blue = 0.0; break; //green
	case GLUT_KEY_F3: red = 0.0; green = 0.0; blue = 1.0; break; //blue

	case GLUT_KEY_F4: red = 1.0; green = 0.0; blue = 0.0; break; //red
	case GLUT_KEY_F5: red = 1.0; green = 0.0; blue = 1.0; break; //purple
	case GLUT_KEY_F6: red = 0.0; green = 1.0; blue = 1.0; break; //cyan
	case GLUT_KEY_F7: red = 0.0; green = 0.0; blue = 0.0; break; //black
	case GLUT_KEY_F8: red = 1.0; green = 1.0; blue = 1.0; break; //white

	default: red = 0.0; green = 0.0; blue = 0.0; break;
	}
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("GLUT Tutorial");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
