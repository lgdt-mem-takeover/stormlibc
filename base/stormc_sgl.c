#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#define STB_RECT_PACK_IMPLEMENTATION
#include "../stb_rect_pack.h"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_surface.h>
#include "stormc_base.h"
#include "stormc_allocator.c"
#include "../text/stormc_string.c"
#include "../containers/stormc_hash.c"
#include <math.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winitializer-overrides"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverride-init-side-effects"


#include <ft2build.h>
#include FT_FREETYPE_H

// #include "/data/site_packages/glad/include/glad/glad.h"
// #include "/data/site_packages/glad/src/glad.c"

#define SGL_GL_IMPL
#include "sglglad.h"

/* --- WHITE / GRAYS --- */
#define SGL_WHITE100 ((struct color){1.f, 1.f, 1.f, 1.f})
#define SGL_WHITE90  ((struct color){0.9f, 0.9f, 0.9f, 0.9f})
#define SGL_WHITE75  ((struct color){0.75f, 0.75f, 0.75f, 0.75f})
#define SGL_WHITE50  ((struct color){0.5f, 0.5f, 0.5f, 0.5f})
#define SGL_WHITE25  ((struct color){0.25f, 0.25f, 0.25f, 0.25f})

#define SGL_BLACK100 ((struct color){0.f, 0.f, 0.f, 1.f})
#define SGL_BLACK90  ((struct color){0.f, 0.f, 0.f, 0.9f})
#define SGL_BLACK75  ((struct color){0.f, 0.f, 0.f, 0.75f})
#define SGL_BLACK50  ((struct color){0.f, 0.f, 0.f, 0.5f})
#define SGL_BLACK25  ((struct color){0.f, 0.f, 0.f, 0.25f})

/* --- BLUE --- */
#define SGL_BLUE100 ((struct color){0.1f, 0.1f, 1.f, 1.f})
#define SGL_BLUE90  ((struct color){0.1f, 0.1f, 0.9f, 0.9f})
#define SGL_BLUE75  ((struct color){0.1f, 0.1f, 0.75f, 0.75f})
#define SGL_BLUE50  ((struct color){0.1f, 0.1f, 0.5f, 0.5f})
#define SGL_BLUE25  ((struct color){0.1f, 0.1f, 0.25f, 0.25f})

#define SGL_BLUE_LIGHT100 ((struct color){0.4f, 0.6f, 1.f, 1.f})
#define SGL_BLUE_DARK100  ((struct color){0.05f, 0.05f, 0.4f, 1.f})

/* --- RED --- */
#define SGL_RED100 ((struct color){1.f, 0.1f, 0.1f, 1.f})
#define SGL_RED90  ((struct color){0.9f, 0.1f, 0.1f, 0.9f})
#define SGL_RED75  ((struct color){0.75f, 0.1f, 0.1f, 0.75f})
#define SGL_RED50  ((struct color){0.5f, 0.1f, 0.1f, 0.5f})
#define SGL_RED25  ((struct color){0.25f, 0.1f, 0.1f, 0.25f})

#define SGL_RED_DARK100 ((struct color){0.4f, 0.05f, 0.05f, 1.f})
#define SGL_RED_LIGHT100 ((struct color){1.f, 0.4f, 0.4f, 1.f})

/* --- GREEN --- */
#define SGL_GREEN100 ((struct color){0.1f, 1.f, 0.1f, 1.f})
#define SGL_GREEN90  ((struct color){0.1f, 0.9f, 0.1f, 0.9f})
#define SGL_GREEN75  ((struct color){0.1f, 0.75f, 0.1f, 0.75f})
#define SGL_GREEN50  ((struct color){0.1f, 0.5f, 0.1f, 0.5f})
#define SGL_GREEN25  ((struct color){0.1f, 0.25f, 0.1f, 0.25f})

#define SGL_GREEN_DARK100 ((struct color){0.05f, 0.4f, 0.05f, 1.f})
#define SGL_GREEN_LIGHT100 ((struct color){0.4f, 1.f, 0.4f, 1.f})

#define SGL_FOREST_PRIMARY       ((struct color){0.18f, 0.45f, 0.28f, 1.f}) // base green
#define SGL_FOREST_PRIMARY_HOVER ((struct color){0.22f, 0.55f, 0.34f, 1.f})
#define SGL_FOREST_PRIMARY_ACTIVE ((struct color){0.14f, 0.35f, 0.22f, 1.f})

#define SGL_FOREST_BG_DARKEST ((struct color){0.04f, 0.07f, 0.05f, 1.f})   // main app bg
#define SGL_FOREST_BG         ((struct color){0.07f, 0.12f, 0.08f, 1.f})   // window bg
#define SGL_FOREST_BG_ELEV    ((struct color){0.10f, 0.18f, 0.12f, 1.f})   // panels/cards
#define SGL_FOREST_ACCENT ((struct color){0.45f, 0.80f, 0.50f, 1.f}) // moss highlight

#define SGL_FOREST_BORDER        ((struct color){0.16f, 0.28f, 0.20f, 1.f})
#define SGL_FOREST_BORDER_SOFT   ((struct color){0.12f, 0.22f, 0.16f, 1.f})

#define SGL_FOREST_TEXT_PRIMARY   ((struct color){0.85f, 0.92f, 0.88f, 1.f})
#define SGL_FOREST_TEXT_MUTED     ((struct color){0.55f, 0.65f, 0.60f, 1.f})
#define SGL_FOREST_TEXT_DISABLED  ((struct color){0.35f, 0.42f, 0.38f, 1.f})

#define SGL_FOREST_SUCCESS ((struct color){0.30f, 0.70f, 0.40f, 1.f})
#define SGL_FOREST_WARNING ((struct color){0.70f, 0.60f, 0.25f, 1.f})
#define SGL_FOREST_DANGER  ((struct color){0.65f, 0.25f, 0.25f, 1.f})


/* --- YELLOW --- */
#define SGL_YELLOW100 ((struct color){1.f, 1.f, 0.1f, 1.f})
#define SGL_YELLOW90  ((struct color){0.9f, 0.9f, 0.1f, 0.9f})
#define SGL_YELLOW75  ((struct color){0.75f, 0.75f, 0.1f, 0.75f})
#define SGL_YELLOW50  ((struct color){0.5f, 0.5f, 0.1f, 0.5f})

#define SGL_YELLOW_DARK100 ((struct color){0.5f, 0.5f, 0.05f, 1.f})

/* --- CYAN --- */
#define SGL_CYAN100 ((struct color){0.1f, 1.f, 1.f, 1.f})
#define SGL_CYAN90  ((struct color){0.1f, 0.9f, 0.9f, 0.9f})
#define SGL_CYAN75  ((struct color){0.1f, 0.75f, 0.75f, 0.75f})

/* --- MAGENTA --- */
#define SGL_MAGENTA100 ((struct color){1.f, 0.1f, 1.f, 1.f})
#define SGL_MAGENTA90  ((struct color){0.9f, 0.1f, 0.9f, 0.9f})
#define SGL_MAGENTA75  ((struct color){0.75f, 0.1f, 0.75f, 0.75f})

/* --- ORANGE --- */
#define SGL_ORANGE100 ((struct color){1.f, 0.5f, 0.1f, 1.f})
#define SGL_ORANGE90  ((struct color){0.9f, 0.45f, 0.1f, 0.9f})
#define SGL_ORANGE75  ((struct color){0.75f, 0.4f, 0.1f, 0.75f})

/* --- PURPLE --- */
#define SGL_PURPLE100 ((struct color){0.6f, 0.2f, 1.f, 1.f})
#define SGL_PURPLE90  ((struct color){0.55f, 0.2f, 0.9f, 0.9f})
#define SGL_PURPLE75  ((struct color){0.5f, 0.2f, 0.75f, 0.75f})

