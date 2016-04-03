#include "Player.h"
#pragma once

class Bullet :
	public Entity
{
public:
	Bullet(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_);
	~Bullet(void);

	virtual void update(int dt);
	bool detectCollision(Entity* ent);
	bool checkOffScreen();

protected:
	bool collide;
	int collisionDelay;
	int collisionTime;
};