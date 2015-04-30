
vec4 lm_fragColor();

void main() {

	float w;
	float h;

	//
	w = 1280.0;
	h = 800.0;
	//

	vec2 point = vec2(w / 2.0, h / 2.0);
	float max = w * w + h * h;
	vec2 d = gl_FragCoord.xy - point.xy;
	float dist = d.x * d.x + d.y * d.y;
	dist = (dist * dist * dist * dist) / (max * max * max * max);
	vec4 c = lm_fragColor();
	vec4 ll = vec4(0.0, 0.0, 0.0, c.a);
	vec4 cc = mix(c, ll, 0.7 * dist);
	gl_FragColor = cc;
}
