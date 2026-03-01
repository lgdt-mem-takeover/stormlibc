#include <assert.h>
#include <stddef.h>
#define STORMC_RAYLIB
#define STORMC_ALLOCATOR
#define STORMC_STRING
#define STORMC_THREADING
#define STORMC_HASHFUNC
#include "/data/2026-projs/c/stormlibc/stormc_header.h"




#define Vec2CMP(a, b) ((a.x == b.x) && (a.y == b.y))

#define STC_DRAWTEXT(text, pos, color) DrawTextEx((gui.txt_font), (text), (pos), (gui.txt_size), (gui.txt_spacing), (color))

// static _Thread_local struct stc_thread_worker worker = {0};

static struct stc_string8 fake_files[] = {
	STR("awesome.exe"), STR("sexypicks.png"), STR("notascam.exe"),
	STR("memories.db"), STR("stackedaf.png"), STR("notascam.bin"),
	STR("oddone.whodis?")
};
static int arr_size = sizeof(fake_files) / sizeof(*fake_files);

#define Y_PADDING 50.0f


struct cursor {
	float x, y;
};

static struct cursor global_cursor = {};


enum box_flags{
	BOX_FLAGS_NIL			= 0,
	BOX_FLAG_COLLISION_HIGHLIGHT	= (1llu << 0),
	BOX_FLAG_LAST_FRAME_PRESSED	= (1llu << 1),
	BOX_FLAG_CLICKABLE		= (1llu << 2),
	BOX_FLAG_HAS_BORDER		= (1llu << 3),
	BOX_FLAG_ON_CLICK_ANIM_XY	= (1llu << 4),
	BOX_FLAG_TEXT			= (1llu << 5),
};

#define BOX_FLAGS_LIFETIME_PER_FRAME_MASK (BOX_FLAG_COLLISION_HIGHLIGHT)


/*@BOX*/
struct box{
	u64			flags;
	struct stc_string8	text;
	Rectangle		surf;
	Color			color;
	f32			anim_progress;
	f32			hot_t;
	f32			active_t;
	bool			is_open;
};


enum grow_types{
	GROW_FIT_TEXT,
	GROW_TYPES_COUNT
};


struct layout{
	Vector2		pos;
	f32		padding_children;
	f32		margin_x;
	f32		margin_y;
	union{
		u32	e;
		f32	v;
	}grow_x;
	union{
		u32	e;
		f32	v;
	}grow_y;
};

struct box_interaction {
	struct box	*box;
	Vector2		mouse;
	Vector2		drag_delta;
	bool		clicked;
	bool		double_clicked;
	bool		right_clicked;
	bool		pressed;
	bool		released;
	bool		dragging;
	bool		right_dragging;
	bool		hovering;
};


#define MAX_ROOTS (1llu << 15)
#define MAX_CHILDREN_PER_ROOT_ROOTS (1llu << 15)
#define MAX_BOXES (MAX_ROOTS) * (MAX_CHILDREN_PER_ROOT_ROOTS)
#define MAX_RESERVATION (1llu << 38)

#define STARTING_BOXES PAGESIZE


#define active_root_idx() gui.active_root
#define active_root_children_ct() gui.ct_active_roots
#define active_child() gui.active_root_active_child
#define root_ct() gui.ct_active_roots
#define active_child_box() gui.boxes[active_child()]
#define get_box(box_idx) gui.boxes[box_idx]



struct stack_frame{
	u64	*children;
	u64	ct_children;
	u64	cmt;
	u64	rsrv;
};


/*@GUI*/
struct gui{
	u64			ct_boxes;
	struct box		*boxes;
	u64			*hash;
	struct layout		*layouts;

	struct stack_frame	*ilt;
	Font			txt_font;
	int			txt_size;
	int			txt_spacing;
	u64			ct_active_frames;
};


#define CHILD_EXPAND_COUNT 512

