# include < windows.h >
# include < GL/glut.h >
void init(void);
void display(void);
void reshape(int w, int h);
void drawMyObjects(void);

float angle = 0.0;
float angleX = 0.0;
float red = 0.0, green = 0.0, blue = 1.0;
float x_axis = 0.0, y_axis = 0.0, z_axis = 0.0;
int specialKey;

void init(void) 
{
	 glClearColor(0.0, 0.0, 0.0, 1.0);
	 glShadeModel(GL_SMOOTH);
	 glEnable(GL_DEPTH_TEST);
	 glDepthFunc(GL_LEQUAL);
	 glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void drawMyObjects() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(x_axis, y_axis, z_axis);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glRotatef(angleX, 1.0, 0.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	
	glBegin(GL_QUADS);
	 // draw blue square
    glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);

	glVertex3f(0.0f, 0.0f, 10.0f);
	glVertex3f(0.0f, 10.0f, 10.0f);
	glVertex3f(10.0f, 10.0f, 10.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glVertex3f(0.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 0.0f);
	glVertex3f(10.0f, 10.0f, 10.0f);
	glVertex3f(0.0f, 10.0f, 10.0f);

	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glEnd();

    glEnable(GL_BLEND);
	glBlendFunc ( GL_SRC_ALPHA , GL_ONE ) ;

	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);

	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(15.0f, 0.0f, 5.0f);
	glVertex3f(10.0f, 15.0f, 10.0f);

	glVertex3f(15.0f, 0.0f, 5.0f);
	glVertex3f(15.0f, 0.0f, 15.0f);
	glVertex3f(10.0f, 15.0f, 10.0f);

	glVertex3f(15.0f, 0.0f, 15.0f);
	glVertex3f(5.0f, 0.0f, 15.0f);
	glVertex3f(10.0f, 15.0f, 10.0f);

	glVertex3f(5.0f, 0.0f, 15.0f);
	glVertex3f(5.0f, 0.0f, 5.0f);
	glVertex3f(10.0f, 15.0f, 10.0f);

	glEnd();
	glDisable(GL_BLEND);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glScalef(0.5, 0.5, 0.5);
	drawMyObjects();
	glutSwapBuffers();
}

 void reshape(int w, int h)
 {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
 }

 void processNormalKeys(unsigned char key, int x, int y)
 {
	 switch (key)
	 {
	 case 27: exit(0); break;
	 case 'w': angleX++; break;
	 case 's': angleX--; break;
	 case 'a': angle--; break;
	 case 'd': angle++; break;
	 }
 }

 void processMousePassiveMotion(int x, int y)
 {
	 if (x < 0)
		 angleX = 0.0;
	 else if (x > 800)
		 angleX = 300.0;
	 else
		 angleX = 180.0 * ((float)x) / 800;

	 if (y < 0)
		 angle = 0.0;
	 else if (y > 800)
		 angle = 180.0;
	 else
		 angle = 180.0 * ((float)y) / 800;
 }

int main(int argc, char** argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	 // double buffered in RGB format
 glutInitWindowSize(640, 480);
 glutCreateWindow(" Blending program ");
 init(); // initialize stuff
 glutDisplayFunc(display);
 glutKeyboardFunc(processNormalKeys);
 glutPassiveMotionFunc(processMousePassiveMotion);
 glutIdleFunc(display);
 glutReshapeFunc(reshape);
 glutMainLoop();
 return 0;
}