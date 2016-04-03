#include "Enemy.h"
#pragma once

class Boomer :
	public Enemy
{
public:
	Boomer(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	~Boomer(void);
	void update(int dt);

private:
	void fire();
	void move(int dt);
	bool reachedTarget();

	vec3 targetPos;
	float dir;
};

