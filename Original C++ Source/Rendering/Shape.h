#include <GL\glew.h> 
#include <GL\freeglut.h>
#include "ShaderHelpers.h"
#pragma once

class Shape
{
public:
	Shape(GLfloat vertices[], int numVertices_, GLuint shaderProg_, GLenum mode_);
	~Shape(void);
	void draw(vec3 position, vec3 shapeScale, vec3 rotAxis, float angle);
	void setColor(float red, float green, float blue);
	Shape* clone();

private:
	// Important OpenGL indices
	GLuint vbo;
	GLuint vao;
	GLuint shaderProg;

	// Draw mode
	GLenum mode;

	// Keep track of the number of vertices
	int numVertices;
	float color[3];
};

