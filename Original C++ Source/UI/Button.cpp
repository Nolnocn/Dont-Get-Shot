#include "Button.h"

Button::Button(Shape* box_, Shape* pauseShape_, Shape* playShape_, vec3 position_, vec3 scale_)
{
	box = box_;
	box->setColor(1, 1, 1);

	pauseShape = pauseShape_;
	pauseShape->setColor(0, 0, 0);

	playShape = playShape_;
	playShape->setColor(0, 0, 0);

	position = position_;
	size = scale_;
	rotAxis = vec3(0, 0, 1);
}

Button::~Button(void)
{
	delete box;
	delete pauseShape;
	delete playShape;
}

bool Button::isClicked(float x, float y)
{
	if(x > position.x - size.x * 0.5f && x < position.x + size.x * 0.5f && y > position.y - size.y * 0.5f && y < position.y + size.x * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::draw(bool paused)
{
	box->draw(position, size, rotAxis, 0.0f);
	if(paused)
	{
		playShape->draw(position, size, rotAxis, 0.0f);
	}
	else
	{
		pauseShape->draw(position + vec3(0.2f * size.x, 0, 0), size, rotAxis, 0.0f);
		pauseShape->draw(position - vec3(0.2f * size.x, 0, 0), size, rotAxis, 0.0f);
	}
}
