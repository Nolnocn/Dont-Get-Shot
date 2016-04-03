#include "Hunter.h"


Hunter::Hunter(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	: Enemy(shape_, position_, scale_, axis_, rotation_, player_)
{
	shape->setColor(1, 0.65f, 0);
	dtScale = 0.0002f;
	fireTime = 0;
	fireDelay = 3000;
	scoreValue = 25;
}


Hunter::~Hunter(void)
{
	int debrisCount = 20;
	for(int i = 0; i < debrisCount; i++)
	{
		createDebris(position, shapeScale * 0.5f, angle + 360 / debrisCount * i, 1, 0.65f, 0);
	}
}

void Hunter::update(int dt)
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

void Hunter::fire()
{
	createHomingBullet(position, angle);
}
