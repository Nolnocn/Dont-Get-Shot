#include "Entity.h"
#pragma once

class Debris :
	public Entity
{
public:
	Debris(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, float red, float green, float blue);
	~Debris(void);

	void update(int dt);

private:
	void move(int dt);
	void spin(int dt);

	float dir;
	float spinAmt;
	int lifeTime;
	int currTime;
};