/* --- UI NEUTRALS --- */
#define SGL_UI_BG        ((struct color){0.08f, 0.08f, 0.1f, 1.f})
#define SGL_UI_PANEL     ((struct color){0.12f, 0.12f, 0.15f, 1.f})
#define SGL_UI_BORDER    ((struct color){0.2f, 0.2f, 0.25f, 1.f})
#define SGL_UI_HOVER     ((struct color){0.2f, 0.3f, 0.5f, 0.5f})
#define SGL_UI_ACTIVE    ((struct color){0.3f, 0.5f, 0.8f, 0.8f})


#define SGL_UNROLL_COLOR4(_color) (_color.r), (_color.g), (_color.b), (_color.a)
#define SGL_UNROLL_COLOR3(_color) (_color.r), (_color.g), (_color.b)

enum sgl_pipeline_type{
	SGL_PIPELINE_UI,
	SGL_PIPELINE_TEX,
	SGL_PIPELINE_GLYPHS,
	SGL_PIPELINE_TEX_GENERIC,
	SGL_PIPELINE_CT
};

struct color {
	f32 r, g, b, a;
};

struct rect{
	f32 x, y, w, h;
};

struct vec2 {
	f32 x, y;
};

struct vec2i {
	i32 x, y;
};

struct vec2u {
	i32 x, y;
};


struct vec2lu {
	i32 x, y;
};

struct vec2d {
	f64 x, y;
};

struct vec3 {
	f32 x, y, z;
};

struct vec3i {
	i32 x, y, z;
};


struct ui_box{
	f32		x, y, w, h;
	struct color	color;
	f32		border_thickness;
	struct color	border_color;
	f32		radius;
};

struct vertex_ui {
	struct vec3	pos;
	struct color	color;
	struct vec2	halfsz;
	struct vec2	uv;
	f32		radius;
	f32		border_thickness;
	struct color	border_color;
};

struct vertex_glyph {
	struct vec3	pos;
	struct color	color;
	struct vec2	uv;
};


struct vertex_tex {
	struct vec3	pos;
	struct color	color;
	struct vec2	uv;
};

struct vertex_tex_generic {
	struct vec3	pos;
	struct color	color;
	struct vec2	uv;
};


struct quad {
	u32	indices[6];
};



#define SGL_MAX_DROPS 36
struct sgl_input {
	bool key_pressed[SDL_SCANCODE_COUNT];
	bool key_repeated[SDL_SCANCODE_COUNT];
	bool key_released[SDL_SCANCODE_COUNT];

	bool mouse_pressed[8];
	bool mouse_released[8];

	f32	mouse_x;
	f32 	mouse_y;
	f32 	mouse_wheel_x;
	f32 	mouse_wheel_y;
	f32	mouse_dx;
	f32	mouse_dy;

	const bool	*keyboard_state;
	int		keyboard_state_count;

	char	text_data[1024];
	u64	text_data_len;


	u32	files_drop_count;
	char	files_dropped_paths[SGL_MAX_DROPS][256];
};


struct glyph_info {
	f32 ax;
	f32 ay;

	f32 bw;
	f32 bh;

	f32 bl;
	f32 bt;

	f32 u0, v0;
	f32 u1, v1;
};



struct text_atlas {
	u32			texture_id;
	u32 			width;
	u32 			height;
	f32 			ascent;
	f32			line_height;
	struct glyph_info	glyphs[128];
};

struct sgl_vertex_attribs {
	GLint		size;
	GLenum		type;
	GLboolean	normalised;
	GLsizei		stride;
	const GLvoid	*pointer;
};


struct sgl_pipeline {
	u32 program;

	u32	vao;
	u32 	vbo;
	u32 	ebo;
	bool32	has_ebo;

	GLenum primitive;

	GLenum vbo_target;
	GLenum vbo_usage;
	GLenum ebo_target;
	GLenum ebo_usage;

	u64 vertex_stride;
	u64 index_stride;

	struct sgl_vertex_attribs attribs[32];
	u64 ct_attribs;

	// optional cached uniforms
	int u_screen;
	int u_softness;
	int u_atlas;
	int u_tex;
};


struct sgl_ctx{
	bool64			running;
	SDL_Event		events;
	SDL_Window		*window;
	i32			ww, wh;
	SDL_GLContext		gl_ctx;
	struct sgl_input	sgl_input;
	struct {
		struct quad		*quads;
		u64			quads_cap;
		u64			ct_quads;
		u64			cmted_bytes_quads;
		struct vertex_ui	*vertices;
		u64			verts_cap;
		u64			ct_vertices;
		u64			cmted_bytes_verts;
		struct sgl_pipeline	pipeline;
	}ui;

	struct {
		struct vertex_glyph	*vertices;
		u64			verts_cap;
		u64			ct_vertices;
		u64			cmted_bytes_verts;
		struct sgl_pipeline	pipeline;
		struct text_atlas	atlas;
	}glyphs;

	struct {
		struct vertex_tex	*vertices;
		u64			verts_cap;
		u64			ct_vertices;
		u64			cmted_bytes_verts;
		struct sgl_pipeline	pipeline;
	}textures;

	struct {
		struct quad			*quads;
		u32				cmted_bytes_quads;
		u32				current_texture;
		struct vertex_tex_generic	*vertices;
		u64				verts_cap;
		u32				ct_vertices;
		u32				cmted_bytes_verts;
		struct sgl_pipeline		pipeline;
		u64				ct_quads;
	}textures_generic;


	struct {
		struct {
			u64		ui_max_quads;
			u64 		ui_max_vertices;
			u64 		txt_size_max;
			u8		*txt_font;
			FT_Face		ft_face;
			FT_Library	ft_lib;
		}ui;


		struct {
			u64 glyph_max_quads;
			u64 glyph_max_vertices;
		}glyphs;

		struct {
			u64 texture_max_quads;
			u64 texture_max_vertices;
		}textures;


		struct {
			u64	max_textures_generic;
		}textures_generic;
		f32 ui_softness_default;
		bool32 vsync;
	}cfg_init_time;
};


static struct sgl_ctx sgl = {
	.running = true,
	.cfg_init_time = {
		.ui = {
			.ui_max_quads = 4096,
			.ui_max_vertices = 4096 * 4,
			.txt_size_max = 48,
			.txt_font = (u8 *)FONT_PATH_DEVAJU_SANS,
		},
		.textures_generic = {
			.max_textures_generic = 2048,
		},
		.ui_softness_default = 12.0f,
		.vsync = true,
	},
};


struct sgl_texture{
	u32	gl_id;
	f32	w;
	f32	h;
	u8	*data;
};

/*@FUNCS SIGNATURES*/
inline u32  sgl_files_dropped_count(void);
inline bool32 sgl_any_text_input(void);
inline bool32 sgl_is_mouse_in_rect(struct rect r);
inline bool32 sgl_has_keyboard_focus(void);
inline bool32 sgl_has_mouse_focus(void);
static inline i32  sgl_window_width(void);
static inline i32  sgl_window_height(void);
static inline bool32 sgl_running(void);
static inline u64  sgl_text_input_len(void);
static inline const char *sgl_text_input_data(void);
static bool32 sgl_col_rec_point(struct rect r, struct vec2 p);
static void sgl_input_process_event(void);
static void sgl_end_draw(void);
static void sgl_begin_draw(void);
static inline void sgl_dispatch_pipeline(enum sgl_pipeline_type);
static inline void sgl_input_begin_frame(void);
static inline void sgl_input_init(void);
static inline void sgl_poll_input(void);
static inline f32 sgl_mouse_dx(void);
static inline f32 sgl_mouse_dy(void);
static inline struct vec2 sgl_mouse_delta(void);
static inline struct vec2 sgl_mouse_pos(void);
static inline bool32 sgl_items_dropped(void);
static struct sgl_texture sgl_load_texture(const char *path);
static inline const char *sgl_dropped_path(u32 index);
static void sgl_draw_texture(struct sgl_texture texture, f32 x, f32 y, f32 w, f32 h, struct color color);
static inline void sgl_clear_batch(enum sgl_pipeline_type type);




