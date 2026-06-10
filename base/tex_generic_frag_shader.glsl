#version 330

in vec4 v_color;
in vec2 v_uv;

out vec4 FragColor;

uniform sampler2D u_tex;

void main()
{
	vec4 tex = texture(u_tex, v_uv) * v_color;
	if (tex.a < 0.01)
		discard;
	FragColor = tex;
}

