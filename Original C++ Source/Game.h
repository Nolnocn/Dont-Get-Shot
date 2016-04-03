#include <iostream>
#include <vector>
#include <time.h>
#include "Player.h"
#include "Fighter.h"
#include "Hunter.h"
#include "Stealth.h"
#include "Boomer.h"
#include "HomingBullet.h"
#include "Button.h"
#include "Debris.h"
#pragma once

using namespace std;

class Game
{
public:
	Game(void);
	~Game(void);

	void init();
	void update();
	void draw();
	void mousePositionRoutine(int x, int y);
	void mouseClickRoutine(int button, int state, int x, int y);

	vec3 getMousePosition();
	void createBullet(vec3 position_, float rotation_);
	void createHomingBullet(vec3 position_, float rotation_);
	void createDebris(vec3 position_, vec3 scale, float rotation_, float red, float green, float blue);
	void addToScore(int amt);

private:
	void setupGame();
	void resetGame();
	void gameOver();
	void spawnEnemy(int dt);
	Shape* createShape(int numSides, GLuint shader);
	void deleteBullet(int index);
	void deleteEnemy(int index);
	void deleteDebris(int index);

	bool paused;
	int prevTime;
	int score;
	int startSpawnCap;
	int spawnCap;
	int spawnTime;
	int spawnDelay;

	vec3 mousePosition;
	Player* player;
	vector<Enemy*> enemies;
	vector<Bullet*> bullets;
	vector<Debris*> debris;
	Button* pauseButton;
	
	Shape* playerShape;
	Shape* fighterShape;
	Shape* boomerShape;
	Shape* hunterShape;
	Shape* stealthShape;
	Shape* bulletShape;
	Shape* hBulletShape;
	Shape* debrisShape;
};