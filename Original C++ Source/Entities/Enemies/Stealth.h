#include "Enemy.h"
#pragma once

class Stealth :
	public Enemy
{
public:
	Stealth(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	~Stealth(void);
	void update(int dt);

private:
	void fire();
};

