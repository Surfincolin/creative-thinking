#version 330

uniform sampler2D tex0;

uniform sampler2D image;
uniform sampler2D edges;

uniform int fN = 7;
//uniform float alpha = 1.0;
//uniform float beta = 0.0;
uniform float opacity = 1.0;

//int fN = 7;
float contrast = 0.732812524;
float brightness = 0.228758186;

in vec2 texCoordVarying;
out vec4 outputColor;

vec2 res = vec2(1280.0, 720.0);

#define NoiseAmount 0.005
#define ErrorPeriod 15.0
#define ErrorRange 0.003


float random (in vec2 st) {
  return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

// Based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
  vec2 i = floor(st);
  vec2 f = fract(st);
  
  // Four corners in 2D of a tile
  float a = random(i);
  float b = random(i + vec2(1.0, 0.0));
  float c = random(i + vec2(0.0, 1.0));
  float d = random(i + vec2(1.0, 1.0));
  
  vec2 u = f * f * (3.0 - 2.0 * f);
  
  return mix(a, b, u.x) +
  (c - a)* u.y * (1.0 - u.x) +
  (d - b) * u.x * u.y;
}

#define OCTAVES 6
float fbm (in vec2 st) {
  // Initial values
  float value = 0.0;
  float amplitud = .5;
  float frequency = 0.;
  //
  // Loop of octaves
  for (int i = 0; i < OCTAVES; i++) {
    value += amplitud * noise(st);
    st *= 2.;
    amplitud *= .5;
  }
  return value;
}

vec4 adjustBrightnessContrast(vec4 colorIn) {
  
  vec3 contrasted = colorIn.rgb * contrast;
  vec3 bright = clamp(contrasted + vec3(brightness), 0.0, 0.9999);
  
  return vec4(bright, colorIn.a);
}

// 0.21 R + 0.72 G + 0.07 B.
const vec3 grayConst = vec3(0.2126, 0.7252, 0.0722);
const vec3 PSgrayConst = vec3(0.2989, 0.5870, 0.1140);

vec4 grayScale(vec4 colorIn) {
  float gray = dot(colorIn.rgb, grayConst);
  
  return vec4(vec3(gray), colorIn.a);
}

vec4 invertColor(vec4 colorIn) {
  vec3 expProtection = clamp(colorIn.rgb, 0.01, 0.99);
  return vec4(vec3(1.0) - expProtection.rgb, colorIn.a );
}

float blendSubtract(float base, float blend) {
  return max(base+blend-1.0,0.0);
}

vec3 blendSubtract(vec3 base, vec3 blend) {
  return max(base+blend-vec3(1.0),vec3(0.0));
}

vec3 blendSubtract(vec3 base, vec3 blend, float opacity) {
  return (blendSubtract(base, blend) * opacity + base * (1.0 - opacity));
}

void distortPos(vec2 uv, inout vec2 uvs[3]) {
  vec2 st = uv;
  
  float col = 0.0;
  st.x *=  res.x/res.y;
  col += fbm(st*1) * 2.0 - 1.;
  //col.y = fbm(st.yx*3) * 2.0 - 1.;
  //col.z = 0.0;
  
  
  float noise = (col - 0.5) * NoiseAmount;
//  float noise = random(st) * NoiseAmount;
  //  float noise = (col.x - 0.5) * distortion;
  uvs[0] = uv + vec2(ErrorRange * sin(ErrorPeriod * uv.y + 0.0) + noise, ErrorRange * sin(ErrorPeriod * uv.x + 0.0) + noise);
  uvs[1] = uv + vec2(ErrorRange * sin(ErrorPeriod * uv.y + 1.047) + noise, ErrorRange * sin(ErrorPeriod * uv.x + 1.142) + noise);
  uvs[2] = uv + vec2(ErrorRange * sin(ErrorPeriod * uv.y + 2.094) + noise, ErrorRange * sin(ErrorPeriod * uv.x + 1.571) + noise);
  
}

void main() {
  
  vec4 color = vec4(0,0,0,1);
  
  vec2 uv = gl_FragCoord.xy/res;
  
  vec2[3] uvs;
  
  distortPos(uv, uvs);
  
  vec4 imageC = texture(image, uv);
  
  vec4 edgeC = texture(edges, uv);
//  vec4 edgeC2 = texture(edges, uvs[0]);
//  vec4 edgeC3 = texture(edges, uvs[2]);
  
  vec4 mask = texture(tex0, uv);
  
  vec4 mskgry = grayScale(mask); // Y
  
  vec4 greyBlur = adjustBrightnessContrast(mskgry);
  
  vec4 inverted = invertColor(greyBlur);
  
  vec4 grayColor = grayScale(imageC);
  vec4 ci = invertColor(grayColor);
  
//  outputColor= edgeC;
//  return;

  if (fN == 1) {
    color = imageC;
  }
  
  if (fN == 2) {
    color = greyBlur;
  }
  
  if (fN == 3) {
    color = clamp(inverted / imageC, 0.0, 1.0);
  }
  
  if (fN == 4) {
    color = clamp(imageC / inverted, 0.0, 1.0);
  }
  
  if (fN == 5) {
    color = clamp(greyBlur / ci, 0.0, 1.0);
  }
  
  if (fN == 6) {
    color = clamp(ci / greyBlur, 0.0, 1.0);
  }
  
  if (fN == 7) {
    color = clamp(inverted / ci, 0.0, 1.0);
  }
  
  if (fN == 8) {
    color = clamp(ci / inverted, 0.0, 1.0);
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

  vec4 edgeI = invertColor(edgeC);
  vec3 subtract = blendSubtract(color.rgb, edgeI.rgb, 0.51);
  
//  edgeC2 = invertColor(edgeC2);
//  edgeC3 = invertColor(edgeC3);
//  subtract = blendSubtract(subtract.rgb, edgeC2.rgb, 0.51);
//  subtract = blendSubtract(subtract.rgb, edgeC3.rgb, 0.51);
  
  color = vec4(subtract, 1.0);
  
  color.rgb = mix(subtract, imageC.rgb, 0.35);
  
  outputColor = color;
  
}
