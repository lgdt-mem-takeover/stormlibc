#version 330 core

in vec2 TexCoords;
in vec4 ocol;
out vec4 color;

uniform sampler2D u_tex;

void main()
{
	float a = texture(u_tex, TexCoords).r;
	color = vec4(ocol.rgb, ocol.a * a);
}
