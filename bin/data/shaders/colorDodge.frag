#version 330

uniform sampler2D tex0;

uniform sampler2D image;
uniform sampler2D edges;

uniform int fN = 7;
//uniform float alpha = 1.0;
//uniform float beta = 0.0;
uniform float opacity = 1.0;

//int fN = 7;
float alpha = 0.732812524;
float beta = 0.228758186;

in vec2 texCoordVarying;
out vec4 outputColor;

vec2 res = vec2(640.0, 480.0);

float blendSubtract(float base, float blend) {
  return max(base+blend-1.0,0.0);
}

vec3 blendSubtract(vec3 base, vec3 blend) {
  return max(base+blend-vec3(1.0),vec3(0.0));
}

vec3 blendSubtract(vec3 base, vec3 blend, float opacity) {
  return (blendSubtract(base, blend) * opacity + base * (1.0 - opacity));
}

void main() {
  
  vec4 color;
  
  vec4 imageC = texture(image, gl_FragCoord.xy/res);
  
  vec4 edgeC = texture(edges, gl_FragCoord.xy/res);
  
  vec4 mask = texture(tex0, gl_FragCoord.xy/res);
  
  float Y = 0.2989 * mask.r + 0.5870 * mask.g + 0.1140 * mask.b;
//  float iY = 0.2989 * color.r + 0.5870 * color.g + 0.1140 * color.b;
  
//  imageC = (alpha * imageC) + beta;
  Y = clamp((alpha * Y) + beta, 0.0, 0.9999);
  
  vec4 greyBlur = vec4(vec3(Y), 1.0);
  vec4 inverted = vec4(vec3(1.0 - Y), 1.0 );
  
  vec4 ci = vec4(vec3(1.0 - imageC.g),1.0);

  if (fN == 1) {
    color = imageC;
  }
  
  if (fN == 2) {
    color = greyBlur;
  }
  
  if (fN == 3) {
    color = clamp(inverted / imageC, 0.0, 1.1);
  }
  
  if (fN == 4) {
    color = clamp(imageC / inverted, 0.0, 1.1);
  }
  
  if (fN == 5) {
    color = clamp(greyBlur / ci, 0.0, 1.1);
  }
  
  if (fN == 6) {
    color = clamp(ci / greyBlur, 0.0, 1.1);
  }
  
  if (fN == 7) {
    color = clamp(inverted / ci, 0.0, 1.1);
  }
  
  if (fN == 8) {
    color = clamp(ci / inverted, 0.0, 1.1);
  }
  
  if (fN == 9) {
    color = inverted;
  }
  
  if (fN == 0) {
    color = ci;
  }
  
  
  // multiply with opacity
//  color = (color * edgeC) * opacity + color * (1.0 - opacity);
//  color = color * vec4(edgeC.r, edgeC.g, edgeC.b, 0.6);
//  color = edgeC;

  vec3 subtract = blendSubtract(color.rgb, edgeC.rgb, 0.61);
  
  color = vec4(subtract, 1.0);
  
  outputColor = color;
  
}
