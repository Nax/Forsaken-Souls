varying vec2 s;
varying float lCount;
varying vec2 l[16];
varying vec2 offset;

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

	int i = 0;
	int count = int(lCount);
	c = cc;
	max = s.x / 6.0;
	vec2 light;
	while (i < count)
	{
		light.x = (l[i].x - offset.x) * ((s.x * 64.0) / 1920.0);
        light.y = (l[i].y - offset.y) * ((s.y * 64.0) / 1080.0);
		d = gl_FragCoord.xy - light.xy;
		dist = sqrt(d.x * d.x + d.y * d.y);
		if (dist < max)
		{
			c.r = min(c.r + (1.0 - (dist / max)) * 0.5, 1.0);
			c.g = min(c.g + (1.0 - (dist / max)) * 0.5, 1.0);
			c.b = min(c.b + (1.0 - (dist / max)) * 0.5, 0.6);
		}
		i++;
	}

	cc = c;
	gl_FragColor = cc;
}
