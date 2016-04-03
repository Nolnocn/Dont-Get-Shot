#include "Entity.h"
#pragma once

class Player :
	public Entity
{
public:
	Player(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_);
	~Player(void);

	void update(int dt);
	void die();
	void reset();

private:
	//void rotateToMouse();
	void moveToMouse(int dt);
};