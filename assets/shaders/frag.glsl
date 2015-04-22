varying vec4 fpos;

vec4 lm_fragColor();

void main() {
	vec2 point = vec2(2560.0 / 2.0, 1400.0 / 2.0);
	vec2 d = gl_FragCoord.xy - point.xy;
	float dist = sqrt(d.x * d.x + d.y * d.y);
	vec4 c = lm_fragColor();
	float l = 0.2126 * c.r + 0.7152 * c.g + 0.0722 * c.b;
	vec4 ll = vec4(l, l, l, c.a);
	vec4 cc = mix(c, ll, dist / 1000.0);
	gl_FragColor = cc;

}
