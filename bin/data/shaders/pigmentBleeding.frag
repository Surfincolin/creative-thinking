#version 330

uniform sampler2D tex0;
uniform sampler2D noise;
uniform sampler2D water;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

void main (void){
  vec2 uv = gl_FragCoord.xy / resolution;
  vec2 pw = 1. / resolution;
  
	vec4 noiseTex = texture(noise, uv);
	vec2 bleedVec = -(noiseTex.xy - 0.5) * 2.0;
	vec4 waterTex = texture(water, uv);
	vec4 pigTex0 = texture(tex0, uv);
	vec4 pigTex1 = texture(tex0, uv + vec2(-1.0, 0.5) * pw);
	vec4 pigTex2 = texture(tex0, uv + vec2(-0.5, -1.0) * pw);
	vec4 pigTex3 = texture(tex0, uv + vec2(1.0, -0.5) * pw);
	vec4 pigTex4 = texture(tex0, uv + vec2(0.5, 1.0) * pw);

	vec4 texOut = texture(tex0, uv + bleedVec * pw); // out
	vec4 texIn = texture(tex0, uv - bleedVec * pw); // in

	float avePigment = (pigTex0.r + pigTex1.r + pigTex2.r +pigTex3.r + pigTex4.r) / 5.0;

	float waterFl = waterTex.r;
	float waterFi = waterTex.g;
	float pigment = pigTex0.r;

	//blur
	pigment = mix(pigment, avePigment, 0.13);

	//flow
	float flow = 0.5 * waterFl;
	pigment = min(1.0, pigment + min(flow, texIn.r) * length(bleedVec));
	pigment = max(0.0, pigment - flow  * length(bleedVec));


	float fix = max(0.0, pigment - waterFi);
	pigment = max(0.0, min(waterFi, pigment));

	outputColor = vec4(pigment, 0.0, fix, 1.0);
}
