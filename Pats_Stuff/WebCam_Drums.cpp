// WebCam_Drums.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL\freeglut.h>
#include "Playfield.h"
#include "CrashCymbal.h"
#include <math.h>

long timeSinceLastFrame;
PlayField* p;
//CrashCymbal c(Vector(0, 0, -.1));

float FIELD_OF_VIEW = 45.0f;
float NEAR_CLIPPING_PLANE = .1f;
float BOARD_LOCATION = 1 + .1f;
float SCREEN_WIDTH = 1024;
float SCREEN_HEIGHT = 768;

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
	//c.update(elapsedTime);
	p->update(elapsedTime);
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glTranslated(0.0f, 0.0f, -10.0f);
	p->render();
	//c.render();
	glFlush();
	glutSwapBuffers();
}


void Display()
{
	Update();
	Render();
	glutPostRedisplay();
}

int _tmain(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("WebCam Drummer");
	glutDisplayFunc(Display);
	InitGL();
	p = new PlayField(tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE, tan(.5 * FIELD_OF_VIEW) * 2 * NEAR_CLIPPING_PLANE * (SCREEN_HEIGHT  / SCREEN_WIDTH), "poop");
	glutMainLoop();
	return 0;
}

