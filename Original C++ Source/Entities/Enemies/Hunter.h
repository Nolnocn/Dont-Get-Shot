#include "Enemy.h"
#pragma once

class Hunter :
	public Enemy
{
public:
	Hunter(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	~Hunter(void);
	void update(int dt);

private:
	void fire();
};

