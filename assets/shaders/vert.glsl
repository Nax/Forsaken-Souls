uniform vec2 size;
uniform int lightCount;
uniform vec2 lights[16];
uniform vec2 off;

varying vec2 s;
varying float lCount;
varying vec2 l[16];
varying vec2 offset;

vec4 lm_position();
vec4 lm_texCoord();
vec4 lm_frontColor();

void main() {
	gl_Position = lm_position();
	gl_TexCoord[0] = lm_texCoord();
	gl_FrontColor = lm_frontColor();
	s = size;
	lCount = float(lightCount);
	offset = off;
	int i = 0;
	while (i < lightCount)
	{
		l[i] = lights[i];
		i++;
	}
}
