/*
 * fun_game.cpp
 * wow, fun game! 
 *
 *  Created on: 29/08/2017
 *      Author: singh
 */

#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <stdlib.h>

#include "Bullet.h"
#include "Enemy.h"

#define PI 3.14159265

void glutInit(){
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

int MAX_LIVES = 5;
int lives = MAX_LIVES;

float MAX_Y = 3.0;
float MAX_X = 5.0;

bool specialKeyBuffer[256];
bool keyBuffer[256];

float currentY = 0.0; //represents the current y position of the graphic
float currentX = 0.0; //represents the current x position of the graphic
float speed = 0.01;

Bullet b[30];
int MAX_BULLETS = 30;
int numBullet=0;

float enemySpeed = 0.001;
Enemy e[30];
int MAX_ENEMY = 30;
int numEnemy=0;

int t = 0; //represents time since glutInit() in milliseconds
int prevTime = 0; //used for displaying enemies at regular intervals
float initPointSize = 10.0;
float numPoints = 20;
float circleRad = 0.2; //radius of circle in middle
float helixRad = 0.6;

/*
* Draws bottom and top bar
*/
void drawBars(){
	glColor3f(0.5, 1.0, 1.0);
	glBegin(GL_QUADS);
		glVertex2f(-MAX_X-2.0, -MAX_Y);
		glVertex2f(-MAX_X-2.0, -MAX_Y-2.0);
		glVertex2f(MAX_X+2.0, -MAX_Y-2.0);
		glVertex2f(MAX_X+2.0, -MAX_Y);
	glEnd();
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex2f(-MAX_X-2.0, MAX_Y);
		glVertex2f(MAX_X+2.0, MAX_Y);
		glVertex2f(MAX_X+2.0, MAX_Y+2.0);
		glVertex2f(-MAX_X-2.0, MAX_Y+2.0);
	glEnd();
}

/*
 * Draws main boy
 */
void drawMainBoy(){
	float pointSize = initPointSize;
	glLineWidth(3.0);

	//set position of helix
	if(specialKeyBuffer[GLUT_KEY_UP] && currentY<MAX_Y)
		currentY = currentY+speed;
	else if(specialKeyBuffer[GLUT_KEY_DOWN] && currentY>(-MAX_Y))
		currentY = currentY-speed;
	if(specialKeyBuffer[GLUT_KEY_RIGHT] && currentX<MAX_X)
		currentX = currentX+speed;
	else if(specialKeyBuffer[GLUT_KEY_LEFT] && currentX>(-MAX_X))
		currentX = currentX-speed;

	//draw helix
	float y = currentY; //variable to represent dot y position
	float i = 0; //increment for loop
	for(;i<numPoints;i++)
	{
		glPointSize(pointSize);
		//helix color deteriorates as life is lost
		glColor3f(1.0, (1-(1.0*lives/MAX_LIVES)), (1-(1.0*lives/MAX_LIVES)));
		if(lives==0 && y<-MAX_Y)
			glColor3f(0.5, 1.0, 1.0);
		glBegin(GL_POINTS);
			glVertex3f(helixRad*cos((1.0*t/100)-(i/10))+currentX, y, helixRad*sin((1.0*t/100)-(i/10)));
			glVertex3f(-helixRad*cos((1.0*t/100)-(i/10))+currentX, y, -helixRad*sin((1.0*t/100)-(i/10)));
		glEnd();

		pointSize = pointSize - 0.5;
		if(pointSize<1.0)
			pointSize = 1.0;

		y = y - 0.2; //decrement y position of points
	}

	//draw circle
	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
		i=0;
		for(;i<360;i++)
		{
			float fi = (i*PI/180);
			glVertex3f(circleRad*cos(fi)+currentX, circleRad*sin(fi)+currentY, 0.0);
		}
	glEnd();
}

/*
 * Draws bullet
 */
void drawBullets(){
	for(int i=0; i<MAX_BULLETS; i++)
	{
		if(b[i].created)
		{
			b[i].move(currentX, currentY);
			b[i].render();
		}
	}
}

/*
 * Draws enemies
 */
void drawEnemies(){
	float p = t;
	if(t>125000)
		p = 100000;
	if(t>prevTime+3000-p/ 50 )
	{
		prevTime = t;
		e[numEnemy] = Enemy();
		e[numEnemy].attack(); //make next enemy alive
		numEnemy++;

		if(numEnemy>=MAX_ENEMY)
			numEnemy=0;

		enemySpeed = enemySpeed*1.02;
		if(enemySpeed > 0.003)
			enemySpeed = 0.003;
	}
	for(int i=0; i<MAX_ENEMY; i++)
	{
		if(e[i].alive)
		{
			e[i].move(enemySpeed);
			e[i].render();
		}
	}
}

void renderScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(0.0f, 0.0f, 10.0f,
			  0.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f);

	t = glutGet(GLUT_ELAPSED_TIME);

	drawBars();
	drawMainBoy();
	drawBullets();
	drawEnemies();

	//Check to see if bullet has hit enemy
	for(int i=0; i<MAX_BULLETS; i++)
	{
		for(int j=0; j<MAX_ENEMY; j++)
		{
			if(b[i].getX() < e[j].getX()+0.2 &&
			   b[i].getX() > e[j].getX()-0.2 &&
			   b[i].getY() < e[j].getY()+0.5 &&
			   b[i].getY() > e[j].getY() &&
			   b[i].created && e[j].alive )
			{
				b[i].destroy();
				e[j] = Enemy();
			}

		}
	}

	//Check to see if enemy has hit main boy or reached bottom
	for(int j=0; j<MAX_ENEMY; j++)
	{
		if((e[j].getX() < currentX + circleRad &&
		   e[j].getX() > currentX - circleRad &&
		   e[j].getY() < currentY + circleRad &&
		   e[j].getY() > currentY - circleRad -0.5 &&
		   e[j].alive) ||
		   (e[j].getY() < -MAX_Y && e[j].alive))
		{
		lives--;
		e[j] = Enemy();
		}
		if(lives<0)
		{
			exit(0);
		}
	}


	glutSwapBuffers();
}

void changeSize(int w, int h){
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).

	glutReshapeWindow(1500, 900);

	float ratio = 1.5;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	//glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);


	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void specialKeyDown(int key, int x, int y){
	specialKeyBuffer[key] = true;
}

void specialKeyUp(int key, int x, int y){
	specialKeyBuffer[key] = false;
}

void keyDownFunc(unsigned char key, int x, int y){
	keyBuffer[key] = true;
	//create bullet when spacebar initially pressed
	if(key==32)
	{
		b[numBullet].create();
	}
}

void keyUpFunc(unsigned char key, int x, int y){
	keyBuffer[key] = false;
	//set shot boolean when spacebar initially released
	if(key==32)
	{
		b[numBullet].shoot();

		numBullet++;
		if(numBullet==MAX_BULLETS)
			numBullet=0;

		b[numBullet].destroy();
	}
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(100, 10);
	glutCreateWindow("");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glutKeyboardFunc(keyDownFunc);
	glutKeyboardUpFunc(keyUpFunc);

	glutInit();

	glutMainLoop();

	return 0;
}

