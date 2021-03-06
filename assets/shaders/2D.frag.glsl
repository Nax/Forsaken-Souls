#version 150

precision lowp float;

in vec2 vTex;
in vec4 vColor;

uniform sampler2D sampler;

out vec4 fragColor;

void main () {
    fragColor = texture(sampler, vTex) * vColor;
}
