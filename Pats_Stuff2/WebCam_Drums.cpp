// WebCam_Drums.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Playfield.h"
#include "CrashCymbal.h"
#include "Font.h"
#include "Vector.h"
#include <sstream>
#include <math.h>
#include <string>

double counter = 0;
long timeSinceLastFrame;
PlayField* p;
//CrashCymbal c(Vector(0, 0, -.1));
Vector left;
Vector right;
float FIELD_OF_VIEW = 45.0f;
float NEAR_CLIPPING_PLANE = .1f;
float BOARD_LOCATION = 1 + .1f;
float SCREEN_WIDTH = 1280;
float SCREEN_HEIGHT = 1024;
float GL_SCREEN_HEIGHT = tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE * (SCREEN_HEIGHT  / SCREEN_WIDTH);
float GL_SCREEN_WIDTH = tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE;

void InitGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glViewport(0, 0, 1024, 768);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, SCREEN_WIDTH / SCREEN_HEIGHT, NEAR_CLIPPING_PLANE, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void Update()
{
	long time = glutGet(GLUT_ELAPSED_TIME);
	double elapsedTime = (double)(time - timeSinceLastFrame) / 1000;
	timeSinceLastFrame = time;
	counter += elapsedTime;
	//c.update(elapsedTime);
	p->update(elapsedTime, left, right);
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslated(0.0f, 0.0f, -10.0f);
	p->render();
	//c.render();
	std::string result;
	std::ostringstream convert;
	convert << counter;
	result += convert.str();
	counter++;
	glFlush();
	glutSwapBuffers();
}


void Display()
{
	Update();
	Render();
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	float glX = (x - SCREEN_WIDTH / 2) * (GL_SCREEN_WIDTH / SCREEN_WIDTH);
	float glY = -(y - SCREEN_HEIGHT / 2) * (GL_SCREEN_HEIGHT / SCREEN_HEIGHT);
	left.setX(glX);
	left.setY(glY);
}

int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("WebCam Drummer");
	glutDisplayFunc(Display);
	glutMouseFunc(Mouse);
	//left.setX(-.0218);
	//left.setY(-.0371);
	InitGL();
	p = new PlayField((tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE) - .06, tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE * (SCREEN_HEIGHT  / SCREEN_WIDTH), .03, 0, "CantTouchThis.gh");
	glutMainLoop();
	return 0;
}

