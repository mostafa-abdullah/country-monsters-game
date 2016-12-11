#include "GL/glut.h"
#include <bits/stdc++.h>
#include "config.h"
#include "constants.h"
#include "point.hpp"
#include "GameObjects/object.h"
#include "GameObjects/hole.h"
#include "GameObjects/monster.h"
#include "GameObjects/Weapons/weapon.hpp"
#include "GameObjects/Weapons/brick.hpp"
#include "GameObjects/Weapons/slippers.hpp"
#include "GameObjects/Weapons/mine.hpp"
#include "GameObjects/person.hpp"
#include "GameObjects/field.h"

using namespace std;

/*
TODO Other Features
Sounds
3D Models
Textures
Setup Lights
*/
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

Field* field;
Person* person;
bool gameOver = false;

void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, windowWidth / windowHeight, 0.001, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(person->location->x, person->location->y, person->location->z, person->lookAt->x, person->lookAt->y, person->lookAt->z, 0.0, 1.0, 0.0);
}
bool first = true;
void display(void)
{
	if(gameOver)
		return;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.6, 0.8, 1, 1);

  person->display_score();
	person->display_time();
  person->display_power();
  glPushMatrix();
  setupLights();
	setupCamera();

  field->draw();
  person->draw();
  glPopMatrix();

  glFlush();
}

void keyboardKey(unsigned char k, int x,int y)
{
  if(k == 'w') {
    person->move(Up);
  }
  else if(k == 'a') {
    person->move(Left);
  }
  else if(k == 's') {
    person->move(Down);
  }
  else if(k == 'd') {
    person->move(Right);
  }
  else if(k == '1') {
    person->set_weapon(new Brick());
  }
  else if(k == '2') {
    person->set_weapon(new Slippers());
  }
	else if(k == '3') {
		person->set_weapon(new Mine());
	}
	else if(k == 'q') {
		field->bombMine();
	}
	glutPostRedisplay();
}
int oldMouseX, oldMouseY;

void mouseMotion(int x, int y)
{
  y = windowHeight - y;
  if(x > oldMouseX) {
    person->look(Right);
  }
  else if(x < oldMouseX) {
    person->look(Left);
  }

  if(y > oldMouseY) {
    person->look(Up);
  }
  else if(y < oldMouseY) {
    person->look(Down);
  }

  if(x <= 1 || x >= windowWidth - 1) {
    glutWarpPointer(windowWidth / 2, y);
  }

  if(y <= 1 || y >= windowHeight - 1) {
    glutWarpPointer(x, windowHeight / 2);
  }

  oldMouseX = x;
  oldMouseY = y;

	glutPostRedisplay();
}

void mouseClick(int button, int state, int x, int y)
{
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    person->isFiring = true;
  }
  else if(state == GLUT_UP) {
    field->fire_weapon(person->fire_weapon());
  }
}

void timeFunc(int val)
{
  if(person->isFiring) {
    person->increase_power();
  }
	person->time -= 20;
	if(person->time <= 0 || field->person_on_hole()){
		displayString("GAME OVER!!", -0.5, 2.5, 0, 0, 0);
		gameOver = true;
	}
  field->update_field();
  glutPostRedisplay();
  glutTimerFunc(20,timeFunc,0);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  gameID = glutCreateWindow("ACM");
  glutFullScreen();
  windowWidth = glutGet(GLUT_SCREEN_WIDTH);
  windowHeight = glutGet(GLUT_SCREEN_HEIGHT);

  srand(time(NULL));

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardKey);
  glutPassiveMotionFunc(mouseMotion);
  glutMouseFunc(mouseClick);
  glutTimerFunc(20,timeFunc,0);
  glutSetCursor(GLUT_CURSOR_NONE);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glShadeModel(GL_SMOOTH);

  person = new Person();
  field = new Field(20, 20, 10, 5, person);

  glutMainLoop();
}
