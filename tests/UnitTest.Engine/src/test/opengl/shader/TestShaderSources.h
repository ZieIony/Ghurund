#pragma once
#include "core/string/String.h"

namespace UnitTest::Utils {
	using namespace Ghurund::Core;

	static const inline AString TEST_VERTEX_SHADER_SOURCE_NO_MAIN = R"(
#version 410

precision highp float;

layout(location = 0) in  vec3 in_Position;
out vec2 out_Position;

void asdf(void)
{
	gl_Position = vec4(in_Position, 1.0);
	out_Position = (in_Position.xy+vec2(1.0, 1.0))/2.0;
}
)";

	static const inline AString TEST_VERTEX_SHADER_SOURCE = R"(
#version 410

precision highp float;

layout(location = 0) in  vec3 in_Position;
out vec2 out_Position;

void main(void)
{
	gl_Position = vec4(in_Position, 1.0);
	out_Position = (in_Position.xy+vec2(1.0, 1.0))/2.0;
}
)";

	static const inline AString TEST_FRAGMENT_SHADER_SOURCE = R"(
#version 410

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
)";

	static const inline AString TEST_OPENGL_SHADER_SOURCE = R"(
<?xml version="1.0" encoding="utf-8"?>
<Shader>
<Vertex>
#version 410

precision highp float;

layout(location = 0) in  vec3 in_Position;
out vec2 out_Position;

void main(void)
{
	gl_Position = vec4(in_Position, 1.0);
	out_Position = (in_Position.xy+vec2(1.0, 1.0))/2.0;
}
</Vertex>
<Fragment>
#version 410

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
</Fragment>
</Shader>
)";
}