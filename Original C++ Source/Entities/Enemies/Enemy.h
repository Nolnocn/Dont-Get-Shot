#include "Player.h"
#pragma once

class Enemy :
	public Entity
{
public:
	Enemy(Shape* shape_, vec3 position_, vec3 scale_, vec3 axis_, float rotation_, Player* player_);
	virtual ~Enemy(void);

	virtual void update(int dt);
	void leave();

protected:
	void rotateToPlayer();
	bool onScreen();
	virtual void fire();

	Player* player;
	int fireDelay;
	int fireTime;
	int scoreValue;
};