static void copy_ft_bitmap_into_atlas(
	u8 *atlas_pixels,
	u32 atlas_w,
	u32 dst_x,
	u32 dst_y,
	const FT_Bitmap *bm)
{
	if (!bm || !bm->buffer || bm->width == 0 || bm->rows == 0) {
		return;
	}

	int pitch = bm->pitch;
	int abs_pitch = pitch < 0 ? -pitch : pitch;

	/*
	    FreeType says pitch is the offset to go DOWN one row.
	    We normalize to a top-to-bottom walk here.
	*/
	const u8 *row0;
	if (pitch > 0) {
		row0 = (const u8 *)bm->buffer;
	} else {
		row0 = (const u8 *)bm->buffer + (size_t)(bm->rows - 1) * (size_t)abs_pitch;
	}

	for (u32 row = 0; row < (u32)bm->rows; ++row) {
		const u8 *src = row0 + (size_t)row * (size_t)abs_pitch;
		u8 *dst = atlas_pixels + (size_t)(dst_y + row) * (size_t)atlas_w + (size_t)dst_x;
		memcpy(dst, src, (size_t)bm->width);
	}
}

struct text_atlas stc_build_text_atlas(FT_Face face, int first_char, int last_char)
{
	struct text_atlas atlas = {0};
	FT_GlyphSlot g = face->glyph;

	u32 atlas_w = 0;
	u32 atlas_h = 0;

	for (int c = first_char; c < last_char; ++c) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			continue;
		}

		atlas_w += (u32)g->bitmap.width + 1;
		atlas_h = stc_maxu32(atlas_h, (u32)g->bitmap.rows);
	}

	if (atlas_w == 0 || atlas_h == 0) {
		fprintf(stderr, "text atlas size is zero\n");
		return atlas;
	}

	atlas.width  = atlas_w;
	atlas.height = atlas_h;
	atlas.ascent = (f32)(face->size->metrics.ascender >> 6);
	atlas.line_height = (f32)(face->size->metrics.height >> 6);

	u8 *pixels = calloc((size_t)atlas.width * (size_t)atlas.height, 1);
	if (!pixels) {
		fprintf(stderr, "atlas pixel alloc failed\n");
		return atlas;
	}

	u32 x_off = 0;

	for (int c = first_char; c < last_char; ++c) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			continue;
		}

		copy_ft_bitmap_into_atlas(
			pixels,
			atlas.width,
			x_off,
			0,
			&g->bitmap
		);

		f32 bw = (f32)g->bitmap.width;
		f32 bh = (f32)g->bitmap.rows;

		atlas.glyphs[c] = (struct glyph_info){
			.ax = (f32)(g->advance.x >> 6),
			.ay = (f32)(g->advance.y >> 6),
			.bw = bw,
			.bh = bh,
			.bl = (f32)g->bitmap_left,
			.bt = (f32)g->bitmap_top,
			.u0 = (f32)x_off / (f32)atlas.width,
			.v0 = 0.0f,
			.u1 = (f32)(x_off + (u32)g->bitmap.width) / (f32)atlas.width,
			.v1 = bh / (f32)atlas.height,
		};

		x_off += (u32)g->bitmap.width + 1;
	}

	glGenTextures(1, &atlas.texture_id);
	glBindTexture(GL_TEXTURE_2D, atlas.texture_id);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_R8,
		(GLsizei)atlas.width,
		(GLsizei)atlas.height,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		pixels
	);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);
	free(pixels);

	return atlas;
}

void sgl_init_quads_texture_generic(void)
{
	sgl.textures_generic.quads = stc_alloc(sgl.cfg_init_time.textures_generic.max_textures_generic * sizeof(struct quad));
	sgl.textures_generic.cmted_bytes_quads = sgl.cfg_init_time.textures_generic.max_textures_generic * sizeof(struct quad);
	for (u64 i = 0; i < sgl.cfg_init_time.textures_generic.max_textures_generic; ++i) {
		u64 base = i * 4;
		sgl.textures_generic.quads[i] = (struct quad){
			.indices = {
				base + 0, base + 1, base + 3,
				base + 1, base + 2, base + 3
			},
		};
	}
}


void sgl_init_vertices_texture_generic(void)
{
	sgl.textures_generic.vertices = stc_alloc(sgl.cfg_init_time.textures_generic.max_textures_generic * sizeof(struct vertex_tex_generic) * 4);
	sgl.textures_generic.cmted_bytes_verts = sgl.cfg_init_time.textures_generic.max_textures_generic * sizeof(struct vertex_tex_generic) * 4;
}

void sgl_init_quads_ui(void)
{
	sgl.ui.quads = stc_rsrv(1llu << 38);
	u64 commit = sizeof(struct quad) * PAGESIZE;
	if (stc_commit(sgl.ui.quads, commit) == NULL) {
		perror("mprotect");
		exit(1);
	}
	sgl.ui.cmted_bytes_quads = commit;
	sgl.ui.quads_cap = PAGESIZE;


	for (u64 i = 0; i < sgl.ui.quads_cap; ++i) {
		u64 base = i * 4;
		sgl.ui.quads[i] = (struct quad){
			.indices = {
				base + 0, base + 1, base + 3,
				base + 1, base + 2, base + 3
			},
		};
	}
}



/*Probably unneeded but will keep*/
// void *sgl_add_quad_ui(struct quad q)
// {
// 	if (unlikely(sgl.ui.quads == NULL)) {
// 		sgl_init_quads_ui();
// 	}
//
//
// 	u64 size_needed_in_bytes = (sgl.ui.ct_quads + 1) * sizeof(*sgl.ui.quads);
//
// 	if (size_needed_in_bytes > sgl.ui.cmted_bytes_quads) {
// 		fprintf(stderr, "Cannot allocate more quads\n");
// 		exit(1);
// 	}
//
// 	sgl.ui.quads[sgl.ui.ct_quads++] = q;
// 	return sgl.ui.quads;
// }


void sgl_init_vertices_glyphs(void)
{
	sgl.glyphs.vertices = stc_rsrv(1llu << 38);
	u64 commit = sizeof(struct vertex_glyph) * PAGESIZE * 6;
	if (stc_commit(sgl.glyphs.vertices, commit) == NULL) {
		perror("mprotect");
		exit(1);
	}
	sgl.glyphs.cmted_bytes_verts = commit;
	sgl.glyphs.verts_cap = PAGESIZE * 6;
}

void *sgl_add_vertex_glyph(struct vertex_glyph v)
{
	if (unlikely(sgl.glyphs.vertices == NULL)) {
		sgl_init_vertices_glyphs();
	}

	u64 size_needed_in_bytes = (sgl.glyphs.ct_vertices + 1) * sizeof(*sgl.glyphs.vertices);

	if (size_needed_in_bytes > sgl.glyphs.cmted_bytes_verts) {
		fprintf(stderr, "Cannot allocate more vertex glyphs\n");
		exit(1);
	}

	sgl.glyphs.vertices[sgl.glyphs.ct_vertices++] = v;
	return sgl.glyphs.vertices;
}

void sgl_init_vertices_ui(void)
{
	sgl.ui.vertices = stc_rsrv(1llu << 38);
	u64 commit = (sizeof(struct vertex_ui) * PAGESIZE) * 6;
	if (stc_commit(sgl.ui.vertices, commit) == NULL) {
		perror("mprotect");
		exit(1);
	}
	sgl.ui.cmted_bytes_verts = commit;
	sgl.ui.verts_cap = PAGESIZE * 6;
}