static struct stc_stack *stack_boxes;
static struct stc_stack *stack_hashes;
static struct stc_stack *stack_layouts;
static struct stc_stack *stack_ilt;
static struct stc_stack *stack_ilt_children;
struct gui gui = {};






void allcoate_boxes(void)
{
	stc_stack_push(stack_boxes, struct box, STARTING_BOXES);
	stc_stack_push(stack_hashes, u64, STARTING_BOXES);
	stc_stack_push(stack_layouts, struct layout, STARTING_BOXES);
}




void allocate_children_at_root(u64 root_idx)
{
	stc_os_mem_cmt(((u8 *)gui.ilt[root_idx].children + gui.ilt[root_idx].cmt), CHILD_EXPAND_COUNT);
}



u64 top_frame(void)
{
	return gui.ct_active_frames - 1;
}

u64 push_frame(void)
{
	u64 current_frame_idx = gui.ct_active_frames;
	gui.ct_active_frames++;
	return current_frame_idx;
}


u64 pop_frame(void)
{
	u64 top_frame = gui.ct_active_frames - 1;
	gui.ct_active_frames--;
	return top_frame;
}



void make_layout(struct stc_string8 string, struct layout layouts)
{

	gui.hash[gui.ct_boxes] = HASHSTR_SCALAR(string, 0);
	gui.layouts[gui.ct_boxes] = layouts;
	gui.ct_boxes++;

}


/*@INITBOXES_START*/
void init_boxes(void)
{
	const u32 RSRV = 1 << 24;
	stack_boxes = stc_stack_gen(1llu << 32);
	stack_hashes = stc_stack_gen(1llu << 32);
	stack_layouts = stc_stack_gen(1llu << 32);
	stack_ilt = stc_stack_gen(1llu << 32);

	gui.boxes = (struct box *)stc_stack_push(stack_boxes, struct box, STARTING_BOXES);
	gui.hash = (u64 *)stc_stack_push(stack_boxes, u64, STARTING_BOXES);
	gui.layouts = (struct layout *)stc_stack_push(stack_boxes, struct layout, STARTING_BOXES);
	gui.ilt = (struct stack_frame *)stc_stack_push(stack_boxes, struct stack_frame, STARTING_BOXES);

	for (u64 i = 0; i < STARTING_BOXES; ++i) {
		gui.ilt[i].children = (u64 *)stc_os_mem_rsrv(RSRV);
		allocate_children_at_root(i);
		gui.ilt[i].cmt = sizeof(u64) * STARTING_BOXES;
		gui.ilt[i].rsrv = (RSRV);
	}


	struct layout global_space_layout = {
		.pos = {0, 0},
		.grow_x = {.v = INF},
		.grow_y = {.v = INF}
	};
	make_layout(STR("Global Space"), global_space_layout);
}
/*@INITBOXES_END*/

u64 get_idx_from_hash(u64 hash)
{
	for (u64 idx = 0; idx < gui.ct_boxes; ++idx) {
		if (gui.hash[idx] == hash)
			return idx;
	}
	return MAX_UINT64;
}

struct box *get_box_from_string(struct stc_string8 string)
{
	u64 hash = HASHSTR_SCALAR(string, 0);
	u64 box_id = get_idx_from_hash(hash);
	if (box_id == MAX_UINT64) {
		return NULL;
	}


	return &gui.boxes[box_id];
}

u64 get_box_id_from_string(struct stc_string8 string)
{
	u64 hash = HASHSTR_SCALAR(string, 0);
	u64 box_id = get_idx_from_hash(hash);

	return box_id;

}


u64 ui_make_box(u64 flags, struct stc_string8 string)
{
	struct box new_box = {};
	new_box.flags = flags;
	u64 box_id = gui.ct_boxes;
	gui.boxes[box_id] = new_box;
	gui.hash[box_id] = HASHSTR_SCALAR(string, 0);

	gui.ct_boxes++;

	return box_id;
}


u64 ui_get_root_boxid(struct stc_string8 string)
{

}



