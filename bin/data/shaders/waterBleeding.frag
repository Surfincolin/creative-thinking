#version 330

uniform sampler2D tex0;
uniform sampler2D noise;
uniform sampler2D water;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

void main (void){
  vec2 uv = gl_FragCoord.xy / resolution;
  vec2 pw = 1./resolution;
  
	vec4 noiseTex = texture(noise, uv);

	float scroll = -0.0;

	vec4 tex0c = texture(tex0, uv + vec2(0.0, scroll) * pw);
	vec2 bleedVec = -(noiseTex.xy - 0.5) * 1.0;
	vec4 tex1 = texture(tex0, uv + vec2(-1.0, 0.5 + scroll) * pw );
	vec4 tex2 = texture(tex0, uv + vec2(-0.5, -1.0 + scroll) * pw);
	vec4 tex3 = texture(tex0, uv + vec2(1.0, -0.5 + scroll) * pw);
	vec4 tex4 = texture(tex0, uv + vec2(0.5, 1.0 + scroll) * pw);

	vec4 texOut = texture(tex0, uv + bleedVec * pw); // out
	vec4 texIn = texture(tex0, uv - bleedVec * pw); // in

	float minFl = min(min(min(tex1.r, tex2.r), tex3.r), tex4.r);

	//blur
	float aveFl = (tex0c.r + tex1.r + tex2.r + tex3.r + tex4.r) / 5.0;
	float aveFi = (tex0c.g + tex1.g + tex2.g + tex3.r + tex4.g) / 5.0;

	float fl = tex0c.r;
	float fi = tex0c.g;

	fl = mix(fl, aveFl, 0.8);
	fi = mix(fi, aveFi, 0.02);

	//flow
	float flow = 0.21;
	fl = min(1.0, fl + min(flow, texIn.r) * length(bleedVec));
	fl = max(0.0, fl - flow  * length(bleedVec));

	// dry
	fl = max(0.0, fl - ((minFl == 0.0) ? 0.005   : 0.003));
	fi = max(0.0, fi - ((fl == 0.0) ? 0.001  : -fl * 0.002));

	outputColor = vec4(fl, fi ,0.0, 1.0);

}