void *sgl_add_vertex_ui(struct vertex_ui v)
{
	if (unlikely(sgl.ui.vertices == NULL)) {
		sgl_init_vertices_ui();
	}


	u64 size_needed_in_bytes = (sgl.ui.ct_vertices + 1) * sizeof(*sgl.ui.vertices);

	if (size_needed_in_bytes > sgl.ui.cmted_bytes_verts) {
		fprintf(stderr, "Cannot allocate more vertex ui\n");
		exit(1);
	}

	sgl.ui.vertices[sgl.ui.ct_vertices++] = v;
	return sgl.ui.vertices;
}



void sgl_init_freetype(void)
{
	if (FT_Init_FreeType(&sgl.cfg_init_time.ui.ft_lib))
	{
		fprintf(stderr, "Could not init FreeType Library");
		exit(1);
	}

	if (FT_New_Face(sgl.cfg_init_time.ui.ft_lib, (const char *)sgl.cfg_init_time.ui.txt_font, 0, &sgl.cfg_init_time.ui.ft_face))
	{
		fprintf(stderr,  "Failed to load font\n");
		exit(1);
	}
	FT_Set_Pixel_Sizes(sgl.cfg_init_time.ui.ft_face, 0, sgl.cfg_init_time.ui.txt_size_max);
}

void sgl_init(int window_width, int window_height, struct stc_string8 window_name)
{
	sgl_init_freetype();
	// stbi_set_flip_vertically_on_load(1);
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "SDL_GL_SetAttribute failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}
	SDL_GL_ResetAttributes();
	if (
	    !SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3) ||
	    !SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3) ||
	    !SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE) ||
	    !SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) ||
	    !SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24) ||
	    !SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1) ||
	    !SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4) ||
	    !SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8)) {
		fprintf(stderr, "SDL_GL_SetAttribute failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(1);
	}

	 sgl.window = SDL_CreateWindow((const char *)window_name.str, window_width, window_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!sgl.window) {
		fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(sgl.window);
		SDL_Quit();
		exit(1);
	}

	sgl.gl_ctx = SDL_GL_CreateContext(sgl.window);
	if (!sgl.gl_ctx) {
		fprintf(stderr, "SDL_GL_CreateContext failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(sgl.window);
		SDL_Quit();
		exit(1);
	}

	if (!SDL_GL_MakeCurrent(sgl.window, sgl.gl_ctx)) {
		fprintf(stderr, "SDL_GL_MakeCurrent failed %s\n", SDL_GetError());
	}
	if (!sgl_gl_load_all()) {
		fprintf(stderr, "failed to load GL functions\n");
		exit(1);
	}

	SDL_GL_SetSwapInterval(1);
	sgl_input_init();
}


#define SGL_MAX_ATTRIBS 32


struct params_shader_program {
	struct stc_string8		vert_filepath;
	struct stc_string8		frag_filepath;
	struct sgl_vertex_attribs	attribs[SGL_MAX_ATTRIBS];
	GLenum				primitive;
	int				ct_attribs;
	GLenum				vbo_target;
	GLenum				vbo_usage;
	GLsizeiptr			vbo_size;
	const GLvoid			*vbo_data;
	GLenum				ebo_target;
	GLenum				ebo_usage;
	GLsizeiptr			ebo_size;
	const GLvoid			*ebo_data;
};





static void
sgl_check_bound_buffer_size(GLenum target, GLsizeiptr expected_size)
{
	GLint size = 0;
	glGetBufferParameteriv(target, GL_BUFFER_SIZE, &size);

	if ((GLsizeiptr)size != expected_size) {
		fprintf(stderr,
			"[BUFFER ERROR] target=0x%x size=%d expected=%td\n",
			target, size, (ptrdiff_t)expected_size);
		exit(1);
	}
}

#define sgl_make_pipeline(...) \
	({\
		struct sgl_pipeline pipeline = _sgl_make_pipeline((struct params_shader_program){\
		.vert_filepath = (struct stc_string8){0}, .frag_filepath = (struct stc_string8){0},\
		.primitive = GL_TRIANGLES,\
		.attribs = {0}, .ct_attribs = -1,\
		.vbo_target = 0, .vbo_usage = 0, .vbo_size = 0, .vbo_data = NULL,\
		.ebo_target = 0, .ebo_usage = 0, .ebo_size = 0, .ebo_data = NULL,\
		__VA_ARGS__\
		});\
		pipeline;\
	})
static void

sgl_check_program(u32 program, GLenum check_type)
{
	int success = 0;
	GLchar info_log[512] = {};
	GLsizei log_len = 0;
	glGetProgramiv(program, check_type, &success);
	if (!success) {
		glGetProgramInfoLog(program, sizeof(info_log), &log_len, info_log);
		fprintf(stderr, "[PROGRAM ERROR] %s\n", info_log);
		glDeleteProgram(program);
		exit(1);
	}
}


static void
sgl_check_shader(GLuint shader)
{
	GLint ok = 0;
	GLchar info_log[512] = {};
	GLsizei log_len = 0;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		glGetShaderInfoLog(shader, sizeof(info_log), &log_len, info_log);
		fprintf(stderr, "[SHADER ERROR] %.*s\n", log_len, info_log);
		glDeleteShader(shader);
		exit(1);
	}
}


struct sgl_pipeline
_sgl_make_pipeline(struct params_shader_program params)
{
	struct sgl_pipeline pl = {};

	FILE *vertf = fopen((const char *)params.vert_filepath.str, "rb");
	if (!vertf) {
		fprintf(stderr, "Failed to open %s\n", params.vert_filepath.str);
		exit(1);
	}
	if(fseek(vertf, 0, SEEK_END) != 0) {
		perror("fseek");
		exit(1);
	}
	i32 len_shader_vert = ftell(vertf);
	if (len_shader_vert < 0) {
		perror("ftell");
		exit(1);
	}
	rewind(vertf);
	struct stc_string8 vert_shader_src = {.str = stc_alloc(len_shader_vert + 1), .len = len_shader_vert};
	vert_shader_src.str[len_shader_vert] = '\0';
	fread(vert_shader_src.str, sizeof(*vert_shader_src.str), len_shader_vert, vertf);


	const GLchar *vert_src = (const GLchar *)vert_shader_src.str;
	GLint vert_len = (GLint)len_shader_vert;
	u32 vert_shader_id = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_shader_id, 1, &vert_src, &vert_len);
	glCompileShader(vert_shader_id);
	sgl_check_shader(vert_shader_id);



	FILE *fragf = fopen((const char *)params.frag_filepath.str, "rb");
	if (!fragf) {
		fprintf(stderr, "Failed to open %s\n", params.frag_filepath.str);
		exit(1);
	}

	if (fseek(fragf, 0, SEEK_END) != 0) {
		perror("fseek");
		exit(1);
	}

	i32 len_shader_frag = ftell(fragf);
	if (len_shader_frag < 0) {
		perror("ftell");
		exit(1);
	}
	rewind(fragf);
	struct stc_string8 frag_shader_src = {.str = stc_alloc(len_shader_frag + 1), .len = len_shader_frag};
	const GLchar *frag_src = (const GLchar *)frag_shader_src.str;
	frag_shader_src.str[len_shader_frag] = '\0';
	fread(frag_shader_src.str, sizeof(*frag_shader_src.str), len_shader_frag, fragf);


	u32 frag_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	GLint frag_len = (GLint)len_shader_frag;
	glShaderSource(frag_shader_id, 1, &frag_src, &frag_len);
	glCompileShader(frag_shader_id);
	sgl_check_shader(frag_shader_id);

	pl.program = glCreateProgram();

	glAttachShader(pl.program, vert_shader_id);
	glAttachShader(pl.program, frag_shader_id);
	glLinkProgram(pl.program);

	sgl_check_program(pl.program, GL_LINK_STATUS);

	glDeleteShader(vert_shader_id);
	glDeleteShader(frag_shader_id);


	stc_free(vert_shader_src.str, len_shader_vert + 1);
	stc_free(frag_shader_src.str, len_shader_frag + 1);
	fclose(vertf);
	fclose(fragf);



	glGenVertexArrays(1, &pl.vao);
	glGenBuffers(1, &pl.vbo);

	glBindVertexArray(pl.vao);
	pl.primitive = params.primitive;
	pl.vbo_target = params.vbo_target;
	pl.vbo_usage = params.vbo_usage;
	pl.ebo_target = params.ebo_target;
	pl.ebo_usage = params.ebo_usage;
	memcpy(pl.attribs, params.attribs, sizeof(*params.attribs) * params.ct_attribs);
	pl.ct_attribs = params.ct_attribs;

	glBindBuffer(pl.vbo_target, pl.vbo);
	glBufferData(pl.vbo_target, params.vbo_size, params.vbo_data, pl.vbo_usage);
	sgl_check_bound_buffer_size(params.vbo_target, params.vbo_size);


	if (params.ebo_data != NULL && params.ebo_size > 0) {
		glGenBuffers(1, &pl.ebo);
		glBindBuffer(pl.ebo_target, pl.ebo);
		glBufferData(pl.ebo_target, params.ebo_size, params.ebo_data, params.ebo_usage);
		sgl_check_bound_buffer_size(params.ebo_target, params.ebo_size);
		pl.has_ebo = true;
	}




	for (u64 i = 0; i < params.ct_attribs; ++i) {
		glVertexAttribPointer(i,
				      pl.attribs[i].size,
				      pl.attribs[i].type,
				      pl.attribs[i].normalised,
				      pl.attribs[i].stride,
				      pl.attribs[i].pointer);
		glEnableVertexAttribArray(i);
	}

	pl.u_screen		= glGetUniformLocation(pl.program, "u_screen");
	pl.u_softness 		= glGetUniformLocation(pl.program, "u_softness");
	pl.u_atlas    		= glGetUniformLocation(pl.program, "u_atlas");
	pl.u_tex		= glGetUniformLocation(pl.program, "u_tex");

	glBindVertexArray(0);


	return pl;
}



