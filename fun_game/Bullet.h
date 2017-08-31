/*
 * Bullet.h
 *
 *  Created on: 30/08/2017
 *      Author: singh
 */

#ifndef DEBUG_BULLET_H_
#define DEBUG_BULLET_H_

class Bullet {
	float xPos, yPos;
public:
	Bullet();
	void move(float, float);
	void render(void);
	void shoot(void);
	void create(void);
	void destroy(void);
	float getX(void);
	float getY(void);
	bool created = false;
	bool shot = false;
};

#endif /* DEBUG_BULLET_H_ */
