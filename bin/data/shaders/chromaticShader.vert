#version 330

uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;
in vec4 color;

out vec2 texCoordVarying; 
out vec4 vertColor;

void main() {
	// texCoordVarying = vec2(texcoord.x, texcoord.y);
	texCoordVarying = texcoord;
	gl_Position = modelViewProjectionMatrix * position;

	vertColor = color;
}