void sgl_draw_uibox(struct ui_box r)
{
	struct vec2 h = { r.w * 0.5f, r.h * 0.5f };

	struct vertex_ui top_left = {
		.pos = {r.x, r.y, 0.0f},
		.color = r.color,
		.halfsz = h,
		.uv = {-h.x, -h.y},
		.radius = r.radius,
		.border_thickness = r.border_thickness,
		.border_color = r.border_color,
	};

	struct vertex_ui top_right = {
		.pos = {r.x + r.w, r.y, 0.0f},
		.color = r.color,
		.halfsz = h,
		.uv = {h.x, -h.y},
		.radius = r.radius,
		.border_thickness = r.border_thickness,
		.border_color = r.border_color,
	};

	struct vertex_ui bot_right = {
		.pos = {r.x + r.w, r.y + r.h, 0.0f},
		.color = r.color,
		.halfsz = h,
		.uv = {h.x, h.y},
		.radius = r.radius,
		.border_thickness = r.border_thickness,
		.border_color = r.border_color,
	};

	struct vertex_ui bot_left = {
		.pos = {r.x, r.y + r.h, 0.0f},
		.color = r.color,
		.halfsz = h,
		.uv = {-h.x, h.y},
		.radius = r.radius,
		.border_thickness = r.border_thickness,
		.border_color = r.border_color,
	};

	sgl_add_vertex_ui(top_left);
	sgl_add_vertex_ui(top_right);
	sgl_add_vertex_ui(bot_right);
	sgl_add_vertex_ui(bot_left);

	sgl.ui.ct_quads++;
}




#define SGL_SET_ATTR(__normalised, __struct_type, __field_member_count, __field_type, __field_name) \
    (struct sgl_vertex_attribs){ \
        .size = (__field_member_count), \
        .type = GL_FLOAT, \
        .normalised = (__normalised), \
        .stride = sizeof(__struct_type), \
        .pointer = (const GLvoid *)offsetof(__struct_type, __field_name) \
    }





#define sgl_create_pipeline(vs_path, fs_path, type)\
	_sgl_create_pipeline(STR(vs_path), STR(fs_path), type)

void _sgl_create_pipeline(struct stc_string8 vs_path, struct stc_string8 fs_path, enum sgl_pipeline_type pipeline_type)
{
	switch (pipeline_type) {
	default:
		fprintf(stderr, "Unknown Pipeline Type Code: %d", pipeline_type);
		exit(1);
	case SGL_PIPELINE_UI:
		sgl_init_vertices_ui();
		sgl_init_quads_ui();
		sgl.ui.pipeline = sgl_make_pipeline(
		    .vert_filepath = vs_path,
		    .frag_filepath = fs_path,
		    .attribs = {
			    [0] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 3, struct vec3, pos),
			    [1] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 4, struct color, color),
			    [2] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 2, struct vec2, halfsz),
			    [3] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 2, struct vec2, uv),
			    [4] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 1, f32, radius),
			    [5] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 1, f32, border_thickness),
			    [6] = SGL_SET_ATTR(GL_FALSE, struct vertex_ui, 4, struct color, border_color),
		    },
		    .vbo_data = sgl.ui.vertices,
		    .vbo_size = sgl.ui.cmted_bytes_verts,
		    .vbo_usage = GL_DYNAMIC_DRAW,
		    .vbo_target = GL_ARRAY_BUFFER,

		    .ebo_data = sgl.ui.quads,
		    .ebo_size = sgl.ui.cmted_bytes_quads,
		    .ebo_usage = GL_STATIC_DRAW,
		    .ebo_target = GL_ELEMENT_ARRAY_BUFFER,
		    .primitive = GL_TRIANGLES,
		    .ct_attribs = 7,
		    );
		break;

	case SGL_PIPELINE_GLYPHS:
		sgl_init_vertices_glyphs();

		sgl.glyphs.pipeline = sgl_make_pipeline(
		    .vert_filepath = vs_path,
		    .frag_filepath = fs_path,

		    .attribs = {
			    [0] = SGL_SET_ATTR(GL_FALSE, struct vertex_glyph, 3, struct vec3, pos),
			    [1] = SGL_SET_ATTR(GL_FALSE, struct vertex_glyph, 4, struct color, color),
			    [2] = SGL_SET_ATTR(GL_FALSE, struct vertex_glyph, 2, struct vec2, uv),
		    },

		    .vbo_data = sgl.glyphs.vertices,
		    .vbo_size = sgl.glyphs.cmted_bytes_verts,
		    .vbo_usage = GL_DYNAMIC_DRAW,
		    .vbo_target = GL_ARRAY_BUFFER,
		    .primitive = GL_TRIANGLES,
		    .ct_attribs = 3,

		    );
		break;
	case SGL_PIPELINE_TEX:
		break;
	case SGL_PIPELINE_TEX_GENERIC:
		sgl_init_vertices_texture_generic();
		sgl_init_quads_texture_generic();
		sgl.textures_generic.pipeline = sgl_make_pipeline(
		    .vert_filepath = vs_path,
		    .frag_filepath = fs_path,

		    .attribs = {
			    [0] = SGL_SET_ATTR(GL_FALSE, struct vertex_tex_generic, 3, struct vec3, pos),
			    [1] = SGL_SET_ATTR(GL_FALSE, struct vertex_tex_generic, 4, struct color, color),
			    [2] = SGL_SET_ATTR(GL_FALSE, struct vertex_tex_generic, 2, struct vec2, uv),
		    },

		    .vbo_data = sgl.textures_generic.vertices,
		    .vbo_size = sgl.textures_generic.cmted_bytes_verts,
		    .vbo_usage = GL_DYNAMIC_DRAW,
		    .vbo_target = GL_ARRAY_BUFFER,
		    .ebo_usage = GL_STATIC_DRAW,
		    .ebo_target = GL_ELEMENT_ARRAY_BUFFER,
		    .ebo_data = sgl.textures_generic.quads,
		    .ebo_size = sgl.textures_generic.cmted_bytes_quads,
		    .primitive = GL_TRIANGLES,
		    .ct_attribs = 3,
		    );
		break;
	}
}


