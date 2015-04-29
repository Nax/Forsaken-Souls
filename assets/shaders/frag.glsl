vec4 lm_fragColor();

void main() {
	vec2 point = vec2(2560.0 / 2.0, 1400.0 / 2.0);
	vec2 d = gl_FragCoord.xy - point.xy;
	float dist = sqrt(d.x * d.x + d.y * d.y);
	dist = (dist * dist * dist * dist) / (1458.0 * 1458.0 * 1458.0 * 1458.0);
	vec4 c = lm_fragColor();
	vec4 ll = vec4(0.0, 0.0, 0.0, c.a);
	vec4 cc = mix(c, ll, 0.7 * dist);
	gl_FragColor = cc;
}
