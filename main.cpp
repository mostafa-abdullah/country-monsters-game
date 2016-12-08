#include "GL/glut.h"
#include <bits/stdc++.h>
#include "config.h"
#include "GameObjects/object.h"
#include "GameObjects/hole.h"
#include "GameObjects/field.h"


using namespace std;

#define intToString( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 0.2f, 0.2f, 0.2, 1.0f };
	GLfloat shininess[] = { 50 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 3, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, windowWidth / windowHeight, 0.001, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 2.0, 3.0, 0, 2, 0, 0.0, 1.0, 0.0);
}

Field* f;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  setupLights();
	setupCamera();

  (*f).draw();

  glFlush();
}

void keyboardKey(unsigned char k, int x,int y)
{

	glutPostRedisplay();
}

void timeFunc(int val)
{
  glutPostRedisplay();
  glutTimerFunc(20,timeFunc,0);
}

void mouseMotion(int x, int y)
{

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{


}

void specialInput(int k, int x, int y)
{

	glutPostRedisplay();
}

int main(int argc, char **argv)
{
  srand(time(NULL));

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  gameID = glutCreateWindow("ACM");

  windowWidth = glutGet(GLUT_SCREEN_WIDTH);
  windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

  Field fTemp(5, 5, 10);
  f = &fTemp;

  glutFullScreen();
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardKey);
  glutPassiveMotionFunc(mouseMotion);
  glutMouseFunc(mouseClick);
  glutSpecialFunc(specialInput);
  glutTimerFunc(0,timeFunc,0);

  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);
  glutMainLoop();
}
