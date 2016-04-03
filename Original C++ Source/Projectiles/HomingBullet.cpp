#include <math.h>
#include "HomingBullet.h"

HomingBullet::HomingBullet(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	:Bullet(shape_, position_, scale_, axis_, rotation_)
{
	player = player_;
	turnSpeed = 2.0f;
	dtScale = 0.0007f;
	shape->setColor(0, 1, 1);
}

HomingBullet::~HomingBullet(void)
{
}

void HomingBullet::update(int dt)
{
	if(player->isAlive())
	{
		rotateTowardPlayer(dt);
	}
	
	move(dt);

	if(!collide)
	{
		if(collisionTime > collisionDelay)
		{
			collide = true;
		}
		else
		{
			collisionTime += dt;
		}
	}
}

void HomingBullet::rotateTowardPlayer(int dt)
{
	float dX = player->getPosition().x - position.x;
	float dY = player->getPosition().y - position.y;
	float desiredAngle = std::atan2(dY, dX) * 180 / 3.1459f;
	
	angle = constrainAngle(angle + turnSpeed * dt * dtScale * constrainAngle(desiredAngle - angle));
}

float HomingBullet::constrainAngle(float x)
{
	x = fmod(x + 180.0f,360.0f);
	if (x < 0)
		x += 360;
    return x - 180.0f;
}