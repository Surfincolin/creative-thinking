#version 330

uniform sampler2D tex0;
uniform sampler2D pigment;
uniform float r;
uniform float g;
uniform float b;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

void main (void){
  vec2 uv = gl_FragCoord.xy / resolution;
//  uv = vec2(uv.x, 1.0-uv.y);
  vec2 pw = 2. / resolution;
  
	vec4 tex0color = texture(tex0, uv);
	vec4 pigmentTex = texture(pigment, uv);
	
	float fix = pigmentTex.b;
//  float fix = 0.5;
	vec4 color = vec4(r / 255.0, g / 255.0, b / 255.0, 1.0);
	vec4 mixCol = mix(tex0color, color, fix / 0.3);
	vec4 outCol = min(mixCol, tex0color);
	
	outputColor = vec4(outCol);
//  outputColor = vec4(pigmentTex.b,0,0, 1.);

}
