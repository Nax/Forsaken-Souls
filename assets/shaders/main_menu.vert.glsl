#version 150

in vec2 position;
in vec2 tex;
in vec4 color;

uniform mat4 projection;

out vec2 vTex;
out vec4 vColor;

void main () {
    gl_Position = projection * vec4(position, 0.0, 1.0);
    vTex = tex;
    vColor = color;
}
