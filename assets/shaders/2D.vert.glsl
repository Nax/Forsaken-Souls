#version 150

precision lowp float;

in vec3 position;
in vec2 tex;
in vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 vTex;
out vec4 vColor;

void main () {
    gl_Position = projection * view * model * vec4(position, 1.0);
    vTex = tex;
    vColor = color;
}
