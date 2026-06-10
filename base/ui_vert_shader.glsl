#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aCol;
layout (location = 2) in vec2 halfsz;
layout (location = 3) in vec2 uv;
layout (location = 4) in float radius;
layout (location = 5) in float aBorderThickness;
layout (location = 6) in vec4 aBorderColor;
out float in_border_thickness;
out vec4 in_border_color;
out vec4 vColor;
out vec2 in_halfsz;
out vec2 in_uv;
out float in_radius;
uniform vec2 u_screen;

void main()
{
	vec2 ndc = vec2((aPos.x / u_screen.x) * 2.0 - 1.0, 1.0 - (aPos.y / u_screen.y) * 2.0);
	gl_Position = vec4(ndc, aPos.z, 1.0);
	vColor = aCol;
	in_halfsz = halfsz;
	in_uv = uv;
	in_radius = radius;
	in_border_thickness = aBorderThickness;
	in_border_color = aBorderColor;
}


