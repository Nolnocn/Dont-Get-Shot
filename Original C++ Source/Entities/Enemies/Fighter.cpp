#include "Fighter.h"


Fighter::Fighter(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	: Enemy(shape_, position_, scale_, axis_, rotation_, player_)
{
	shape->setColor(1, 0, 0);
	dtScale = 0.00025f;
	fireTime = 0;
	fireDelay = 1000;
	scoreValue = 10;
}


Fighter::~Fighter(void)
{
	int debrisCount = 4;
	for(int i = 0; i < debrisCount; i++)
	{
		createDebris(position, shapeScale * 0.5f, angle + 360 / debrisCount * i, 1, 0, 0);
	}
}

void Fighter::update(int dt)
{
	move(dt);
	if(player->isAlive())
	{
		rotateToPlayer();
		if(onScreen())
		{
			if(fireTime > fireDelay)
			{
				fire();
				fireTime = 0;
			}
			else
			{
				fireTime += dt;
			}
		}
	}
}

void Fighter::fire()
{
	createBullet(position, angle);
}
