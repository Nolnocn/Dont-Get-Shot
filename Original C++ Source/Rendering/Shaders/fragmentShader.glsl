#version 330

// Color sent in from C++
uniform vec4 colorTint;

// Color from Vertex Shader
in vec4 colorFromVS;

void main()
{
	// Set the color
	gl_FragColor = colorFromVS * colorTint;
}