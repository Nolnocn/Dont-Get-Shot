#include <GL\glew.h> 
#include <GL\freeglut.h>
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#pragma once

using namespace glm;

// Method declarations
char* loadTextFile(const char* file);
GLuint loadShader(const char* file, GLenum shaderType);
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);
void setShaderColor(GLuint program, const char* uniform, float red, float green, float blue);
void setShaderMatrix(GLuint shader, const char* variable, mat4 matrix);