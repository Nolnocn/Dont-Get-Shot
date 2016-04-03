#include "GameHelpers.h"
#pragma once

class Button
{
public:
	Button(Shape* box, Shape* pauseShape_, Shape* playShape_, vec3 position_, vec3 scale_);
	~Button(void);

	bool isClicked(float x, float y);
	void draw(bool paused);

private:
	Shape* box;
	Shape* pauseShape;
	Shape* playShape;
	vec3 position, size, rotAxis;
};

