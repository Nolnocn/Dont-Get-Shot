#include "Game.h"
#include "GameHelpers.h"

Game* game;

void update();
void draw();
void mousePositionRoutine(int x, int y);
void mouseClickRoutine(int button, int state, int x, int y);

int main(int argc, char** argv) 
{
	srand((unsigned int)time(0));

	game = new Game();

	// Create the window
	glewExperimental = GL_TRUE;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitWindowSize((int)(glutGet(GLUT_SCREEN_WIDTH) * 0.90f), (int)(glutGet(GLUT_SCREEN_HEIGHT) * 0.90f));
	//glutInitWindowSize(700, 500);
	glutCreateWindow("Don't Get Shot");

	// Make sure Glew initialized
	if(glewInit() != GLEW_OK) { return -1; } 

	// Call update() when the main loop is idle 
	glutIdleFunc(update);

	// Call draw() to redisplay the window 
	glutDisplayFunc(draw);

	glutMouseFunc(mouseClickRoutine);
	glutPassiveMotionFunc(mousePositionRoutine);

	// Intialize and loop
	game->init();
	glutMainLoop();
}

void update()
{
	game->update();
}

void draw()
{
	game->draw();
}

void mousePositionRoutine(int x, int y)
{
	game-> mousePositionRoutine(x, y);
}

void mouseClickRoutine(int button, int state, int x, int y)
{
	game->mouseClickRoutine(button, state, x, y);
}

vec3 getMousePosition()
{
	return game->getMousePosition();
}

void createBullet(vec3 position_, float rotation_)
{
	game->createBullet(position_, rotation_);
}

void createHomingBullet(vec3 position_, float rotation_)
{
	game->createHomingBullet(position_, rotation_);
}

void createDebris(vec3 position_, vec3 scale_, float rotation_, float red, float green, float blue)
{
	game->createDebris(position_, scale_, rotation_, red, green, blue);
}

void addToScore(int amt)
{
	game->addToScore(amt);
}