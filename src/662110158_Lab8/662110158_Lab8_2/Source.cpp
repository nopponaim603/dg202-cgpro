# include < windows.h >
# include < GL/glut.h >
#include <math.h>
float fog_colour[] = { 0.6f,0.58f,0.79f,0.0f };
float fog_density = 0.05f;
GLenum fog_mode = GL_EXP;
float far_distance = 200.0f;
float near_distance = 0.05f;
float zoom = 15.0f;
float angle = 0.0f;
float angleY = 0.0f;
float rotx = 0;
float roty = 0.1f;
float tx = 0;
float ty = 0;
int lastx = 0;
int lasty = 0;
unsigned char Button[3] = { 0 };

void Init()
{
	glClearColor(fog_colour[0], fog_colour[1], fog_colour[2], fog_colour[3]);
	glFogf(GL_FOG_START, near_distance);
	glFogf(GL_FOG_END, far_distance);
	glFogfv(GL_FOG_COLOR, fog_colour);
	glFogi(GL_FOG_MODE, fog_mode);
	glFogf(GL_FOG_DENSITY, fog_density);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void Reshape(int w, int h)
{
	if (w == 0)
		h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)w/h,near_distance,far_distance);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, -zoom);
	glTranslatef(tx, ty, 0);
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	for (int i = -100; i <= 100; i += 10)
	{
		for (int j = -100; j <= 100; j += 10)
		{
			glPushMatrix();
			glTranslatef(i, 0, j);
			glRotatef(0.0, 1.0, 0.0, 0.0);
			glRotatef(angleY, 0.0,1.0, 0.0);
			glutSolidTeapot(0.5);
			glPopMatrix();
		}
	}
	angleY = angleY + angle;
	glutSwapBuffer
}