#include <windows.h>
#include <GL/glut.h>
float angle = 0.0;
float angleX = 0.0;
float red = 0.0, green = 0.0, blue = 1.0;
float x_axis = 0.0, y_axis = 0.0, z_axis = 0.0;
int specialKey;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(x_axis, y_axis, z_axis);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

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

void processMouse(int button, int state, int x, int y)
{
	specialKey = glutGetModifiers();
	if ((state == GLUT_DOWN) && (specialKey == GLUT_ACTIVE_ALT))
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			red = 1.0; green = 0.0; blue = 0.0;
		}
		else if (button == GLUT_MIDDLE_BUTTON)
		{
			red = 0.0; green = 1.0; blue = 0.0;
		}
		else
		{
			red = 0.0; green = 0.0; blue = 1.0;
		}
	}
}

void processMouseActiveMotion(int x, int y)
{
	if (x < 0)
		red = 0.0;
	else if (x > 800)
		red = 1.0;
	else
		red = ((float)x) / 800;
	if (y < 0)
		green = 0.0;
	else if (y > 600)
		green = 1.0;
	else
		green = ((float)y) / 600;
	blue = 0.0;
}

void processMousePassiveMotion(int x, int y)
{
	if (x < 0)
		angleX = 0.0;
	else if (x > 800)
		angleX = 180.0;
	else
		angleX = 180.0 * ((float) x) / 800;
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

int main(int argc, char ** argv)
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
	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseActiveMotion);
	glutPassiveMotionFunc(processMousePassiveMotion);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
