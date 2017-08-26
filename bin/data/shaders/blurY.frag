#version 330

uniform sampler2D tex0;
uniform float blurAmount;

in vec2 texCoordVarying;
out vec4 outputColor;

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

uniform vec2 resolution = vec2(640.0,480.0);

void main() {
  
//  vec4 col = texture(tex0, vec2(0.5,0.5));
//  if (col.r > 0.0) {
//    //red
//    outputColor = vec4(1.0,0,0,1.0);
//  } else {
//    //green
//    outputColor = vec4(0,1.0,0,1.0);
//  }
//  return;
  
//  outputColor = texture(tex0, gl_FragCoord.xy/resolution);
//  return;
  
  vec4 color;
  
  color = texture(tex0, gl_FragCoord.xy/resolution) * weight[0];
  
  for (int i = 1; i < 3; i++) {

    color += texture(tex0, (gl_FragCoord.xy + vec2(0.0, offset[i])) / resolution ) * weight[i];
    color += texture(tex0, (gl_FragCoord.xy - vec2(0.0, offset[i])) / resolution ) * weight[i];

  }
  
  outputColor = color;
  
}
