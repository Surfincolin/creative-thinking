#version 330

uniform sampler2D tex0;

in vec2 texCoordVarying;
out vec4 outputColor;

uniform vec2 resolution = vec2(1280.0,720.0);

void main() {
  
  vec4 color = vec4(0,0,0,0);
  
  vec2 offset = vec2(1.0,0.0);
  

  color = texture(tex0, gl_FragCoord.xy/resolution);

  vec4 r = texture(tex0, (gl_FragCoord.xy + offset.xy )/resolution);
  vec4 l = texture(tex0, (gl_FragCoord.xy - offset.xy )/resolution);
  vec4 t = texture(tex0, (gl_FragCoord.xy + offset.yx )/resolution);
  vec4 b = texture(tex0, (gl_FragCoord.xy - offset.yx )/resolution);
  
//  vec4 nuC = color;
//  nuC.a -= 0.005;
  
  float a = max(color.a, r.a);
  a = max(a, l.a);
  a = max(a, b.a);
  a = max(a, t.a);
  
  a -= 0.005;
  
//  vec4 avg = (r + l + t + b)*0.90;
//  if (color.a == 0.0) {
//    if (r.a > 0.0) {
//      color = r;
//    } else if (l.a > 0.0) {
//      color = l;
//    } else if (t.a > 0.0) {
//      color = t;
//    } else if (b.a > 0.0) {
//      color = b;
//    }
//  }
  
//  color = mix(color, avg, 0.5);
  color.a = a;
  
//  if (color.a == 0.00) {
//    color = vec4(1.,0.0,0.0,1.0);
//  }
  
  outputColor = color;
  
}
