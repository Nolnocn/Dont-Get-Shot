#include "Game.h"

Game::Game(void)
{
}

Game::~Game(void)
{
	delete player;
	delete pauseButton;

	delete playerShape;
	delete fighterShape;
	delete boomerShape;
	delete hunterShape;
	delete stealthShape;
	delete bulletShape;
	delete hBulletShape;
	delete debrisShape;

	for(int i = bullets.size() - 1; i >= 0; i--)
	{
		deleteBullet(i);
	}

	for(int i = enemies.size() - 1; i >= 0; i--)
	{
		deleteEnemy(i);
	}

	for(int i = debris.size() - 1; i >= 0; i--)
	{
		deleteDebris(i);
	}
}

//###################################################################################################################################
//
//
//
//###################################################################################################################################

void Game::init()
{
	cout << "Initializing" << endl;

	// Loads the shaders
	GLuint shader = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

	// Check that the shader program loaded
	if(shader != 0)
	{
		glUseProgram(shader);
	}
	else
	{
		cout << "Failed to use Program" << endl;
	}

	playerShape = createShape(3, shader);
	fighterShape = createShape(4, shader);
	boomerShape = createShape(8, shader);
	hunterShape = createShape(24, shader);
	stealthShape = createShape(3, shader);
	bulletShape = createShape(3, shader);
	hBulletShape = createShape(3, shader);

	GLfloat boxVerts[36] = 
	{
		//	X		Y		R		G		B		A
			0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.5f,	-0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.5f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
	};

	Shape* buttonBox = new Shape(boxVerts, 36, shader, GL_TRIANGLES);

	GLfloat playVerts[18] = 
	{
		//	X		Y		R		G		B		A
			-0.25f,	0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.25f,	-0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.25f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f,
	};

	Shape* buttonPlayIcon = new Shape(playVerts, 18, shader, GL_TRIANGLES);

	GLfloat pauseVerts[36] = 
	{
		//	X		Y		R		G		B		A
			0.1f,	0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.1f,	-0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.1f,	-0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.1f,	0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.1f,	-0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
			-0.1f,	0.25f,	1.0f,	1.0f,	1.0f,	1.0f,
	};

	Shape* buttonPauseIcon = new Shape(pauseVerts, 36, shader, GL_TRIANGLES);

	GLfloat debrisVerts[18] = 
	{
		//	X		Y		R		G		B		A
			-0.0f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.5f,	0.0f,	1.0f,	1.0f,	1.0f,	1.0f,
			0.0f,	0.5f,	1.0f,	1.0f,	1.0f,	1.0f,
	};

	debrisShape = new Shape(debrisVerts, 18, shader, GL_TRIANGLES);

	float ratio = (float)(glutGet(GLUT_WINDOW_HEIGHT)) / (float)(glutGet(GLUT_WINDOW_WIDTH));
	pauseButton = new Button(buttonBox, buttonPauseIcon, buttonPlayIcon, vec3(0.85f, 0.85f, 0), vec3(0.1f * ratio, 0.1f, 1));

	setupGame();

	// Set the background color
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::update()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	int dt = currentTime - prevTime; 
	prevTime = currentTime;

	if(!paused)
	{
		//cout << "Updating" << endl;

		if(player->isAlive())
		{
			player->update(dt);

			int enemyCount = enemies.size(); // signed/unsigned mismatch fix
			if(enemyCount < spawnCap)
			{
				spawnEnemy(dt);
			}
		}

		for(int i = bullets.size() - 1; i >= 0; i--)
		{
			bullets[i]->update(dt);

			if(bullets[i]->checkOffScreen())
			{
				deleteBullet(i);
				break;
			}

			if(player->isAlive() && bullets[i]->detectCollision(player))
			{
				deleteBullet(i);
				gameOver();
				break;
			}

			for(int j = enemies.size() - 1; j >= 0; j--)
			{
				if(bullets[i]->detectCollision(enemies[j]))
				{
					deleteEnemy(j);
					deleteBullet(i);
					break;
				}
			}
		}

		for(int i = enemies.size() - 1; i >= 0; i--)
		{
			enemies[i]->update(dt);

			if(!enemies[i]->isAlive())
			{
				deleteEnemy(i);
			}
		}

		for(int i = debris.size() - 1; i >= 0; i--)
		{
			debris[i]->update(dt);

			if(!debris[i]->isAlive())
			{
				deleteDebris(i);
			}
		}
	}

	// Redisplay everything on screen
	glutSwapBuffers();
	glutPostRedisplay();
}

void Game::draw()
{
	//cout << "Drawing" << endl;
	glClear(GL_COLOR_BUFFER_BIT);
	
	for(int i = debris.size() - 1; i >= 0; i--)
	{
		debris[i]->draw();
	}

	for(int i = bullets.size() - 1; i >= 0; i--)
	{
		bullets[i]->draw();
	}

	for(int i = enemies.size() - 1; i >= 0; i--)
	{
		enemies[i]->draw();
	}

	if(player->isAlive())
		player->draw();

	pauseButton->draw(paused || !player->isAlive());
}

//###################################################################################################################################
//
//
//
//###################################################################################################################################

void Game::mousePositionRoutine(int x, int y)
{
	mousePosition = vec3(x, y, 0);
}

void Game::mouseClickRoutine(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		float xPos = ((float)x / glutGet(GLUT_WINDOW_WIDTH)) * 2 - 1;
		float yPos = ((float)y / glutGet(GLUT_WINDOW_HEIGHT)) * 2 - 1;
		yPos *= -1;

		if(pauseButton->isClicked(xPos, yPos))
		{
			if(player->isAlive())
			{
				paused = !paused;
			}
			else
			{
				resetGame();
			}
		}
	}
}

