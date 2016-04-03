#include "Stealth.h"


Stealth::Stealth(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	: Enemy(shape_, position_, scale_, axis_, rotation_, player_)
{
	shape->setColor(0.05f, 0.05f, 0.05f);
	dtScale = 0.0001f;
	fireTime = 0;
	fireDelay = 10000;
	scoreValue = 100;
}


Stealth::~Stealth(void)
{
	int debrisCount = 3;
	for(int i = 0; i < debrisCount; i++)
	{
		createDebris(position, shapeScale * 0.5f, angle + 360 / debrisCount * i, 0.05f, 0.05f, 0.05f);
	}
}

void Stealth::update(int dt)
{
	move(dt);

	if(player->isAlive())
	{
		rotateToPlayer();

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

void Stealth::fire()
{
	createBullet(position, angle);
}
