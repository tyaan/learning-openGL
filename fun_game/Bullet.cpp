/*
 * Bullet.cpp
 *
 *  Created on: 30/08/2017
 *      Author: singh
 */

#include <GL/glut.h>
#include "Bullet.h"

Bullet::Bullet() {
	xPos = 0.0;
	yPos = 0.0;
}

void Bullet::move(float x, float y){
	if(shot)
	{
		yPos = yPos + 0.005;
	}
	else
	{
		xPos = x;
		yPos = y;
	}

	if(yPos>5.0)
	{
		created = false;
		shot = false;
	}
}

void Bullet::render(){
	if(created)
	{
		glColor3f(0.0, 0.0, 0.0);
		glPointSize(10.0);
		glBegin(GL_POINTS);
			glVertex3f(xPos, yPos, 0.0);
		glEnd();
	}
}

void Bullet::shoot(){
	shot = true;
}

void Bullet::create(){
	created = true;
}

void Bullet::destroy(){
	created = false;
	shot = false;
}

float Bullet::getX(){
	return xPos;
}

float Bullet::getY(){
	return yPos;
}
