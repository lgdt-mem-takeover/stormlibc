#version 330 core
in vec4 vColor;
in vec2 in_halfsz;
in vec2 in_uv;
in float in_radius;
in float in_border_thickness;
in vec4 in_border_color;
out vec4 FragColor;
uniform float u_softness;

float sdf_rounded_rect(vec2 p, vec2 halfsz, float radius)
{
	vec2 d = abs(p) - halfsz + vec2(radius);
	return length(max(d, vec2(0.0))) + min(max(d.x, d.y), 0.0) - radius;
}

void main()
{
	float r = min(in_radius, min(in_halfsz.x, in_halfsz.y));
	float t = clamp(in_border_thickness, 0.0, min(r, min(in_halfsz.x, in_halfsz.y)));
	float dist_outer = sdf_rounded_rect(in_uv, in_halfsz, r);

	vec2 inner_halfsz = max(in_halfsz - vec2(t), vec2(0.0));
	float inner_r = max(r - t, 0.0);
	float dist_inner = sdf_rounded_rect(in_uv, inner_halfsz, inner_r);
	float aa = max(u_softness, fwidth(dist_outer));

	float outer_alpha = 1.0 - smoothstep(0.0, aa, dist_outer);
	float inner_alpha = 1.0 - smoothstep(0.0, aa, dist_inner);
	float border_alpha = max(outer_alpha - inner_alpha, 0.0);

	vec4 fill_col = vColor * inner_alpha;
	vec4 border_col = in_border_color * border_alpha;
	vec4 col = fill_col + border_col;
	if (col.a <= 0.0) discard;
	FragColor = col;
}
