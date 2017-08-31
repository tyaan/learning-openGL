/*
 * Enemy.h
 *
 *  Created on: 30/08/2017
 *      Author: singh
 */

#ifndef ENEMY_H_
#define ENEMY_H_

class Enemy {
float xInit, yInit;
float xPos, yPos;
public:

	Enemy();
	void move(float);
	void render(void);
	void attack(void);
	void increaseSpeed(void);
	float getX(void);
	float getY(void);
	float alive;
};

#endif /* ENEMY_H_ */
