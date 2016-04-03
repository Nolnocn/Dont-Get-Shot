#include "GameHelpers.h"
#pragma once

class Entity
{
public:
	Entity(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_);
	virtual ~Entity(void);

	void draw();
	virtual void update(int dt);
	bool isAlive();

	vec3 getPosition();
	vec3 getScale();

protected:
	virtual void move(int dt);
	bool alive;
	Shape* shape;
	float dtScale;
	vec3 position, shapeScale, rotAxis;
	float angle;
	vec3 velocity;
};