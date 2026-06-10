#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec4 in_color;

uniform vec2 u_screen;

void main()
{
	vec2 ndc = vec2(
			in_pos.x / u_screen.x * 2.0 - 1.0,
			1.0 - (in_pos.y / u_screen.y) * 2.0
		       );
}
