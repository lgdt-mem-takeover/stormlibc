#version 330
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_uv;

out vec4 v_color;
out vec2 v_uv;

uniform vec2 u_screen;

void main()
{
	vec2 ndc = vec2((in_pos.x / u_screen.x) * 2.0f - 1.0, 1.0 - (in_pos.y / u_screen.y) * 2.0);

	gl_Position = vec4(ndc, in_pos.z, 1.0);
	v_color = in_color;
	v_uv = in_uv;
}
