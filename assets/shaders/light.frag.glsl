#version 150

precision lowp float;

in vec2 vTex;
in vec2 vPosition;

uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	vec4 cc = vec4(1.0, 1.0, 1.0, 1.0);
	vec2 pos = vPosition * vec2(16.0/9.0, 1.0);
	float dist = (pos.x * pos.x + pos.y * pos.y) * 10;

	fragColor = texture(sampler, vTex) + cc * max(1.0 - dist, 0.0);
}
