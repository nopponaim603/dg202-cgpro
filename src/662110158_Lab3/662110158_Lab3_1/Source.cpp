#include<windows.h>
#include<GL/glut.h>
void init(void);
void RenderScene(void);

void init(void)
{
	glClearColor(0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -150.0, 150.0);
}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat fAspect;
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0f, fAspect, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(1, 1, 1, 0, 0, 0, 0, 1, 1);

	GLfloat mat_speculla[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_diffuse[] = { 1,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 1.0,1.0,1.0,1.0 };
	GLfloat mat_shininess[] = { 10.0};
	GLfloat light_position[] = { -1.0,2.0,0.0,0.0 };
	GLfloat light_spec[] = { 1.0,1.0,1.0,0.0 };
	GLfloat light_amb[] = { 1,0.5,0.0,0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_speculla);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spec);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glTranslatef(0.1f, 0.1f, 0.1f);
	glutSolidCube(0.2f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.2f, 0.5f,0.2f);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.2, -0.5f, -0.8f);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Perspective Projections");
	init();
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();
}