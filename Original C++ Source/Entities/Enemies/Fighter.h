#include "Enemy.h"
#pragma once

class Fighter :
	public Enemy
{
public:
	Fighter(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	~Fighter(void);
	void update(int dt);

private:
	void fire();
};

