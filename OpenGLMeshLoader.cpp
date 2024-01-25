#pragma once
#include <Level1.h>
#include <Level2.h>
#include <irrKlang.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>

using namespace std;
using namespace irrklang;

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

int WIDTH = 1280;
int HEIGHT = 720;

ISoundEngine* background = createIrrKlangDevice();

char title[] = "3D Model Loader Sample";

// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 100;

int level = 1;
Level1 level1 = Level1();
Level2 level2 = Level2();

class Vector
{
public:
	GLdouble x, y, z;
	Vector() {}
	Vector(GLdouble _x, GLdouble _y, GLdouble _z) : x(_x), y(_y), z(_z) {}
	//================================================================================================//
	// Operator Overloading; In C++ you can override the behavior of operators for you class objects. //
	// Here we are overloading the += operator to add a given value to all vector coordinates.        //
	//================================================================================================//
	void operator +=(float value)
	{
		x += value;
		y += value;
		z += value;
	}
};

Vector Eye(20, 5, 20);
Vector At(0, 0, 0);
Vector Up(0, 1, 0);

int cameraZoom = 0;

//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	if (level == 1) {
		level1.InitLightSource1();
	}
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	if (level == 1) {
		level1.InitMaterial();
	}
	else {
		// Enable Material Tracking
		glEnable(GL_COLOR_MATERIAL);

		// Sich will be assigneet Material Properties whd by glColor
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

		// Set Material's Specular Color
		// Will be applied to all objects
		GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

		// Set Material's Shine value (0->128)
		GLfloat shininess[] = { 96.0f };
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	}
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	if (level == 1) {
		level1.myInit();
	}
	else {
		glClearColor(0.0, 0.0, 0.0, 0.0);

		glMatrixMode(GL_PROJECTION);

		glLoadIdentity();

		gluPerspective(fovy, aspectRatio, zNear, zFar);
		//***********//
		// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
		// aspectRatio:		Ratio of width to height of the clipping plane.							 //
		// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
		//***********//

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
		//***********//
		// EYE (ex, ey, ez): defines the location of the camera.									 //
		// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
		// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
		//***********//

		InitLightSource();

		InitMaterial();

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_NORMALIZE);
	}
}

//=======================================================================
// Light Setup Function
//=======================================================================
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	// set the light source properties
	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

//=======================================================================
// Camera Setup Function
//=======================================================================
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (level == 1) {
		level1.camera.look();
	}
	else {
		level2.camera.look();
	}
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	setupCamera();
	setupLights();

	// Start drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (level1.finished) {
		level = 2;
		level2.startUpdateGameVariables(level1.score, level1.player.playerHealth, level1.player.playerAttackDamage);
	}


	if (level == 1) {
		GLfloat lightIntensity[] = { 0.1, 0.1, 0.1, 0.0f };
		GLfloat lightPosition[] = { 0.0f, 100.0f, 0.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lightIntensity);
		InitLightSource();
		/*GLfloat lightIntensity1[] = { 0.5f, 0.0f, 0.0f, 1.0f };
		glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);*/
		level1.myDisplay();
	}
	else {
		level2.myDisplay();
	}


	glutSwapBuffers();
}

//=======================================================================
// My Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	if (level == 1) {
		level1.Mouse(x, y);
	}
	else {
		level2.Mouse(x, y);
	}

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(Eye.x, Eye.y, Eye.z, At.x, At.y, At.z, Up.x, Up.y, Up.z);
}

//=======================================================================
// Keyboard Function
//=======================================================================
void Keyboard(unsigned char key, int x, int y) {
	if (level == 1) {
		level1.Keyboard(key, x, y);
	}
	else {
		level2.Keyboard(key, x, y);
	}

	glutPostRedisplay();
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	level1.LoadAssets();
	level2.LoadAssets();
}

//=======================================================================
// Timer Functions
//=======================================================================
void TimerLevel1(int value) {

	if (level == 1) {
		level1.fight(20, 20, -20, -20);

		// Reset the state of the player
		level1.player.playerState = 0;
	}

	glutTimerFunc(1000, TimerLevel1, 0);
}

void Timer1Level2(int value) {
	if (level == 2) {
		if (level2.couldBossAttack()) {
			level2.bossAttackTime--;
			if (level2.bossAttackTime == 0) {
				level2.bossAttack();
				level2.bossAttackTime = 3;
			}
		}
		glutPostRedisplay();
	}

	glutTimerFunc(1000, Timer1Level2, 0);
}

void Timer2Level2(int val) {
	if (level == 2) {
		level2.moveBoss();
		glutPostRedisplay();
	}

	glutTimerFunc(500, Timer2Level2, 0);
}

//=======================================================================
// Animation Function
//=======================================================================
void Anim() {
	glutPostRedisplay();
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	//background->play2D("media/background.mp3", GL_TRUE);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);

	glutDisplayFunc(myDisplay);

	glutKeyboardFunc(Keyboard);

	glutMotionFunc(myMotion);

	glutIdleFunc(Anim);

	glutTimerFunc(1000, TimerLevel1, 0);

	glutTimerFunc(1000, Timer1Level2, 0);

	glutTimerFunc(1000, Timer2Level2, 0);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}