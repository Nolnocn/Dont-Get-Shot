#include "Enemy.h"

Enemy::Enemy(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_)
	:Entity(shape_, position_, scale_, axis_, rotation_)
{
	player = player_;
}

Enemy::~Enemy(void)
{
	addToScore(scoreValue);
}

void Enemy::update(int dt){}

void Enemy::fire(){}

void Enemy::rotateToPlayer()
{
	float dX = player->getPosition().x - position.x;
	float dY = player->getPosition().y - position.y;
	angle = std::atan2(dY, dX) * 180 / 3.1459f;
}

bool Enemy::onScreen()
{
	if(position.x < 1 && position.x > -1 && position.y < 1 && position.y > -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Enemy::leave()
{
	angle += 180 + (float)(rand() % 60) - 30;
}