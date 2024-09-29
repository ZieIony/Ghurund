#version 330 core

layout(location = 0) in  vec3 in_Position;
out vec2 out_Position;

void main(void)
{
	gl_Position = vec4(in_Position, 1.0);
	out_Position = (in_Position.xy+vec2(1.0, 1.0))/2.0;
}