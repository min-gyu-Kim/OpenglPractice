#include <stdio.h>
#include <math.h>

#include <GL/freeglut.h>

//Draw Square
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
	{
		glVertex3f(-0.5f, -0.5f, 0.f);
		glVertex3f(0.5f, -0.5f, 0.f);
		glVertex3f(0.5f, 0.5f, 0.f);
		glVertex3f(-0.5f, 0.5f, 0.f);
	}
	glEnd();
	glFlush();
	//glutSwapBuffers();
}

//Draw Circle
void DrawCircle()
{
	constexpr GLfloat PI = 3.1415f;
	constexpr GLfloat PI_2 = PI * 2.0f;
	GLfloat ptSize[2];
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.f, 0.f, 0.f);
	glGetFloatv(GL_POINT_SIZE_RANGE, ptSize);
	glPointSize(ptSize[0] * 10);

	glBegin(GL_POINTS);
	{
		for (GLfloat fAngle = 0.f; fAngle <= PI_2; fAngle += PI / 20.f)
		{
			glVertex3f(cosf(fAngle), sinf(fAngle), 0.f);
		}
	}
	glEnd();
	glFlush();
}

void DrawPrimitive()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.4f, 0.3f);	

	glBegin(GL_POLYGON);
	{
		glVertex3f(0.f, 1.f, 0.f);
		glVertex3f(-1.f, 0.5f, 0.f);
		glVertex3f(-1.f, -0.5f, 0.f);
		glVertex3f(0.f, -1.f, 0.f);
		glVertex3f(1.f, -0.5f, 0.f);
		glVertex3f(1.f, 0.5f, 0.f);
	}
	glEnd();
	glFlush();
}

/* 기본 그리기
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	/* Draw Square
	glutCreateWindow("Opengl Initialize Test!");
	glutDisplayFunc(MyDisplay);
	*/

	/* Draw Circle
	glutCreateWindow("Draw Circle");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glutDisplayFunc(DrawCircle);
	

	//Draw Primitive
	glutCreateWindow("Draw Primitive");
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
	glutDisplayFunc(DrawPrimitive);

	glutMainLoop();

	return 0;
}
*/

GLUquadricObj* qobj = gluNewQuadric();

void MyInit(void) {
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat model_ambient[] = { 0.5, 0.4, 0.3, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
}

void DrawSphere() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);

	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricTexture(qobj, GL_FALSE);
	gluSphere(qobj, 1.5, 50, 50);

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-2.5, 2.5, -2.5 * (GLfloat)h / (GLfloat)w, 2.5 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Draw Sphere");
	MyInit();
	glutDisplayFunc(DrawSphere);
	glutReshapeFunc(Reshape);

	glutMainLoop();
	return 0;
}