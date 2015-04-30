varying vec2 s;

vec4 lm_fragColor();

void main() {
	vec2 point = vec2(s.x / 2.0, s.y / 2.0);
	vec2 d = gl_FragCoord.xy - point.xy;
	float dist = d.x * d.x + d.y * d.y;
	float max = (s.x * s.x + s.y * s.y) / 2.0;
	dist = 5.0 * (dist * dist) / (max * max);
	vec4 c = lm_fragColor();
	vec4 ll = vec4(0.0, 0.0, 0.0, c.a);
	vec4 cc = mix(c, ll, 0.7 * dist);
	gl_FragColor = cc;
}