void sgl_draw_text(struct stc_string8 text, f32 x, f32 y, f32 size, struct color color)
{
	if (!text.str || text.len == 0) {
		return;
	}


	f32 scale = size / (f32)sgl.cfg_init_time.ui.txt_size_max;
	f32 pen_x = x;
	f32 pen_y = y;
	for (u64 i = 0; i < text.len; ++i) {
		unsigned char c = (unsigned char)text.str[i];

		if (c == '\n') {
			pen_x = x;
			pen_y += sgl.glyphs.atlas.line_height * scale;
			continue;
		}

		if (c >= STC_ARRCOUNT(sgl.glyphs.atlas.glyphs)) {
			continue;
		}

		struct glyph_info g = sgl.glyphs.atlas.glyphs[c];

		if (g.bw <= 0.0f || g.bh <= 0.0f) {
			pen_x += g.ax * scale;
			continue;
		}

		f32 xpos = pen_x + g.bl * scale;
		f32 ypos = pen_y + (sgl.glyphs.atlas.ascent - g.bt) * scale;

		f32 w = g.bw * scale;
		f32 h = g.bh * scale;

		struct vertex_glyph v0 = {
			.pos = { xpos,     ypos,     0.0f },
			.color = color,
			.uv = { g.u0, g.v0 },
		};

		struct vertex_glyph v1 = {
			.pos = { xpos,     ypos + h, 0.0f },
			.color = color,
			.uv = { g.u0, g.v1 },
		};

		struct vertex_glyph v2 = {
			.pos = { xpos + w, ypos + h, 0.0f },
			.color = color,
			.uv = { g.u1, g.v1 },
		};

		struct vertex_glyph v3 = {
			.pos = { xpos,     ypos,     0.0f },
			.color = color,
			.uv = { g.u0, g.v0 },
		};

		struct vertex_glyph v4 = {
			.pos = { xpos + w, ypos + h, 0.0f },
			.color = color,
			.uv = { g.u1, g.v1 },
		};

		struct vertex_glyph v5 = {
			.pos = { xpos + w, ypos,     0.0f },
			.color = color,
			.uv = { g.u1, g.v0 },
		};

		sgl_add_vertex_glyph(v0);
		sgl_add_vertex_glyph(v1);
		sgl_add_vertex_glyph(v2);
		sgl_add_vertex_glyph(v3);
		sgl_add_vertex_glyph(v4);
		sgl_add_vertex_glyph(v5);

		pen_x += g.ax * scale;
	}
}

void sgl_poll_input(void)
{
	sgl_input_begin_frame();

	while (SDL_PollEvent(&sgl.events)) {
		sgl_input_process_event();
	}
}

void sgl_begin_draw(void)
{
	sgl_poll_input();
	SDL_GetWindowSizeInPixels(sgl.window, &sgl.ww, &sgl.wh);

	glViewport(0, 0, sgl.ww, sgl.wh);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


inline void sgl_clear_batch(enum sgl_pipeline_type type)
{
	switch (type) {
	case SGL_PIPELINE_UI:
		sgl.ui.ct_vertices = 0;
		sgl.ui.ct_quads = 0;
		break;
	case SGL_PIPELINE_GLYPHS:
		sgl.glyphs.ct_vertices = 0;
		break;
	case SGL_PIPELINE_TEX:
		sgl.textures.ct_vertices = 0;
		break;
	case SGL_PIPELINE_TEX_GENERIC:
		sgl.textures_generic.ct_quads = 0;
		sgl.textures_generic.ct_vertices = 0;
		break;
	default:
		fprintf(stderr, "Unknown Pipeline Type Code: %d", type);
		exit(1);
	}
}


inline void sgl_dispatch_pipeline(enum sgl_pipeline_type pipeline_type)
{

	switch (pipeline_type) {
	default:
		fprintf(stderr, "Unknown Pipeline Type Code: %d", pipeline_type);
		exit(1);
	case SGL_PIPELINE_UI:
	{
		if (sgl.ui.ct_quads == 0) return;
		struct sgl_pipeline *ui = &sgl.ui.pipeline;

		glUseProgram(ui->program);
		glBindVertexArray(ui->vao);
		glBindBuffer(ui->vbo_target, ui->vbo);
		glUniform2f(ui->u_screen, (f32)sgl.ww, (f32)sgl.wh);
		glUniform1f(ui->u_softness, sgl.cfg_init_time.ui_softness_default);

		glBufferSubData(ui->vbo_target, 0,
				sgl.ui.ct_vertices * sizeof(*sgl.ui.vertices),
				sgl.ui.vertices);

		glDrawElements(ui->primitive, sgl.ui.ct_quads * 6, GL_UNSIGNED_INT, 0);
		break;
	}
	case SGL_PIPELINE_GLYPHS:
	{
		if (sgl.glyphs.ct_vertices == 0) return;
		struct sgl_pipeline *glyph = &sgl.glyphs.pipeline;

		glUseProgram(glyph->program);
		glBindVertexArray(glyph->vao);
		glBindBuffer(glyph->vbo_target, glyph->vbo);

		glUniform2f(glyph->u_screen, (f32)sgl.ww, (f32)sgl.wh);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sgl.glyphs.atlas.texture_id);
		glUniform1i(glyph->u_tex, 0);

		glBufferSubData(
		    glyph->vbo_target,
		    0,
		    sgl.glyphs.ct_vertices * sizeof(*sgl.glyphs.vertices),
		    sgl.glyphs.vertices
		    );

		glDrawArrays(glyph->primitive, 0, sgl.glyphs.ct_vertices);
		break;

	}
	case SGL_PIPELINE_TEX:
	{
		if (sgl.textures.ct_vertices == 0) return;
		struct sgl_pipeline *textures = &sgl.textures.pipeline;
		break;
	}
	case SGL_PIPELINE_TEX_GENERIC:
	{
		if (sgl.textures_generic.ct_quads == 0) return;
		struct sgl_pipeline *textures_generic = &sgl.textures_generic.pipeline;


		glUseProgram(textures_generic->program);
		glBindVertexArray(textures_generic->vao);
		glBindBuffer(textures_generic->vbo_target, textures_generic->vbo);
		glUniform2f(textures_generic->u_screen, (f32)sgl.ww, (f32)sgl.wh);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, sgl.textures_generic.current_texture);
		glUniform1i(textures_generic->u_tex, 0);

		glBufferSubData(textures_generic->vbo_target, 0,
				sgl.textures_generic.ct_vertices * sizeof(*sgl.textures_generic.vertices),
				sgl.textures_generic.vertices);

		glDrawElements(textures_generic->primitive, sgl.textures_generic.ct_quads * 6, GL_UNSIGNED_INT, 0);
		break;

	}
	}
	sgl_clear_batch(pipeline_type);
}


void sgl_end_draw(void)
{
	sgl_dispatch_pipeline(SGL_PIPELINE_UI);
	sgl_dispatch_pipeline(SGL_PIPELINE_GLYPHS);
	sgl_dispatch_pipeline(SGL_PIPELINE_TEX);
	sgl_dispatch_pipeline(SGL_PIPELINE_TEX_GENERIC);

	SDL_GL_SwapWindow(sgl.window);
}


