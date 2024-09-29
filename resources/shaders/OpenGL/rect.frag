#version 330 core

precision highp float;

uniform vec2 resolution;
in vec2 out_Position;
out vec4 out_Color;

float isRoundRect(vec2 pos, vec2 size, float r) {
  float a = size.x/2.0-r;
  float b = size.y/2.0-r;
  float x = pos.x;
  float y = pos.y;
  float eq = pow(max(abs(x)-a,0.0),2.0)+pow(max(abs(y)-b, 0.0), 2.0) - pow(r, 2.0);
  return mix(1.0, 0.0, eq);
}

float isRoundRect(vec2 pos, vec2 size, float r, float t) {
  float a = size.x/2.0-r;
  float b = size.y/2.0-r;
  float x = pos.x;
  float y = pos.y;
  float eq = pow(max(abs(x)-a,0.0),2.0)+pow(max(abs(y)-b, 0.0), 2.0) - pow(r, 2.0);
  float eq2 = pow(max(abs(x)-a,0.0),2.0)+pow(max(abs(y)-b, 0.0), 2.0) - pow(r - t, 2.0);
  return mix(1.0, 0.0, eq*eq2);
}

void main() {
  vec2 pos = out_Position * resolution;
  float x = pos.x-resolution.x/3.0;
  float y = pos.y-resolution.y/3.0;
  float x2 = pos.x-resolution.x*2.0/3.0;
  float y2 = pos.y-resolution.y*2.0/3.0;
  float c = isRoundRect(vec2(x,y), vec2(120.0, 80.0), 10.0);
  float c2 = isRoundRect(vec2(x2,y2), vec2(140.0, 100.0), 10.0, 2.0);

    out_Color = vec4(max(c,c2),out_Position.xy,1.0);
}
