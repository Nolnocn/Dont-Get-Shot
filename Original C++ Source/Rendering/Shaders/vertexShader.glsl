#version 330

// Vertex info Coming in
in vec2 position;
in vec4 color;

uniform mat4 worldMatrix;

// Color info to be sent to fragment shader
out vec4 colorFromVS;

void main()
{
	gl_Position = worldMatrix * vec4(position, 0, 1);
	colorFromVS = color;
}