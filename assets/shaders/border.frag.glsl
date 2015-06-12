#version 150

precision lowp float;

in vec2 vTex;
in vec2 vPosition;

uniform sampler2D sampler;

out vec4 fragColor;

void main() {
	vec4 cc = vec4(0.0, 0.0, 0.0, 1.0);
	float dist = vPosition.x * vPosition.x + vPosition.y * vPosition.y;
	dist = dist * 0.5;

	fragColor = mix(cc, texture(sampler, vTex), 1.0 - dist);
}
