#version 150

in vec2 position;
in vec2 tex;

out vec2 vPosition;
out vec2 vTex;

void main () {
	gl_Position = vec4(position, 0.0, 1.0);
	vTex = tex;
	vPosition = position;
}