void sgl_cleanup(void)
{
	FT_Done_Face(sgl.cfg_init_time.ui.ft_face);
	FT_Done_FreeType(sgl.cfg_init_time.ui.ft_lib);
	glDeleteVertexArrays(1, &sgl.ui.pipeline.vao);
	glDeleteBuffers(1, &sgl.ui.pipeline.vbo);
	glDeleteBuffers(1, &sgl.ui.pipeline.ebo);
	glDeleteProgram(sgl.ui.pipeline.program);

	glDeleteVertexArrays(1, &sgl.glyphs.pipeline.vao);
	glDeleteBuffers(1, &sgl.glyphs.pipeline.vbo);
	if (sgl.glyphs.pipeline.has_ebo) {
		glDeleteBuffers(1, &sgl.glyphs.pipeline.ebo);
	}
	glDeleteProgram(sgl.glyphs.pipeline.program);
	glDeleteTextures(1, &sgl.glyphs.atlas.texture_id);

	glDeleteVertexArrays(1, &sgl.textures.pipeline.vao);
	glDeleteBuffers(1, &sgl.textures.pipeline.vbo);
	if (sgl.textures.pipeline.has_ebo) {
		glDeleteBuffers(1, &sgl.textures.pipeline.ebo);
	}
	glDeleteProgram(sgl.textures.pipeline.program);


	glDeleteVertexArrays(1, &sgl.textures_generic.pipeline.vao);
	glDeleteBuffers(1, &sgl.textures_generic.pipeline.vbo);
	if (sgl.textures_generic.pipeline.has_ebo) {
		glDeleteBuffers(1, &sgl.textures_generic.pipeline.ebo);
	}
	glDeleteProgram(sgl.textures_generic.pipeline.program);

	stc_free(sgl.textures_generic.quads, sgl.textures_generic.cmted_bytes_quads);
	stc_free(sgl.textures_generic.vertices, sgl.textures_generic.cmted_bytes_verts);
	stc_free(sgl.ui.quads, sgl.ui.cmted_bytes_quads);
	stc_free(sgl.ui.vertices, sgl.ui.cmted_bytes_verts);
}



static void
sgl_input_init(void)
{
	sgl.sgl_input.keyboard_state = SDL_GetKeyboardState(&sgl.sgl_input.keyboard_state_count);
}

static void
sgl_input_begin_frame(void)
{
	memset(sgl.sgl_input.key_pressed, 0, sizeof(sgl.sgl_input.key_pressed));
	memset(sgl.sgl_input.key_released, 0, sizeof(sgl.sgl_input.key_released));
	memset(sgl.sgl_input.key_repeated, 0, sizeof(sgl.sgl_input.key_repeated));
	memset(sgl.sgl_input.mouse_pressed, 0, sizeof(sgl.sgl_input.mouse_pressed));
	memset(sgl.sgl_input.mouse_released, 0, sizeof(sgl.sgl_input.mouse_released));

	sgl.sgl_input.mouse_wheel_x = 0.0f;
	sgl.sgl_input.mouse_wheel_y = 0.0f;
	sgl.sgl_input.files_drop_count = 0;
	// sgl.sgl_input.text_data_len = 0;
	// sgl.sgl_input.text_data[0] = '\0';

	SDL_GetMouseState(&sgl.sgl_input.mouse_x, &sgl.sgl_input.mouse_y);
	SDL_GetRelativeMouseState(&sgl.sgl_input.mouse_dx, &sgl.sgl_input.mouse_dy);
}

void
sgl_input_process_event(void)
{
	switch (sgl.events.type) {
	case SDL_EVENT_QUIT:
		sgl.running = false;
		break;
	case SDL_EVENT_TEXT_INPUT:
	{
		const char *t = sgl.events.text.text;
		while (*t && sgl.sgl_input.text_data_len < 1023) {
			sgl.sgl_input.text_data[sgl.sgl_input.text_data_len++] = *t++;
		}
		sgl.sgl_input.text_data[sgl.sgl_input.text_data_len] = '\0';
	}
		break;

	case SDL_EVENT_KEY_DOWN:
	{
		SDL_Scancode sc = sgl.events.key.scancode;
		if (!sgl.events.key.repeat) {
			if ((int)sc >= 0 && (int)sc < SDL_SCANCODE_COUNT) {
				sgl.sgl_input.key_pressed[sc] = true;
			}
		} else {
			if ((int)sc >= 0 && (int)sc < SDL_SCANCODE_COUNT) {
				sgl.sgl_input.key_repeated[sc] = true;
			}
		}
	}
		break;

	case SDL_EVENT_KEY_UP:
	{
		SDL_Scancode sc = sgl.events.key.scancode;
		if ((int)sc >= 0 && (int)sc < SDL_SCANCODE_COUNT) {
			sgl.sgl_input.key_released[sc] = true;
		}
	} break;

	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		if (sgl.events.button.button < (int)SDL_arraysize(sgl.sgl_input.mouse_pressed)) {
			sgl.sgl_input.mouse_pressed[sgl.events.button.button] = true;
		}
		break;

	case SDL_EVENT_MOUSE_BUTTON_UP:
		if (sgl.events.button.button < (int)SDL_arraysize(sgl.sgl_input.mouse_released)) {
			sgl.sgl_input.mouse_released[sgl.events.button.button] = true;
		}
		break;

	case SDL_EVENT_MOUSE_MOTION:
		sgl.sgl_input.mouse_x = sgl.events.motion.x;
		sgl.sgl_input.mouse_y = sgl.events.motion.y;
		break;

	case SDL_EVENT_MOUSE_WHEEL:
		sgl.sgl_input.mouse_wheel_x += sgl.events.wheel.x;
		sgl.sgl_input.mouse_wheel_y += sgl.events.wheel.y;
		break;

	case SDL_EVENT_DROP_FILE:
	{
		char *path = (char *)sgl.events.drop.data;
		u64 path_len = sstrlenx((const  u8*)path);
		if (sgl.sgl_input.files_drop_count < SGL_MAX_DROPS) {
			stc_memcpy(sgl.sgl_input.files_dropped_paths[sgl.sgl_input.files_drop_count], path, path_len);
			sgl.sgl_input.files_dropped_paths[sgl.sgl_input.files_drop_count][path_len] = '\0';
			sgl.sgl_input.files_drop_count++;
			printf("Dropped %s\n", sgl.sgl_input.files_dropped_paths[0]);
		}
		break;

	}

	default:
		break;
	}
}

static inline bool
sgl_is_key_down(SDL_Scancode sc)
{
	if ((int)sc < 0 || (int)sc >= sgl.sgl_input.keyboard_state_count) {
		return false;
	}
	return sgl.sgl_input.keyboard_state[sc];
}

static inline bool
sgl_is_key_pressed(SDL_Scancode sc)
{
	if ((int)sc < 0 || (int)sc >= SDL_SCANCODE_COUNT) {
		return false;
	}
	return sgl.sgl_input.key_pressed[sc];
}

static inline bool
sgl_is_key_repeated(SDL_Scancode sc)
{
	if ((int)sc < 0 || (int)sc >= SDL_SCANCODE_COUNT) {
		return false;
	}
	return sgl.sgl_input.key_repeated[sc];
}

static inline bool
sgl_is_key_released(SDL_Scancode sc)
{
	if ((int)sc < 0 || (int)sc >= SDL_SCANCODE_COUNT) {
		return false;
	}
	return sgl.sgl_input.key_released[sc];
}

static inline bool
sgl_is_mouse_down(Uint8 button)
{
	float x, y;
	Uint32 mask = SDL_GetMouseState(&x, &y);
	return (mask & SDL_BUTTON_MASK(button)) != 0;
}

static inline bool
sgl_is_mouse_pressed(Uint8 button)
{
	if (button >= SDL_arraysize(sgl.sgl_input.mouse_pressed)) {
		return false;
	}
	return sgl.sgl_input.mouse_pressed[button];
}

