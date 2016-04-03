#include "Boomer.h"

Boomer::Boomer(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	: Enemy(shape_, position_, scale_, axis_, rotation_, player_)
{
	shape->setColor(1.0f, 1.0f, 0.0f);
	dtScale = 0.00005f;
	targetPos = player->getPosition();
	float dX = targetPos.x - position.x;
	float dY = targetPos.y - position.y;
	dir = std::atan2(dY, dX) * 180 / 3.1459f;
	fireTime = 0;
	fireDelay = 1000;
	scoreValue = 50;
}

Boomer::~Boomer(void)
{
	int debrisCount = 12;
	for(int i = 0; i < debrisCount; i++)
	{
		createDebris(position, shapeScale * 0.5f, angle + 360 / debrisCount * i, 1, 1, 0);
	}
}

void Boomer::update(int dt)
{
	if(reachedTarget())
	{
		if(fireTime > fireDelay)
		{
			scoreValue = 0;
			fire();
		}
		else
		{
			fireTime += dt;
		}
	}
	else
	{
		move(dt);
	}
}

void Boomer::move(int dt)
{
	velocity = vec3(std::cos(dir * (3.1459f / 180)), std::sin(dir * (3.1459f / 180)), 0) * (dtScale * dt);
	position.x += velocity.x;
	position.y += velocity.y;
}

bool Boomer::reachedTarget()
{

	float dX = targetPos.x - position.x;
	float dY = targetPos.y - position.y;

	if(dX * dX + dY * dY < 0.01f * 0.01f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Boomer::fire()
{
	for(int i = 0; i < 8; i++)
	{
		createBullet(position, 45.0f * i);
	}
	alive = false;
}