#include "Bullet.h"

Bullet::Bullet(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_)
	:Entity(shape_, position_, scale_, axis_, rotation_)
{
	dtScale = 0.001f;
	shape->setColor(1, 0, 1);
	collide = false;
	collisionDelay = 200;
	collisionTime = 0;
}

Bullet::~Bullet(void)
{
}

bool Bullet:: detectCollision(Entity* ent)
{
	if(collide)
	{
		float dist = glm::length(ent->getPosition() - position);

		if(dist < ent->getScale().y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Bullet::checkOffScreen()
{
	if(position.x > 1 || position.x < -1 || position.y > 1 || position.y < -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Bullet::update(int dt)
{
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