//###################################################################################################################################
//
//
//
//###################################################################################################################################

void Game::setupGame()
{
	paused = true;
	score = 0;
	spawnTime = 0;
	spawnDelay = 1000;
	startSpawnCap = 3;
	spawnCap = startSpawnCap;

	player = new Player(playerShape, vec3(0,0,0), vec3(0.1f, 0.05f, 1.0f), vec3(0, 0, 1), 90.0f);
}

Shape* Game::createShape(int numSides, GLuint shader)
{
	int numComponents = (numSides + 2) * 6;
	float angle = (2 * 3.1459f) / numSides;
	float radius = 0.5f;
	GLfloat* verts = new GLfloat[numComponents];

	// First vertex is the center
	verts[0] = 0.0f;
	verts[1] = 0.0f;
	verts[2] = 1.0f;
	verts[3] = 1.0f;
	verts[4] = 1.0f;
	verts[5] = 1.0f;

	// Outer points
	for(int i = 0; i < numSides; i++)
	{
		verts[(i + 1) * 6] = radius * cos(angle * i);
		verts[(i + 1) * 6 + 1] = radius * sin(angle * i);
		verts[(i + 1) * 6 + 2] = 1.0f;
		verts[(i + 1) * 6 + 3] = 1.0f;
		verts[(i + 1) * 6 + 4] = 1.0f;
		verts[(i + 1) * 6 + 5] = 1.0f;
	}

	// Lazy way to close the shape
	verts[numComponents - 6] = radius * std::cos(0.0f);
	verts[numComponents - 5] = radius * std::sin(0.0f);
	verts[numComponents - 4] = 1.0f;
	verts[numComponents - 3] = 1.0f;
	verts[numComponents - 2] = 1.0f;
	verts[numComponents - 1] = 1.0f;

	Shape* shape = new Shape(verts, numComponents, shader, GL_TRIANGLE_FAN);
	delete[] verts;
	return shape;
}

void Game::resetGame()
{
	for(int i = bullets.size() - 1; i >= 0; i--)
	{
		deleteBullet(i);
	}

	for(int i = enemies.size() - 1; i >= 0; i--)
	{
		deleteEnemy(i);
	}

	for(int i = debris.size() - 1; i >= 0; i--)
	{
		deleteDebris(i);
	}

	score = 0;
	spawnCap = startSpawnCap;

	player->reset();
}

void Game::gameOver()
{
	player->die();

	for(int i = enemies.size() - 1; i >= 0; i--)
	{
		enemies[i]->leave();
	}
}

void Game::spawnEnemy(int dt)
{
	if(spawnTime > spawnDelay)
	{
		int num = rand() % 4;
		vec3 position = vec3(0, 0, 0);

		if(num == 0)
		{
			position = vec3((float)((rand() % 25 + 1) * 0.1f) - 1.25f, 1.25f,0);
		}
		else if(num == 2)
		{
			position = vec3(1.25f, (float)((rand() % 25 + 1) * 0.1f) - 1.25f,0);
		}
		else if(num == 3)
		{
			 position = vec3((float)((rand() % 25 + 1) * 0.1f) - 1.25f, -1.25f,0);
		}
		else
		{
			position = vec3(-1.25f, (float)((rand() % 25 + 1) * 0.1f) - 1.25f,0);
		}

		num = rand() % 100;

		if(num < 10)
		{
			Stealth* stealth = new Stealth(stealthShape, position, vec3(0.1f, 0.05f, 1.0f), vec3(0, 0, 1), 0.0f, player);
			enemies.push_back(stealth);
		}
		else if(num < 25)
		{
			Boomer* boomer = new Boomer(boomerShape, position, vec3(0.05f, 0.05f, 1.0f), vec3(0, 0, 1), 0.0f, player);
			enemies.push_back(boomer);
		}
		else if(num < 50)
		{
			Hunter* hunter = new Hunter(hunterShape, position, vec3(0.1f, 0.1f, 1.0f), vec3(0, 0, 1), 0.0f, player);
			enemies.push_back(hunter);
		}
		else
		{
			Fighter* fighter = new Fighter(fighterShape, position, vec3(0.1f, 0.1f, 1.0f), vec3(0, 0, 1), 0.0f, player);
			enemies.push_back(fighter);
		}

		spawnTime = 0;
	}
	else
	{
		spawnTime += dt;
	}
}

//###################################################################################################################################
//
//
//
//###################################################################################################################################

vec3 Game::getMousePosition()
{
	return mousePosition;
}

void Game::createBullet(vec3 position_, float rotation_)
{
	Bullet* bullet = new Bullet(bulletShape, position_, vec3(0.05f, 0.025f, 1.0f), vec3(0, 0, 1), rotation_);
	bullets.push_back(bullet);
}

void Game::createHomingBullet(vec3 position_, float rotation_)
{
	HomingBullet* bullet = new HomingBullet(hBulletShape, position_, vec3(0.05f, 0.025f, 1.0f), vec3(0, 0, 1), rotation_, player);
	bullets.push_back(bullet);
}

void Game::createDebris(vec3 position_, vec3 scale_, float rotation_, float red, float green, float blue)
{
	Debris* debbie = new Debris(debrisShape, position_, scale_, vec3(0, 0, 1), rotation_, red, green, blue);
	debris.push_back(debbie);
}

void Game::deleteBullet(int index)
{
	delete bullets[index];
	bullets.erase(bullets.begin() + index);
}

void Game::deleteEnemy(int index)
{
	delete enemies[index];
	enemies.erase(enemies.begin() + index);
}

void Game::deleteDebris(int index)
{
	delete debris[index];
	debris.erase(debris.begin() + index);
}

void Game::addToScore(int amt)
{
	score += amt;
	spawnCap = startSpawnCap + score / 100;
}