void begin_root_ctx(struct stc_string8 string)
{
	thread(0) {
		push_frame();
	}
	stc_barrier_wait(0);
}


void end_root_ctx(void)
{
	thread(0) {
		pop_frame();
		// printf("%lu\n", gui.ct_active_frames);
		assert(gui.ct_active_frames == 0);
	}
	stc_barrier_wait(0);
}


struct box_interaction ui_interaction_from_box(struct box *box)
{
	if (box == NULL) {
		printf("box is null\n");
		exit(1);
	}
	struct box_interaction inter = {0};
	Vector2 mpos = GetMousePosition();
	Vector2 mdelta = GetMouseDelta();
	bool32 collided = CheckCollisionPointRec(mpos, box->surf);
	bool32 mdown_left = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
	bool32 mdown_right = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
	bool32 mpress_left = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
	bool32 mpress_right = IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

	inter.hovering = collided;
	inter.clicked = (mpress_left && collided) * !!(box->flags & BOX_FLAG_CLICKABLE);
	inter.right_clicked = mpress_right && collided;
	inter.dragging = mdown_left && collided;
	inter.right_dragging = mdown_right && collided;
	inter.box = box;




	return inter;
}


struct params_ui_context_menu {
	struct stc_string8	string;
	struct layout		layout;
};

struct params_ui_context_menu_element {
	struct stc_string8	string;
	struct layout		layout;
};


#define any_mbutton_pressed() (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
#define STUB_LAYOUT ((struct layout){.pos = {.x = 0.0f, .y = 0.0f}, .grow_x = {.v = INF}})
#define layout_is_stub(layout) (layout.grow_x.v == INF)



#define ui_context_menu(__string, ...)\
	_ui_context_menu((struct params_ui_context_menu){.string = __string, .layout = STUB_LAYOUT, __VA_ARGS__})

#define ui_context_menu_element(__string, ...)\
	_ui_context_menu_elem((struct params_ui_context_menu_element){.string = __string, .layout = STUB_LAYOUT, __VA_ARGS__})

struct box_interaction _ui_context_menu(struct params_ui_context_menu params)
{
	u64 frame_idx = push_frame();
	gui.ilt[frame_idx].ct_children = 0;
	u64 hash = HASHSTR_SCALAR(params.string, 0);
	u64 box_idx = get_idx_from_hash(hash);
	if (box_idx == MAX_UINT64) {
		box_idx = ui_make_box(0, params.string);
	}

	struct box *box = &gui.boxes[box_idx];
	struct layout *layout = &gui.layouts[box_idx];

	layout->padding_children = 5.0f;
	layout->margin_x = 5.0f;
	layout->margin_y = 5.0f;
	layout->grow_x.e = GROW_FIT_TEXT;
	layout->grow_y.e = GROW_FIT_TEXT;
	// layout->grow_x.v = 100.0f;
	// layout->grow_y.v = 100.0f;
	box->color = DARKBLUE;


	struct box_interaction inter = ui_interaction_from_box(box);

	if (box->is_open) {
		if (any_mbutton_pressed() && !CheckCollisionPointRec(GetMousePosition(), box->surf)) {
			box->is_open = false;
			return inter;
		}
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		layout->pos = GetMousePosition();
		box->surf.x = layout->pos.x;
		box->surf.y = layout->pos.y;
		box->is_open = true;
	}

	inter.box = box;


	assert(gui.ilt[frame_idx].ct_children == 0);
	gui.ilt[frame_idx].children[gui.ilt[frame_idx].ct_children] = box_idx;
	// printf("pushing children for frame %lu\n", frame_idx);
	gui.ilt[frame_idx].ct_children++;

	return inter;
}

struct box_interaction _ui_context_menu_elem(struct params_ui_context_menu_element params)
{
	u64 base_box_idx = gui.ct_active_frames - 1;
	u64 frame_idx = top_frame();
	u64 hash = HASHSTR_SCALAR(params.string, 0);
	u64 idx = get_idx_from_hash(hash);
	// printf("frame idx for element %lu = %lu\n", idx, base_box_idx);
	if (idx == MAX_UINT64) {
		idx = ui_make_box(
				BOX_FLAG_CLICKABLE |
				BOX_FLAG_COLLISION_HIGHLIGHT |
				BOX_FLAG_HAS_BORDER | BOX_FLAG_TEXT,
				params.string);
	}

