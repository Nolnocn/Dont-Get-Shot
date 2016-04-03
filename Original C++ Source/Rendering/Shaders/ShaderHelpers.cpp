#include "ShaderHelpers.h"

using namespace std;

// Loads in a text file
char* loadTextFile(const char* file)
{
	// Open the file in binary
	ifstream input(file, ios::binary);

	// Make sure the file is open
	if(input.is_open())
	{
		// Copy the contents to an array
		input.seekg(0, ios::end);
		int length = (int) input.tellg();
		input.seekg(0, ios::beg);
		char* fileContents = new char[length + 1];
		input.read(fileContents, length);
		input.close();
		fileContents[length] = '\0';

		// Return the array
		return fileContents;
	}
	else
	{
		// Return 0 if the file didn't open
		return 0;
	}
}

// Load a shader by file name
GLuint loadShader(const char* file, GLenum shaderType)
{
	// Read in the text file
	const char* shaderFile = loadTextFile(file);

	// Check that the file was read in
	if(shaderFile == 0)
	{
		// Return an error if it was not
		cout << "Error loading shader file: " << file << endl;
		return 0;
	}

	// Create and compile the shader
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderFile, 0);
	glCompileShader(shader);

	// Delete the no longer needed file contents
	delete[] shaderFile;

	// Get the compile status
	GLint result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

	// Check if the shader compiled
	if(result != 0)
	{
		// Return the shader if it did
		return shader;
	}
	else
	{
		// Print the log if it did not
		GLint logLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		GLchar* log = new GLchar[logLength];
		glGetShaderInfoLog(shader, logLength, 0, log);
		for(int i = 0; i < logLength; i++)
		{
			cout << log[i];
		}
		glDeleteShader(shader);
		delete[] log;
		return 0;
	}
}

// Load the vertes and fragment shaders
GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	// Load the vertex shader from the text file
	GLuint vertResult = loadShader(vertexFile, GL_VERTEX_SHADER);
	if(vertResult == 0)
	{
		// Print an error if it didn't load
		cout << "Failed to load vertex shader" << endl;
		return 0;
	}

	// Load the fragment shader from the text file
	GLuint fragResult = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if(fragResult == 0)
	{
		// Print an error if it didn't load
		cout << "Failed to load fragment shader" << endl;
		return 0;
	}

	// Create the shader program 
	// and attach the vertex and fragment shaders
	GLuint program = glCreateProgram();
	glAttachShader(program, vertResult);
	glAttachShader(program, fragResult);
	glLinkProgram(program);

	// Get the link status of the program
	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	// Check if it linked
	if(result != 0)
	{
		// Return the program if it did
		return program;
	}
	else
	{
		// Print the log if it did not
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		char* log = new char[logLength + 1];
		glGetProgramInfoLog(program, logLength, 0, log);
		for(int i = 0; i < logLength; i++)
		{
			cout << log[i];
		}
		glDeleteProgram(program);
		delete[] log;
		return 0;
	}
	
}

// Set the color of the shader
void setShaderColor(GLuint program, const char* uniform, float red, float green, float blue)
{
	// Get the location of the uniform variable and change it
	GLuint loc = glGetUniformLocation(program, uniform);
	glProgramUniform4f(program, loc, red, green, blue, 1.0f);
}

void setShaderMatrix(GLuint program, const char* uniform, mat4 matrix)
{
	GLuint loc = glGetUniformLocation(program, uniform);
	glProgramUniformMatrix4fv(program, loc, 1, GL_FALSE, &matrix[0][0]);
}