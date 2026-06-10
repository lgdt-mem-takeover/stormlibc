#version 330 core
layout (location = 0) in vec3 apos;
layout (location = 1) in vec4 acol;
layout (location = 2) in vec2 auv;


out vec2 TexCoords;
out vec4 ocol;
uniform vec2 u_screen;


void main()
{

	vec2 ndc = vec2((apos.x / u_screen.x) * 2.0 - 1.0, 1.0 - (apos.y / u_screen.y) * 2.0);
	gl_Position = vec4(ndc, apos.z, 1.0);
	TexCoords = auv;
	ocol = acol;
}
