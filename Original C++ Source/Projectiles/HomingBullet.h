#include "Bullet.h"
#pragma once

class HomingBullet :
	public Bullet
{
public:
	HomingBullet(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	~HomingBullet(void);
	void update(int dt);

private:
	void rotateTowardPlayer(int dt);
	float constrainAngle(float x);

	Player* player;
	float turnSpeed;
};

