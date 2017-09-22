#version 330

uniform sampler2D tex0;
uniform float r;
uniform float g;
uniform float b;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

void main (void){
  vec2 uv = gl_FragCoord.xy / resolution;
//  uv = vec2(uv.x, 1.0-uv.y);
  vec2 pw = 1. / resolution;
  
	vec4 tex0c = texture(tex0, uv);
	
	float pigment = tex0c.r;
	vec4 color = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);
	vec4 outCol = mix(vec4(1.0), color, pigment / 1.5);
	
	outputColor = vec4(outCol);
}
