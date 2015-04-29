vec4 lm_fragColor();

void main() {
	vec4 c = lm_fragColor();
	vec4 p = gl_FragCoord;
	vec2 L = vec2(2560.0 / 2.0, 1400.0);
	if (p.y < L.y)
	{
		if (p.x > L.x - (L.y - p.y) * tan(0.5235)
			&& p.x < L.x + (L.y - p.y) * tan(0.5235))
		{
			vec4 ll = vec4(1.0, 1.0, 1.0, c.a);
			vec4 cc = mix(c, ll, 0.4);
			c = cc;
		}
	}
	gl_FragColor = c;
}
