vec4 lm_position();
vec4 lm_texCoord();
vec4 lm_frontColor();

varying vec4 fpos;

void main() {
	fpos = lm_position();
	gl_Position = fpos;
	gl_TexCoord[0] = lm_texCoord();
	gl_FrontColor = lm_frontColor();
}
