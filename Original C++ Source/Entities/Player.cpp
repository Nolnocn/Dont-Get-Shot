#include "Player.h"

Player::Player(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_)
	:Entity(shape_, position_, scale_, axis_, rotation_)
{
	shape->setColor(0.0f, 1.0f, 0.0f);
	dtScale = 0.0005f;
	alive = true;
}

Player::~Player(void)
{
}

void Player::update(int dt)
{
	moveToMouse(dt);
	//move(dt);
}

void Player::moveToMouse(int dt)
{
	vec3 mouse = getMousePosition();

	float dX = mouse.x - (position.x + 1) * (glutGet(GLUT_WINDOW_WIDTH) * 0.5f);
	float dY = mouse.y - ((glutGet(GLUT_WINDOW_HEIGHT) - (position.y + 1) * (glutGet(GLUT_WINDOW_HEIGHT) * 0.5f)));
	angle = std::atan2(-dY, dX) * 180 / 3.1459f;

	float dist = glm::length(vec2(dX, dY));

	if(dist > 10.0f)
	{
		move(dt);
	}
	else 
	{
		velocity = vec3(0, 0, 0);
	}
}

void Player::die()
{
	int debrisCount = 8;
	for(int i = 0; i < debrisCount; i++)
	{
		createDebris(position, shapeScale * 0.25f, angle + 360 / debrisCount * i, 0, 1, 0);
	}
	alive = false;
}

void Player::reset()
{
	position = vec3(0, 0, 0);
	velocity = vec3(0, 0, 0);
	angle = 90.0f;
	alive = true;
}