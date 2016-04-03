#include "Shape.h"
#pragma once

vec3 getMousePosition();
void createBullet(vec3 position_, float rotation_);
void createHomingBullet(vec3 position_, float rotation_);
void createDebris(vec3 position_, vec3 scale, float rotation_, float red, float green, float blue);
void addToScore(int amt);