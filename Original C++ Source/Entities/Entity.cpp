#include "Entity.h"

Entity::Entity(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_)
{
	alive = true;
	shape = shape_;
	position = position_;
	shapeScale = scale_;
	rotAxis = axis_;
	angle = rotation_;

	velocity = vec3(0, 0, 0);
}

Entity::~Entity(void)
{
}

void Entity:: draw()
{
	shape->draw(position, shapeScale, rotAxis, angle);
}

void Entity::update(int dt){}

void Entity:: move(int dt)
{
	velocity = vec3(std::cos(angle * (3.1459f / 180)), std::sin(angle * (3.1459f / 180)), 0) * (dtScale * dt);
	position.x += velocity.x;
	position.y += velocity.y;
}

bool Entity::isAlive()
{
	return alive;
}

vec3 Entity::getPosition()
{
	return position;
}

vec3 Entity::getScale()
{
	return shapeScale;
}