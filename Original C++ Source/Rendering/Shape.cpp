#include "Shape.h"

// Create a shape from an array of vertices
Shape::Shape(GLfloat vertices[], int numVertices_, GLuint shaderProg_, GLenum mode_)
{
	// Keep track of important variables
	numVertices = numVertices_;
	shaderProg = shaderProg_;
	mode = mode_;

	// Generate and Bind the Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Generate and bind the Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Set the buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 6, (void*)(sizeof(GL_FLOAT) * 2));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}

// Destructor
Shape::~Shape(void)
{
	// Delete the vao and vbo
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

// Draws the shape
void Shape::draw(vec3 position, vec3 shapeScale, vec3 rotAxis, float angle)
{
	mat4 worldMatrix = translate(position) * rotate(angle, rotAxis) * scale(shapeScale);
	setShaderMatrix(shaderProg, "worldMatrix", worldMatrix);
	setShaderColor(shaderProg, "colorTint", color[0], color[1], color[2]);

	// Bind and draw Vertex Array
	glBindVertexArray(vao);
	glDrawArrays(mode, 0, numVertices);
	glFlush();
}

Shape* Shape::clone()
{
	return new Shape(*this);
}

void Shape::setColor(float red, float green, float blue)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}