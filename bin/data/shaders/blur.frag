#version 330

uniform sampler2D tex;
uniform sampler2D water;
uniform sampler2D noise;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

void main (void){
  vec2 uv = gl_FragCoord.xy / resolution;
//  uv = vec2(uv.x, 1.0-uv.y);
  vec2 pw = 2. / resolution;
  
	vec4 noiseTex = texture(noise, uv);
	vec4 waterTex = texture(water, uv);
	float scroll = (waterTex.r * noiseTex.b * - 1.0) * 0.8;
	vec4 tex0 = texture(tex, uv + vec2(0.0, scroll) * pw);
	vec4 tex1 = texture(tex, uv + vec2(-1.0, 0.5 + scroll) * pw);
	vec4 tex2 = texture(tex, uv + vec2(-0.5, -1.0 + scroll) * pw);
	vec4 tex3 = texture(tex, uv + vec2(1.0, -0.5 + scroll) * pw);
	vec4 tex4 = texture(tex, uv + vec2(0.5, 1.0 + scroll) * pw);

	vec4 ave = (tex1 + tex2 + tex3 + tex4) / 4.0;
	vec4 mixCol = mix(tex0, ave, min(0.8, waterTex.r *3.0));
	mixCol = min(vec4(1.0), mixCol +vec4(0.004));

	vec4 outCol = min(mixCol, tex0);

	outputColor = outCol;

}
