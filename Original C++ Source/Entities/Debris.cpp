#include "Debris.h"

Debris::Debris(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, float red, float green, float blue)
	:Entity(shape_, position_, scale_, axis_, rotation_)
{
	//shape = shape_->clone();
	shape->setColor(red, green, blue);
	spinAmt = rand() % 100 * .1f;
	dir = rotation_;
	dtScale = 0.0001f * ((rand() % 4) + 1);
	lifeTime = 750;
	currTime = 0;
}

Debris::~Debris(void)
{
	//delete shape;
}

void Debris::update(int dt)
{
	move(dt);
	spin(dt);

	if(currTime > lifeTime)
	{
		alive = false;
	}
	else
	{
		currTime += dt;
	}
}

void Debris::move(int dt)
{
	velocity = vec3(std::cos(dir * (3.1459f / 180)), std::sin(dir * (3.1459f / 180)), 0) * (dtScale * dt);
	position.x += velocity.x;
	position.y += velocity.y;
}

void Debris::spin(int dt)
{
	angle += spinAmt;
}