static inline bool
sgl_is_mouse_released(Uint8 button)
{
	if (button >= SDL_arraysize(sgl.sgl_input.mouse_released)) {
		return false;
	}
	return sgl.sgl_input.mouse_released[button];
}

static inline float
sgl_mouse_x(void)
{
	return sgl.sgl_input.mouse_x;
}

static inline float
sgl_mouse_y(void)
{
	return sgl.sgl_input.mouse_y;
}

static inline float
sgl_mouse_wheel_x(void)
{
	return sgl.sgl_input.mouse_wheel_x;
}

static inline float
sgl_mouse_wheel_y(void)
{
	return sgl.sgl_input.mouse_wheel_y;
}


inline i32  sgl_window_width(void)  { return sgl.ww; }
inline i32  sgl_window_height(void) { return sgl.wh; }
inline bool32 sgl_running(void)     { return sgl.running; }

inline u64  sgl_text_input_len(void) { return sgl.sgl_input.text_data_len; }
inline const char *sgl_text_input_data(void) { return sgl.sgl_input.text_data; }

inline u32  sgl_files_dropped_count(void) { return sgl.sgl_input.files_drop_count; }


inline bool32 sgl_any_text_input(void)
{
	return sgl.sgl_input.text_data_len > 0;
}

inline bool32 sgl_is_mouse_in_rect(struct rect r)
{
	return sgl_col_rec_point(r, sgl_mouse_pos());
}

inline bool32 sgl_has_keyboard_focus(void)
{
	return SDL_GetKeyboardFocus() == sgl.window;
}

inline bool32 sgl_has_mouse_focus(void)
{
	return SDL_GetMouseFocus() == sgl.window;
}



void sgl_text_append(struct stc_string8 *s, u32 cap)
{
	if (cap == 0 || sgl.sgl_input.text_data_len == 0) return;
	if (s->len >= cap - 1) return;

	u64 free_space = cap - 1 - s->len;
	u64 n = sgl.sgl_input.text_data_len;
	if (n > free_space) n = free_space;

	memcpy(s->str + s->len, sgl.sgl_input.text_data, n);
	s->len += n;
	s->str[s->len] = '\0';

	sgl.sgl_input.text_data_len = 0;
	sgl.sgl_input.text_data[0] = '\0';
}



void sgl_draw_line(f32 x0, f32 y0, f32 x1, f32 y1, f32 thickness, struct color color)
{
	f32 dx = x1 - x0;
	f32 dy = y1 - y0;

	f32 len = sqrtf(dx*dx + dy*dy);   // needed
	if (len <= 0.0001f) return;
	struct vec2 h = { len * 0.5f, thickness * 0.5f };

	// unit direction
	f32 ux = dx / len;
	f32 uy = dy / len;

	// perpendicular (normal)
	f32 nx = -uy;
	f32 ny = ux;

	// half thickness offset
	f32 ox = nx * thickness * 0.5f;
	f32 oy = ny * thickness * 0.5f;
	struct vec2 p0 = {x0 + ox, y0 + oy};
	struct vec2 p1 = {x1 + ox, y1 + oy};
	struct vec2 p2 = {x1 - ox, y1 - oy};
	struct vec2 p3 = {x0 - ox, y0 - oy};

	sgl_add_vertex_ui((struct vertex_ui){
		.pos = {p0.x, p0.y},
		.radius = h.y,
		.halfsz = h,
		.uv = {-h.x, -h.y},
		.color = color,
	});
	sgl_add_vertex_ui((struct vertex_ui){
		.pos = {p1.x, p1.y},
		.radius = h.y,
		.halfsz = h,
		.uv = {h.x, -h.y},
		.color = color,
	});
	sgl_add_vertex_ui((struct vertex_ui){
		.pos = {p2.x, p2.y},
		.radius = h.y,
		.halfsz = h,
		.uv = {h.x, h.y},
		.color = color,
	});
	sgl_add_vertex_ui((struct vertex_ui){
		.pos = {p3.x, p3.y},
		.halfsz = h,
		.radius = h.y,
		.uv = {-h.x, h.y},
		.color = color,
	});
	sgl.ui.ct_quads++;
}

inline float sgl_mouse_dx(void) { return sgl.sgl_input.mouse_dx; }
inline float sgl_mouse_dy(void) { return sgl.sgl_input.mouse_dy; }
inline struct vec2 sgl_mouse_delta(void) { return (struct vec2){sgl.sgl_input.mouse_dx, sgl.sgl_input.mouse_dy}; }
inline struct vec2 sgl_mouse_pos(void) { return (struct vec2){sgl.sgl_input.mouse_x, sgl.sgl_input.mouse_y}; }


bool32 sgl_col_rec_point(struct rect r, struct vec2 p)
{
	return (p.x >= r.x) && (p.x <= r.x + r.w) && (p.y >= r.y) && (p.y <= r.y + r.h);
}


struct vec2 sgl_measure_text(struct stc_string8 s, u32 size)
{
	struct vec2 out = {0};

	if (!s.str || s.len == 0) return out;

	f32 scale = size / (f32)sgl.cfg_init_time.ui.txt_size_max;

	f32 line_width = 0.0f;
	f32 max_width = 0.0f;
	u32 lines = 1;

	for (u64 i = 0; i < s.len; ++i) {
		unsigned char c = (unsigned char)s.str[i];

		if (c == '\n') {
			if (line_width > max_width) max_width = line_width;
			line_width = 0.0f;
			lines++;
			continue;
		}

		if (c >= STC_ARRCOUNT(sgl.glyphs.atlas.glyphs)) continue;

		struct glyph_info g = sgl.glyphs.atlas.glyphs[c];
		line_width += g.ax * scale;
	}

	if (line_width > max_width) max_width = line_width;

	out.x = max_width;
	out.y = lines * sgl.glyphs.atlas.line_height * scale;

	return out;
}


inline bool32 sgl_items_dropped(void)
{
	return sgl.sgl_input.files_drop_count > 0;
}


struct sgl_texture sgl_load_texture(const char *path)
{
	struct sgl_texture tex = {0};

	int w, h, ch;
	stbi_uc *data = stbi_load(path, &w, &h, &ch, 4);
	if (!data) {
		fprintf(stderr, "stbi failed: %s\n", path);
		return tex;
	}

	tex.w = w;
	tex.h = h;

	glGenTextures(1, &tex.gl_id);
	glBindTexture(GL_TEXTURE_2D, tex.gl_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA8,
		w,
		h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return tex;
}



inline const char *sgl_dropped_path(u32 index)
{
	return sgl.sgl_input.files_dropped_paths[index];
}


void
sgl_draw_texture(
    struct sgl_texture texture,
    f32 x, f32 y,
    f32 w, f32 h,
    struct color color)
{
	if (texture.gl_id == 0) return;

	if (sgl.textures_generic.ct_quads > 0 &&
	    sgl.textures_generic.current_texture != texture.gl_id) {
		sgl_dispatch_pipeline(SGL_PIPELINE_TEX_GENERIC);
	}

	if (sgl.textures_generic.ct_quads >= sgl.cfg_init_time.textures_generic.max_textures_generic) {
		sgl_dispatch_pipeline(SGL_PIPELINE_TEX_GENERIC);
	}

	sgl.textures_generic.current_texture = texture.gl_id;

	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x, y, 0.0f},
		.color = color,
		.uv = {0.0f, 0.0f},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x + w, y, 0.0f},
		.color = color,
		.uv = {1.0f, 0.0f},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x + w, y + h, 0.0f},
		.color = color,
		.uv = {1.0f, 1.0f},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x, y + h, 0.0f},
		.color = color,
		.uv = {0.0f, 1.0f},
	};

	sgl.textures_generic.ct_quads++;
}
