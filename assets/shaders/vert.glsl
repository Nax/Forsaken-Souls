// uniform float width;
// uniform float height;

// varying float w;
// varying float h;

vec4 lm_position();
vec4 lm_texCoord();
vec4 lm_frontColor();

void main() {
	gl_Position = lm_position();
	gl_TexCoord[0] = lm_texCoord();
	gl_FrontColor = lm_frontColor();
	// w = width;
	// h = height;
}
