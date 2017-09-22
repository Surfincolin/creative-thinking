#version 330

uniform sampler2D tex0;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0, 720.0);

//uniform float waterOn = 1;

void main (void){
  
  vec2 uv = gl_FragCoord.xy / resolution;
  uv = vec2(uv.x, 1.0-uv.y);
  
  vec2 pw = 1.0 / resolution;
  
	vec4 tex0c = texture(tex0, uv);


	vec4 tex1 = texture(tex0, uv + vec2(-1.0, 0.5) * pw );
	vec4 tex2 = texture(tex0, uv + vec2(-0.5, -1.0) * pw );
	vec4 tex3 = texture(tex0, uv + vec2(1.0, -0.5) * pw );
	vec4 tex4 = texture(tex0, uv + vec2(0.5, 1.0) * pw );

	float dx = tex0c.r - tex1.r * -1.0 + tex2.r * -0.5 + tex3.r * 1.0 + tex4.r * 0.5;
	float dy = tex0c.r - tex1.r * 0.5 + tex2.r * -1.0 + tex3.r * -0.5 + tex4.r * 1.0;
	vec3 normal = vec3(dx, dy, 1.0);
	normal = normalize(normal);

	float a = min(0.1, tex0c.g);
	a += tex0c.r *0.5;
	float lev = 1.0 - a;



	vec3 lightDir = vec3(0.0, 1.5,1.0);
	vec4 ambientColor = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 diffuseColor = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 specularColor = vec4(1.0, 1.0, 1.0, 1.0);

	float diffuse = max(0.0, dot(normalize(normal), normalize(lightDir)));
	vec4 flagColor = diffuse * diffuseColor;
	flagColor += ambientColor;
	vec3 vReflection = normalize(reflect(-normalize(lightDir), normalize(normal)));
	float specular = pow(max(0.0, dot(normalize(normal), vReflection)), 128.0);
	flagColor += specular * specularColor;

	lev = mix(max(flagColor.r, lev), flagColor.r, 0.2); ;
	lev = 1.0 - (1.0 - lev) * 0.6;

	outputColor = vec4(lev, lev, lev, 1.0);
//  outputColor = vec4(tex0c.r,0,0,1.);
//  if (lev > 0.9) {
//    outputColor = vec4(0, 1., 0, 1.0);
//  }
}
