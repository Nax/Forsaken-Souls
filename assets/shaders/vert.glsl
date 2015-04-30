uniform vec2 size;
varying vec2 s;

vec4 lm_position();
vec4 lm_texCoord();
vec4 lm_frontColor();

void main() {
	gl_Position = lm_position();
	gl_TexCoord[0] = lm_texCoord();
	gl_FrontColor = lm_frontColor();
	s = size;
}