	struct box *box = &gui.boxes[idx];
	struct box_interaction inter = ui_interaction_from_box(box);
	box->text = params.string;
	box->color = DARKGREEN;

	struct box *parent_box = &gui.boxes[gui.ilt[frame_idx].children[0]];


	if (inter.hovering && !!(box->flags & BOX_FLAG_COLLISION_HIGHLIGHT)) {
		box->color = ColorBrightness(box->color, 0.4f);
	}

	box->surf.x = parent_box->surf.x;
	box->surf.y = parent_box->surf.y;
	box->surf.width = 0.0f;
	box->surf.height = 0.0f;


	gui.ilt[frame_idx].children[gui.ilt[frame_idx].ct_children] = idx;
	gui.ilt[frame_idx].ct_children++;
	return inter;
}




void ui_context_menu_end(void)
{
	assert(gui.ct_active_frames > 0);

	u64 frame = pop_frame();

	int start = 0;
	int end = gui.ilt[frame].ct_children;
	struct layout parent_layout = gui.layouts[gui.ilt[frame].children[0]];
	struct box *parent_box = &gui.boxes[gui.ilt[frame].children[0]];

	f32 cursor_vert = parent_layout.margin_x;

	f32 cursor_horizontal = INF;


	f32 widest_text = -1.0f;
	f32 tallest_text = -1.0f;
	for (int i = 1; i < end; ++i) {
		u64 box_idx = gui.ilt[frame].children[i];
		struct box *box = &gui.boxes[box_idx];
		Vector2 text_size = MeasureTextEx(gui.txt_font, box->text.str, gui.txt_size, gui.txt_spacing);


		if (parent_layout.grow_x.e == GROW_FIT_TEXT) {
			if (widest_text < (text_size.x + parent_layout.margin_x * 2)) {
				widest_text = text_size.x + parent_layout.margin_x * 2;
			}
		} else {
			if (box->surf.width > parent_layout.grow_x.v || box->surf.width == 0) {
				widest_text = parent_layout.grow_x.v;
			}
		}

		if (parent_layout.grow_y.e == GROW_FIT_TEXT) {
			if (tallest_text < text_size.y) {
				tallest_text = text_size.y;
			}
		} else {
			if (box->surf.height > parent_layout.grow_y.v || box->surf.height == 0) {
				tallest_text = parent_layout.grow_y.v;
			}
		}
	}

	for (int i = 1; i < end; ++i) {
		u64 box_idx = gui.ilt[frame].children[i];
		struct box *box = &gui.boxes[box_idx];
		box->surf.width = widest_text;
		box->surf.height = tallest_text;

		if (cursor_horizontal > box->surf.width)
			cursor_horizontal = box->surf.width;




		box->surf.x = parent_layout.pos.x + parent_layout.margin_x;
		box->surf.y = parent_layout.pos.y + parent_layout.margin_y;

		box->surf.y += cursor_vert;
		cursor_vert += box->surf.height;
		cursor_vert += parent_layout.padding_children;
	}
	cursor_vert += parent_layout.margin_y * 2;
	cursor_horizontal += parent_layout.margin_x * 2;


	if (end > 1) {
		parent_box->surf.width =  cursor_horizontal;
		parent_box->surf.height = cursor_vert;
		// DrawRectangleRec(parent_box->surf, parent_box->color);
		DrawRectangleRounded(parent_box->surf, 0.2f, 10, parent_box->color);
		for (int i = 1; i < end; ++i) {
			u64 box_idx = gui.ilt[frame].children[i];
			struct box *box = &gui.boxes[box_idx];

			// DrawRectangleRec(box->surf, box->color);
			DrawRectangleRounded(box->surf, 0.2f, 10, box->color);
			Vector2 pos = (Vector2){box->surf.x + parent_layout.margin_x, box->surf.y};
			DrawTextEx(gui.txt_font, box->text.str, pos, gui.txt_size, gui.txt_spacing, WHITE);
		}
	}
}


