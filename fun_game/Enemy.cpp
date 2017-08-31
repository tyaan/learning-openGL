/*
 * Enemy.cpp
 *
 *  Created on: 30/08/2017
 *      Author: singh
 */

#include "Enemy.h"
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

Enemy::Enemy() {
	xInit = (8.0)*((1.0*rand()-(RAND_MAX/2))/RAND_MAX);
	yInit = 3.0;
	xPos = xInit;
	yPos = yInit;
	alive = false;
}

void Enemy::move(float speed){
	xPos = xInit;
	yPos = yPos - speed;

	if(yPos< -5.0)
		alive = false;
}

void Enemy::render(){
	glLineWidth(7.0);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
		for(int i=0; i<10; i++)
		{
			glVertex2f(xPos + 0.2*sin(1.0*(glutGet(GLUT_ELAPSED_TIME)-20.0*i)/40), yPos+1.0*i/10);
		}
	glEnd();
}

void Enemy::attack(){
	alive = true;
}

float Enemy::getX(){
	return xPos;
}

float Enemy::getY(){
	return yPos;
}