enum element_sizing_type{
	SIZE_PERCENT_PARENT,
	SIZE_FIXED,
};





/*@LAYOUT_START*/
void ui_layout(void)
{
	begin_root_ctx(STR("Global Space"));
	{
		thread(0) {
			if (ui_context_menu(STR("GS Context Menu")).box->is_open) {
				if(ui_context_menu_element(STR("Elem0")).clicked) {
					printf("ELEM0\n");
				}
				if(ui_context_menu_element(STR("Elem1")).clicked) {
					printf("ELEM1\n");

				}
				if(ui_context_menu_element(STR("Elem2")).clicked) {
					printf("ELEM2\n");

				}
				if(ui_context_menu_element(STR("<Elem3>")).clicked) {
					printf("ELEM3\n");

				}
				if(ui_context_menu_element(STR("Elem4")).clicked) {
					printf("ELEM4\n");

				}

			}
			ui_context_menu_end();
		}
		thread(1) {
			/* only some top pparents rooted to the screen */
		}
		thread(2) {
			/* only some top pparents rooted to the screen */
		}
		thread(3) {
			/* only some top pparents rooted to the screen */
		}
		stc_barrier_wait(0);
	}
	end_root_ctx();
}
/*@LAYOUT_END*/

void pass0(void)
{

}


void apply_animation(int box_index, f32 delta, bool64 should_shrink, f32 target)
{
	f32 shrink_value = gui.boxes[box_index].anim_progress + (delta * 20.0f);
	f32 expand_value = gui.boxes[box_index].anim_progress - (delta * 20.0f);
	f32 transform_value_next = should_shrink ? shrink_value : expand_value;
	bool64 is_below_zero = gui.boxes[box_index].anim_progress < 0.0f;
	bool64 is_above_target = gui.boxes[box_index].anim_progress > target;
	f32 value_clamp_expand = (is_above_target) ? target : transform_value_next;
	f32 value_clamp_shrink = (is_below_zero) ? 0.0f : transform_value_next;

	gui.boxes[box_index].anim_progress = (is_above_target) ?  value_clamp_expand : value_clamp_shrink;
}



void resolve_flags(void)
{
}


/*@MAIN*/
int main(int argc, char **argv)
{
	stc_threading_group_t group0 = stc_threading_create_new_group();
	// stc_threading_group_t group1 = stc_threading_create_new_group();
	stc_threading_thread_data_for_group(group0, KILOBYTE(4), MEGABYTE(32000), 4);
	// stc_threading_thread_data_for_group(group1, KILOBYTE(2), MEGABYTE(16000), 4);
	stc_threading_system_begin();
	stc_threading_system_end();
	return 0;
}


void draw_ui(void)
{
}


/*@STORMC*/
STC_T_FUN(stormc_main, param)
{
	stc_threading_setup_thread_identity(param);

	thread_group(0) {
		thread(0) {
			InitWindow(1440, 680, "StormcVTT");
			gui.txt_size = 18;
			gui.txt_spacing = 2;
			gui.txt_font = LoadFontEx("assets/fonts/ttf/DejaVuSans.ttf", gui.txt_size, NULL, 0);
			init_boxes();
			SetTargetFPS(60);
		}
	}
	stc_barrier_wait(0);


	while (!WindowShouldClose()) {
		thread_group(0) {
			thread(0) {
				BeginDrawing();
				ClearBackground(GRAY);
			}
		}
		stc_barrier_wait(0);


		ui_layout();
		stc_barrier_wait(0);

		thread_group(0) {
			thread(0) {
				EndDrawing();
			}
		}
		stc_barrier_wait(0);
	}
	return 0;
}

