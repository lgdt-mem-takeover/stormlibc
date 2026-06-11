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
#include <math.h>
#include "stormc_base.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winitializer-overrides"
#pragma GCC diagnostic ignored "-Woverride-init"
#pragma GCC diagnostic ignored "-Woverride-init-side-effects"


#ifndef SGL_UI_MAX_QUADS
	#define SGL_UI_MAX_QUADS 16384
#endif

#ifndef SGL_VERTS_UI_CAP
	#define SGL_VERTS_UI_CAP SGL_UI_MAX_QUADS * 6
#endif

#ifndef SGL_VERTS_GLYPHS_CAP
	#define SGL_VERTS_GLYPHS_CAP SGL_UI_MAX_QUADS * 6
#endif

#ifndef SGL_VERTS_TEXTURES_CAP
	#define SGL_VERTS_TEXTURES_CAP SGL_UI_MAX_QUADS * 6
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

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

#define SGL_KEY_UNKNOWN SDL_SCANCODE_UNKNOWN
#define SGL_KEY_A SDL_SCANCODE_A
#define SGL_KEY_B SDL_SCANCODE_B
#define SGL_KEY_C SDL_SCANCODE_C
#define SGL_KEY_D SDL_SCANCODE_D
#define SGL_KEY_E SDL_SCANCODE_E
#define SGL_KEY_F SDL_SCANCODE_F
#define SGL_KEY_G SDL_SCANCODE_G
#define SGL_KEY_H SDL_SCANCODE_H
#define SGL_KEY_I SDL_SCANCODE_I
#define SGL_KEY_J SDL_SCANCODE_J
#define SGL_KEY_K SDL_SCANCODE_K
#define SGL_KEY_L SDL_SCANCODE_L
#define SGL_KEY_M SDL_SCANCODE_M
#define SGL_KEY_N SDL_SCANCODE_N
#define SGL_KEY_O SDL_SCANCODE_O
#define SGL_KEY_P SDL_SCANCODE_P
#define SGL_KEY_Q SDL_SCANCODE_Q
#define SGL_KEY_R SDL_SCANCODE_R
#define SGL_KEY_S SDL_SCANCODE_S
#define SGL_KEY_T SDL_SCANCODE_T
#define SGL_KEY_U SDL_SCANCODE_U
#define SGL_KEY_V SDL_SCANCODE_V
#define SGL_KEY_W SDL_SCANCODE_W
#define SGL_KEY_X SDL_SCANCODE_X
#define SGL_KEY_Y SDL_SCANCODE_Y
#define SGL_KEY_Z SDL_SCANCODE_Z
#define SGL_KEY_1 SDL_SCANCODE_1
#define SGL_KEY_2 SDL_SCANCODE_2
#define SGL_KEY_3 SDL_SCANCODE_3
#define SGL_KEY_4 SDL_SCANCODE_4
#define SGL_KEY_5 SDL_SCANCODE_5
#define SGL_KEY_6 SDL_SCANCODE_6
#define SGL_KEY_7 SDL_SCANCODE_7
#define SGL_KEY_8 SDL_SCANCODE_8
#define SGL_KEY_9 SDL_SCANCODE_9
#define SGL_KEY_0 SDL_SCANCODE_0
#define SGL_KEY_RETURN SDL_SCANCODE_RETURN
#define SGL_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define SGL_KEY_BACKSPACE SDL_SCANCODE_BACKSPACE
#define SGL_KEY_TAB SDL_SCANCODE_TAB
#define SGL_KEY_SPACE SDL_SCANCODE_SPACE
#define SGL_KEY_MINUS SDL_SCANCODE_MINUS
#define SGL_KEY_EQUALS SDL_SCANCODE_EQUALS
#define SGL_KEY_LEFTBRACKET SDL_SCANCODE_LEFTBRACKET
#define SGL_KEY_RIGHTBRACKET SDL_SCANCODE_RIGHTBRACKET
#define SGL_KEY_BACKSLASH SDL_SCANCODE_BACKSLASH
#define SGL_KEY_NONUSHASH SDL_SCANCODE_NONUSHASH
#define SGL_KEY_SEMICOLON SDL_SCANCODE_SEMICOLON
#define SGL_KEY_APOSTROPHE SDL_SCANCODE_APOSTROPHE
#define SGL_KEY_GRAVE SDL_SCANCODE_GRAVE
#define SGL_KEY_COMMA SDL_SCANCODE_COMMA
#define SGL_KEY_PERIOD SDL_SCANCODE_PERIOD
#define SGL_KEY_SLASH SDL_SCANCODE_SLASH
#define SGL_KEY_CAPSLOCK SDL_SCANCODE_CAPSLOCK
#define SGL_KEY_F1 SDL_SCANCODE_F1
#define SGL_KEY_F2 SDL_SCANCODE_F2
#define SGL_KEY_F3 SDL_SCANCODE_F3
#define SGL_KEY_F4 SDL_SCANCODE_F4
#define SGL_KEY_F5 SDL_SCANCODE_F5
#define SGL_KEY_F6 SDL_SCANCODE_F6
#define SGL_KEY_F7 SDL_SCANCODE_F7
#define SGL_KEY_F8 SDL_SCANCODE_F8
#define SGL_KEY_F9 SDL_SCANCODE_F9
#define SGL_KEY_F10 SDL_SCANCODE_F10
#define SGL_KEY_F11 SDL_SCANCODE_F11
#define SGL_KEY_F12 SDL_SCANCODE_F12
#define SGL_KEY_PRINTSCREEN SDL_SCANCODE_PRINTSCREEN
#define SGL_KEY_SCROLLLOCK SDL_SCANCODE_SCROLLLOCK
#define SGL_KEY_PAUSE SDL_SCANCODE_PAUSE
#define SGL_KEY_INSERT SDL_SCANCODE_INSERT
#define SGL_KEY_HOME SDL_SCANCODE_HOME
#define SGL_KEY_PAGEUP SDL_SCANCODE_PAGEUP
#define SGL_KEY_DELETE SDL_SCANCODE_DELETE
#define SGL_KEY_END SDL_SCANCODE_END
#define SGL_KEY_PAGEDOWN SDL_SCANCODE_PAGEDOWN
#define SGL_KEY_RIGHT SDL_SCANCODE_RIGHT
#define SGL_KEY_LEFT SDL_SCANCODE_LEFT
#define SGL_KEY_DOWN SDL_SCANCODE_DOWN
#define SGL_KEY_UP SDL_SCANCODE_UP
#define SGL_KEY_NUMLOCKCLEAR SDL_SCANCODE_NUMLOCKCLEAR
#define SGL_KEY_KP_DIVIDE SDL_SCANCODE_KP_DIVIDE
#define SGL_KEY_KP_MULTIPLY SDL_SCANCODE_KP_MULTIPLY
#define SGL_KEY_KP_MINUS SDL_SCANCODE_KP_MINUS
#define SGL_KEY_KP_PLUS SDL_SCANCODE_KP_PLUS
#define SGL_KEY_KP_ENTER SDL_SCANCODE_KP_ENTER
#define SGL_KEY_KP_1 SDL_SCANCODE_KP_1
#define SGL_KEY_KP_2 SDL_SCANCODE_KP_2
#define SGL_KEY_KP_3 SDL_SCANCODE_KP_3
#define SGL_KEY_KP_4 SDL_SCANCODE_KP_4
#define SGL_KEY_KP_5 SDL_SCANCODE_KP_5
#define SGL_KEY_KP_6 SDL_SCANCODE_KP_6
#define SGL_KEY_KP_7 SDL_SCANCODE_KP_7
#define SGL_KEY_KP_8 SDL_SCANCODE_KP_8
#define SGL_KEY_KP_9 SDL_SCANCODE_KP_9
#define SGL_KEY_KP_0 SDL_SCANCODE_KP_0
#define SGL_KEY_KP_PERIOD SDL_SCANCODE_KP_PERIOD
#define SGL_KEY_NONUSBACKSLASH SDL_SCANCODE_NONUSBACKSLASH
#define SGL_KEY_APPLICATION SDL_SCANCODE_APPLICATION
#define SGL_KEY_POWER SDL_SCANCODE_POWER
#define SGL_KEY_KP_EQUALS SDL_SCANCODE_KP_EQUALS
#define SGL_KEY_F13 SDL_SCANCODE_F13
#define SGL_KEY_F14 SDL_SCANCODE_F14
#define SGL_KEY_F15 SDL_SCANCODE_F15
#define SGL_KEY_F16 SDL_SCANCODE_F16
#define SGL_KEY_F17 SDL_SCANCODE_F17
#define SGL_KEY_F18 SDL_SCANCODE_F18
#define SGL_KEY_F19 SDL_SCANCODE_F19
#define SGL_KEY_F20 SDL_SCANCODE_F20
#define SGL_KEY_F21 SDL_SCANCODE_F21
#define SGL_KEY_F22 SDL_SCANCODE_F22
#define SGL_KEY_F23 SDL_SCANCODE_F23
#define SGL_KEY_F24 SDL_SCANCODE_F24
#define SGL_KEY_EXECUTE SDL_SCANCODE_EXECUTE
#define SGL_KEY_HELP SDL_SCANCODE_HELP
#define SGL_KEY_MENU SDL_SCANCODE_MENU
#define SGL_KEY_SELECT SDL_SCANCODE_SELECT
#define SGL_KEY_STOP SDL_SCANCODE_STOP
#define SGL_KEY_AGAIN SDL_SCANCODE_AGAIN
#define SGL_KEY_UNDO SDL_SCANCODE_UNDO
#define SGL_KEY_CUT SDL_SCANCODE_CUT
#define SGL_KEY_COPY SDL_SCANCODE_COPY
#define SGL_KEY_PASTE SDL_SCANCODE_PASTE
#define SGL_KEY_FIND SDL_SCANCODE_FIND
#define SGL_KEY_MUTE SDL_SCANCODE_MUTE
#define SGL_KEY_VOLUMEUP SDL_SCANCODE_VOLUMEUP
#define SGL_KEY_VOLUMEDOWN SDL_SCANCODE_VOLUMEDOWN
#define SGL_KEY_LOCKINGCAPSLOCK SDL_SCANCODE_LOCKINGCAPSLOCK
#define SGL_KEY_LOCKINGNUMLOCK SDL_SCANCODE_LOCKINGNUMLOCK
#define SGL_KEY_LOCKINGSCROLLLOCK SDL_SCANCODE_LOCKINGSCROLLLOCK
#define SGL_KEY_KP_COMMA SDL_SCANCODE_KP_COMMA
#define SGL_KEY_KP_EQUALSAS400 SDL_SCANCODE_KP_EQUALSAS400
#define SGL_KEY_INTERNATIONAL1 SDL_SCANCODE_INTERNATIONAL1
#define SGL_KEY_INTERNATIONAL2 SDL_SCANCODE_INTERNATIONAL2
#define SGL_KEY_INTERNATIONAL3 SDL_SCANCODE_INTERNATIONAL3
#define SGL_KEY_INTERNATIONAL4 SDL_SCANCODE_INTERNATIONAL4
#define SGL_KEY_INTERNATIONAL5 SDL_SCANCODE_INTERNATIONAL5
#define SGL_KEY_INTERNATIONAL6 SDL_SCANCODE_INTERNATIONAL6
#define SGL_KEY_INTERNATIONAL7 SDL_SCANCODE_INTERNATIONAL7
#define SGL_KEY_INTERNATIONAL8 SDL_SCANCODE_INTERNATIONAL8
#define SGL_KEY_INTERNATIONAL9 SDL_SCANCODE_INTERNATIONAL9
#define SGL_KEY_LANG1 SDL_SCANCODE_LANG1
#define SGL_KEY_LANG2 SDL_SCANCODE_LANG2
#define SGL_KEY_LANG3 SDL_SCANCODE_LANG3
#define SGL_KEY_LANG4 SDL_SCANCODE_LANG4
#define SGL_KEY_LANG5 SDL_SCANCODE_LANG5
#define SGL_KEY_LANG6 SDL_SCANCODE_LANG6
#define SGL_KEY_LANG7 SDL_SCANCODE_LANG7
#define SGL_KEY_LANG8 SDL_SCANCODE_LANG8
#define SGL_KEY_LANG9 SDL_SCANCODE_LANG9
#define SGL_KEY_ALTERASE SDL_SCANCODE_ALTERASE
#define SGL_KEY_SYSREQ SDL_SCANCODE_SYSREQ
#define SGL_KEY_CANCEL SDL_SCANCODE_CANCEL
#define SGL_KEY_CLEAR SDL_SCANCODE_CLEAR
#define SGL_KEY_PRIOR SDL_SCANCODE_PRIOR
#define SGL_KEY_RETURN2 SDL_SCANCODE_RETURN2
#define SGL_KEY_SEPARATOR SDL_SCANCODE_SEPARATOR
#define SGL_KEY_OUT SDL_SCANCODE_OUT
#define SGL_KEY_OPER SDL_SCANCODE_OPER
#define SGL_KEY_CLEARAGAIN SDL_SCANCODE_CLEARAGAIN
#define SGL_KEY_CRSEL SDL_SCANCODE_CRSEL
#define SGL_KEY_EXSEL SDL_SCANCODE_EXSEL
#define SGL_KEY_KP_00 SDL_SCANCODE_KP_00
#define SGL_KEY_KP_000 SDL_SCANCODE_KP_000
#define SGL_KEY_THOUSANDSSEPARATOR SDL_SCANCODE_THOUSANDSSEPARATOR
#define SGL_KEY_DECIMALSEPARATOR SDL_SCANCODE_DECIMALSEPARATOR
#define SGL_KEY_CURRENCYUNIT SDL_SCANCODE_CURRENCYUNIT
#define SGL_KEY_CURRENCYSUBUNIT SDL_SCANCODE_CURRENCYSUBUNIT
#define SGL_KEY_KP_LEFTPAREN SDL_SCANCODE_KP_LEFTPAREN
#define SGL_KEY_KP_RIGHTPAREN SDL_SCANCODE_KP_RIGHTPAREN
#define SGL_KEY_KP_LEFTBRACE SDL_SCANCODE_KP_LEFTBRACE
#define SGL_KEY_KP_RIGHTBRACE SDL_SCANCODE_KP_RIGHTBRACE
#define SGL_KEY_KP_TAB SDL_SCANCODE_KP_TAB
#define SGL_KEY_KP_BACKSPACE SDL_SCANCODE_KP_BACKSPACE
#define SGL_KEY_KP_A SDL_SCANCODE_KP_A
#define SGL_KEY_KP_B SDL_SCANCODE_KP_B
#define SGL_KEY_KP_C SDL_SCANCODE_KP_C
#define SGL_KEY_KP_D SDL_SCANCODE_KP_D
#define SGL_KEY_KP_E SDL_SCANCODE_KP_E
#define SGL_KEY_KP_F SDL_SCANCODE_KP_F
#define SGL_KEY_KP_XOR SDL_SCANCODE_KP_XOR
#define SGL_KEY_KP_POWER SDL_SCANCODE_KP_POWER
#define SGL_KEY_KP_PERCENT SDL_SCANCODE_KP_PERCENT
#define SGL_KEY_KP_LESS SDL_SCANCODE_KP_LESS
#define SGL_KEY_KP_GREATER SDL_SCANCODE_KP_GREATER
#define SGL_KEY_KP_AMPERSAND SDL_SCANCODE_KP_AMPERSAND
#define SGL_KEY_KP_DBLAMPERSAND SDL_SCANCODE_KP_DBLAMPERSAND
#define SGL_KEY_KP_VERTICALBAR SDL_SCANCODE_KP_VERTICALBAR
#define SGL_KEY_KP_DBLVERTICALBAR SDL_SCANCODE_KP_DBLVERTICALBAR
#define SGL_KEY_KP_COLON SDL_SCANCODE_KP_COLON
#define SGL_KEY_KP_HASH SDL_SCANCODE_KP_HASH
#define SGL_KEY_KP_SPACE SDL_SCANCODE_KP_SPACE
#define SGL_KEY_KP_AT SDL_SCANCODE_KP_AT
#define SGL_KEY_KP_EXCLAM SDL_SCANCODE_KP_EXCLAM
#define SGL_KEY_KP_MEMSTORE SDL_SCANCODE_KP_MEMSTORE
#define SGL_KEY_KP_MEMRECALL SDL_SCANCODE_KP_MEMRECALL
#define SGL_KEY_KP_MEMCLEAR SDL_SCANCODE_KP_MEMCLEAR
#define SGL_KEY_KP_MEMADD SDL_SCANCODE_KP_MEMADD
#define SGL_KEY_KP_MEMSUBTRACT SDL_SCANCODE_KP_MEMSUBTRACT
#define SGL_KEY_KP_MEMMULTIPLY SDL_SCANCODE_KP_MEMMULTIPLY
#define SGL_KEY_KP_MEMDIVIDE SDL_SCANCODE_KP_MEMDIVIDE
#define SGL_KEY_KP_PLUSMINUS SDL_SCANCODE_KP_PLUSMINUS
#define SGL_KEY_KP_CLEAR SDL_SCANCODE_KP_CLEAR
#define SGL_KEY_KP_CLEARENTRY SDL_SCANCODE_KP_CLEARENTRY
#define SGL_KEY_KP_BINARY SDL_SCANCODE_KP_BINARY
#define SGL_KEY_KP_OCTAL SDL_SCANCODE_KP_OCTAL
#define SGL_KEY_KP_DECIMAL SDL_SCANCODE_KP_DECIMAL
#define SGL_KEY_KP_HEXADECIMAL SDL_SCANCODE_KP_HEXADECIMAL
#define SGL_KEY_LCTRL SDL_SCANCODE_LCTRL
#define SGL_KEY_LSHIFT SDL_SCANCODE_LSHIFT
#define SGL_KEY_LALT SDL_SCANCODE_LALT
#define SGL_KEY_LGUI SDL_SCANCODE_LGUI
#define SGL_KEY_RCTRL SDL_SCANCODE_RCTRL
#define SGL_KEY_RSHIFT SDL_SCANCODE_RSHIFT
#define SGL_KEY_RALT SDL_SCANCODE_RALT
#define SGL_KEY_RGUI SDL_SCANCODE_RGUI
#define SGL_KEY_MODE SDL_SCANCODE_MODE
#define SGL_KEY_SLEEP SDL_SCANCODE_SLEEP
#define SGL_KEY_WAKE SDL_SCANCODE_WAKE
#define SGL_KEY_CHANNEL_INCREMENT SDL_SCANCODE_CHANNEL_INCREMENT
#define SGL_KEY_CHANNEL_DECREMENT SDL_SCANCODE_CHANNEL_DECREMENT
#define SGL_KEY_MEDIA_PLAY SDL_SCANCODE_MEDIA_PLAY
#define SGL_KEY_MEDIA_PAUSE SDL_SCANCODE_MEDIA_PAUSE
#define SGL_KEY_MEDIA_RECORD SDL_SCANCODE_MEDIA_RECORD
#define SGL_KEY_MEDIA_FAST_FORWARD SDL_SCANCODE_MEDIA_FAST_FORWARD
#define SGL_KEY_MEDIA_REWIND SDL_SCANCODE_MEDIA_REWIND
#define SGL_KEY_MEDIA_NEXT_TRACK SDL_SCANCODE_MEDIA_NEXT_TRACK
#define SGL_KEY_MEDIA_PREVIOUS_TRACK SDL_SCANCODE_MEDIA_PREVIOUS_TRACK
#define SGL_KEY_MEDIA_STOP SDL_SCANCODE_MEDIA_STOP
#define SGL_KEY_MEDIA_EJECT SDL_SCANCODE_MEDIA_EJECT
#define SGL_KEY_MEDIA_PLAY_PAUSE SDL_SCANCODE_MEDIA_PLAY_PAUSE
#define SGL_KEY_MEDIA_SELECT SDL_SCANCODE_MEDIA_SELECT
#define SGL_KEY_AC_NEW SDL_SCANCODE_AC_NEW
#define SGL_KEY_AC_OPEN SDL_SCANCODE_AC_OPEN
#define SGL_KEY_AC_CLOSE SDL_SCANCODE_AC_CLOSE
#define SGL_KEY_AC_EXIT SDL_SCANCODE_AC_EXIT
#define SGL_KEY_AC_SAVE SDL_SCANCODE_AC_SAVE
#define SGL_KEY_AC_PRINT SDL_SCANCODE_AC_PRINT
#define SGL_KEY_AC_PROPERTIES SDL_SCANCODE_AC_PROPERTIES
#define SGL_KEY_AC_SEARCH SDL_SCANCODE_AC_SEARCH
#define SGL_KEY_AC_HOME SDL_SCANCODE_AC_HOME
#define SGL_KEY_AC_BACK SDL_SCANCODE_AC_BACK
#define SGL_KEY_AC_FORWARD SDL_SCANCODE_AC_FORWARD
#define SGL_KEY_AC_STOP SDL_SCANCODE_AC_STOP
#define SGL_KEY_AC_REFRESH SDL_SCANCODE_AC_REFRESH
#define SGL_KEY_AC_BOOKMARKS SDL_SCANCODE_AC_BOOKMARKS
#define SGL_KEY_SOFTLEFT SDL_SCANCODE_SOFTLEFT
#define SGL_KEY_SOFTRIGHT SDL_SCANCODE_SOFTRIGHT
#define SGL_KEY_CALL SDL_SCANCODE_CALL
#define SGL_KEY_ENDCALL SDL_SCANCODE_ENDCALL
#define SGL_KEY_RESERVED SDL_SCANCODE_RESERVED
#define SGL_KEY_COUNT SDL_SCANCODE_COUNT

enum sgl_mouse_button_flags {
	SGL_MOUSEF_LDOWN = 1ull << 0,
	SGL_MOUSEF_LPRESS = 1ull << 1,
	SGL_MOUSEF_LRELEASE = 1ull << 2,

	SGL_MOUSEF_RDOWN = 1ull << 3,
	SGL_MOUSEF_RPRESS = 1ull << 4,
	SGL_MOUSEF_RRELEASE = 1ull << 5,

	SGL_MOUSEF_MDOWN = 1ull << 6,
	SGL_MOUSEF_MPRESS = 1ull << 7,
	SGL_MOUSEF_MRELEASE = 1ull << 8,
};


enum sgl_mouse_button {
	SGL_MOUSE_LEFT,
	SGL_MOUSE_RIGHT,
	SGL_MOUSE_MIDDLE,
};

enum sgl_pipeline_type{
	SGL_PIPELINE_UI,
	SGL_PIPELINE_TEX,
	SGL_PIPELINE_GLYPHS,
	SGL_PIPELINE_TEX_GENERIC,
	SGL_PIPELINE_CT
};

struct sgl_sprite {
	u32 x, y, w, h;
	f32 u0, v0, u1, v1;
};

struct sgl_texture{
	u32	gl_id;
	f32	w;
	f32	h;
	u8	*data;
};

struct sgl_atlas_entry {
	struct stc_string8 name;
	u32 x, y, w, h;
	f32 u0, v0, u1, v1;
};

struct sgl_atlas {
	struct sgl_texture texture;
	struct sgl_atlas_entry *entries;
	u32 count_entries;
	u32 w, h;
};
struct color {
	f32 r, g, b, a;
};



struct sgl_mouse {
	f32	x, y;
	f32	dx, dy;
	f32	wheel_x, wheel_y;
	u64	flags;
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

	// bool mouse_pressed[8];
	// bool mouse_released[8];

	f32	mouse_x;
	f32 	mouse_y;
	f32	mouse_dx;
	f32	mouse_dy;
	f32 	mouse_wheel_x;
	f32 	mouse_wheel_y;
	u64	mouse_mask;

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
	enum sgl_pipeline_type	current_pipeline;
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
			.ui_max_quads = SGL_VERTS_UI_CAP,
			.ui_max_vertices = SGL_VERTS_UI_CAP * 4,
			.txt_size_max = 48,
			.txt_font = (u8 *)FONT_PATH_DEJAVU_SANS,
		},
		.textures_generic = {
			.max_textures_generic = SGL_VERTS_TEXTURES_CAP,
		},
		.ui_softness_default = 1.0f,
		.vsync = true,
	},
};





/*@FUNCS SIGNATURES*/
static void sgl_init(int window_width, int window_height, struct stc_string8 window_name);
static void _sgl_create_pipeline(enum sgl_pipeline_type pipeline_type);
static void sgl_scissor_begin(f32 x, f32 y, f32 w, f32 h);
static void sgl_scissor_end(void);
static void sgl_draw_sprite(struct sgl_texture texture, struct sgl_sprite sprite, f32 x, f32 y, f32 w, f32 h, struct color color);
static void sgl_draw_texture_region(struct sgl_texture texture, f32 x, f32 y, f32 w, f32 h, f32 u0, f32 v0, f32 u1, f32 v1, struct color color);
static struct sgl_atlas sgl_make_atlas(struct sgl_texture *textures, u32 count, u32 atlas_w, u32 atlas_h, u32 pad);
void sgl_start_text_input(void);
void sgl_stop_text_input(void);
static inline struct sgl_mouse sgl_get_mouse(void);
static inline u32  sgl_files_dropped_count(void);
static inline bool32 sgl_any_text_input(void);
static inline bool32 sgl_is_mouse_in_rect(struct rect r);
static inline bool32 sgl_has_keyboard_focus(void);
static inline bool32 sgl_has_mouse_focus(void);
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
static inline void sgl_flush_current_pipeline(void);
static inline void sgl_touch_pipeline(enum sgl_pipeline_type next);
static inline void sgl_input_begin_frame(void);
static inline void sgl_input_init(void);
static inline void sgl_poll_input(void);
// static inline f32 sgl_mouse_dx(void);
// static inline f32 sgl_mouse_dy(void);
// static inline struct vec2 sgl_mouse_delta(void);
// static inline struct vec2 sgl_mouse_pos(void);
static inline bool32 sgl_items_dropped(void);
static struct sgl_texture sgl_load_texture(const char *path);
static inline const char *sgl_dropped_path(u32 index);
static void sgl_draw_texture(struct sgl_texture texture, f32 x, f32 y, f32 w, f32 h, struct color color);
static inline void sgl_clear_batch(enum sgl_pipeline_type type);
static inline bool32 sgl_is_mouse_down(i32);
static inline bool32 sgl_is_mouse_pressed(i32);
static inline bool32 sgl_is_mouse_released(i32);
static inline u64 sgl_mouse_flag(i32 button, u64 l, u64 r, u64 m);
static inline bool32 sgl_mouse_left_pressed(struct sgl_mouse m);
static inline bool32 sgl_mouse_left_down(struct sgl_mouse m);
static inline bool32 sgl_mouse_left_released(struct sgl_mouse m);
static inline bool32 sgl_mouse_right_pressed(struct sgl_mouse m);
static inline bool32 sgl_mouse_right_down(struct sgl_mouse m);
static inline bool32 sgl_mouse_right_released(struct sgl_mouse m);

void sgl_draw_sprite(
    struct sgl_texture texture,
    struct sgl_sprite sprite,
    f32 x, f32 y,
    f32 w, f32 h,
    struct color color)
{
    sgl_draw_texture_region(
        texture,
        x, y, w, h,
        sprite.u0, sprite.v0,
        sprite.u1, sprite.v1,
        color
    );
}


void
sgl_draw_texture_region(
    struct sgl_texture texture,
    f32 x, f32 y,
    f32 w, f32 h,
    f32 u0, f32 v0,
    f32 u1, f32 v1,
    struct color color)
{
	if (texture.gl_id == 0) return;

	sgl_touch_pipeline(SGL_PIPELINE_TEX_GENERIC);

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
		.uv = {u0, v0},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x + w, y, 0.0f},
		.color = color,
		.uv = {u1, v0},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x + w, y + h, 0.0f},
		.color = color,
		.uv = {u1, v1},
	};
	sgl.textures_generic.vertices[sgl.textures_generic.ct_vertices++] = (struct vertex_tex_generic){
		.pos = {x, y + h, 0.0f},
		.color = color,
		.uv = {u0, v1},
	};

	sgl.textures_generic.ct_quads++;
}

struct sgl_atlas
sgl_make_atlas(
    struct sgl_texture *textures,
    u32 count,
    u32 atlas_w,
    u32 atlas_h,
    u32 pad)
{
	struct sgl_atlas atlas = {0};
	if (!textures || count == 0) return atlas;

	stbrp_context ctx = {0};
	stbrp_node *nodes = stc_alloc(sizeof(*nodes) * atlas_w);
	stbrp_rect *rects = stc_alloc(sizeof(*rects) * count);
	atlas.entries = stc_alloc(sizeof(*atlas.entries) * count);

	if (!nodes || !rects || !atlas.entries) {
		fprintf(stderr, "atlas alloc failed\n");
		goto fail;
	}

	for (u32 i = 0; i < count; ++i) {
		rects[i].id = (int)i;
		rects[i].w = (stbrp_coord)(textures[i].w + pad * 2);
		rects[i].h = (stbrp_coord)(textures[i].h + pad * 2);
	}

	stbrp_init_target(&ctx, (int)atlas_w, (int)atlas_h, nodes, (int)atlas_w);
	if (!stbrp_pack_rects(&ctx, rects, (int)count)) {
		fprintf(stderr, "atlas packing failed\n");
		goto fail;
	}

	u8 *pixels = calloc((size_t)atlas_w * (size_t)atlas_h * 4, 1);
	if (!pixels) {
		fprintf(stderr, "atlas pixel alloc failed\n");
		goto fail;
	}

	for (u32 i = 0; i < count; ++i) {
		if (!rects[i].was_packed) {
			fprintf(stderr, "sprite %u did not fit atlas\n", i);
			free(pixels);
			goto fail;
		}

		u32 dst_x = (u32)rects[i].x + pad;
		u32 dst_y = (u32)rects[i].y + pad;
		u32 src_w = (u32)textures[i].w;
		u32 src_h = (u32)textures[i].h;

		/* requires textures[i].data to exist */
		for (u32 row = 0; row < src_h; ++row) {
			u8 *dst = pixels + (((size_t)dst_y + row) * atlas_w + dst_x) * 4;
			u8 *src = textures[i].data + ((size_t)row * src_w) * 4;
			stc_memcpy(dst, src, (size_t)src_w * 4);
		}

		atlas.entries[i] = (struct sgl_atlas_entry){
			.x = dst_x,
			.y = dst_y,
			.w = src_w,
			.h = src_h,
			.u0 = (f32)dst_x / (f32)atlas_w,
			.v0 = (f32)dst_y / (f32)atlas_h,
			.u1 = (f32)(dst_x + src_w) / (f32)atlas_w,
			.v1 = (f32)(dst_y + src_h) / (f32)atlas_h,
		};
	}

	atlas.w = atlas_w;
	atlas.h = atlas_h;
	atlas.count_entries = count;

	glGenTextures(1, &atlas.texture.gl_id);
	glBindTexture(GL_TEXTURE_2D, atlas.texture.gl_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, atlas_w, atlas_h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	atlas.texture.w = (f32)atlas_w;
	atlas.texture.h = (f32)atlas_h;

	free(pixels);
	stc_free(nodes, sizeof(*nodes) * atlas_w);
	stc_free(rects, sizeof(*rects) * count);
	return atlas;

fail:
	if (nodes) stc_free(nodes, sizeof(*nodes) * atlas_w);
	if (rects) stc_free(rects, sizeof(*rects) * count);
	if (atlas.entries) stc_free(atlas.entries, sizeof(*atlas.entries) * count);
	atlas.entries = NULL;
	return atlas;
}


struct sgl_sprite
sgl_sprite_from_grid(struct sgl_texture tex, u32 cols, u32 rows, u32 frame)
{
	u32 cell_w = (u32)tex.w / cols;
	u32 cell_h = (u32)tex.h / rows;

	u32 col = frame % cols;
	u32 row = frame / cols;

	u32 x = col * cell_w;
	u32 y = row * cell_h;

	return (struct sgl_sprite){
		.x = x,
		.y = y,
		.w = cell_w,
		.h = cell_h,
		.u0 = (f32)x / tex.w,
		.v0 = (f32)y / tex.h,
		.u1 = (f32)(x + cell_w) / tex.w,
		.v1 = (f32)(y + cell_h) / tex.h,
	};
}

f64 sgl_get_dt(void)
{
	static u64 last_counter = 0;
	u64 counter = SDL_GetPerformanceCounter();
	u64 freq = SDL_GetPerformanceFrequency();

	f64 dt = 0.0f;

	if (last_counter != 0) {
		dt = (f64)(counter - last_counter) / (f64)freq;
	}

	last_counter = counter;
	return dt;
}


void sgl_start_text_input(void)
{
	SDL_StartTextInput(sgl.window);
}

void sgl_stop_text_input(void)
{
	SDL_StopTextInput(sgl.window);
}


static inline bool32 sgl_mouse_left_pressed(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_LPRESS) != 0;
}

static inline bool32 sgl_mouse_left_down(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_LDOWN) != 0;
}

static inline bool32 sgl_mouse_left_released(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_LRELEASE) != 0;
}

static inline bool32 sgl_mouse_right_pressed(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_RPRESS) != 0;
}



static inline bool32 sgl_mouse_right_down(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_RDOWN) != 0;
}

static inline bool32 sgl_mouse_right_released(struct sgl_mouse m)
{
	return (m.flags & SGL_MOUSEF_RRELEASE) != 0;
}





/*@MOUSE_STARt*/
static inline u64
sgl_mouse_flag(i32 button, u64 l, u64 r, u64 m)
{
	switch (button) {
	case SDL_BUTTON_LEFT:   return l;
	case SDL_BUTTON_RIGHT:  return r;
	case SDL_BUTTON_MIDDLE: return m;
	default: return 0;
	}
}

static inline bool32
sgl_is_mouse_down(i32 button)
{
	return (sgl.sgl_input.mouse_mask &
	        sgl_mouse_flag(button,
	                       SGL_MOUSEF_LDOWN,
	                       SGL_MOUSEF_RDOWN,
	                       SGL_MOUSEF_MDOWN)) != 0;
}

static inline bool32
sgl_is_mouse_pressed(i32 button)
{
	return (sgl.sgl_input.mouse_mask &
	        sgl_mouse_flag(button,
	                       SGL_MOUSEF_LPRESS,
	                       SGL_MOUSEF_RPRESS,
	                       SGL_MOUSEF_MPRESS)) != 0;
}

static inline bool32
sgl_is_mouse_released(i32 button)
{
	return (sgl.sgl_input.mouse_mask &
	        sgl_mouse_flag(button,
	                       SGL_MOUSEF_LRELEASE,
	                       SGL_MOUSEF_RRELEASE,
	                       SGL_MOUSEF_MRELEASE)) != 0;
}


// static inline f32
// sgl_mouse_x(void)
// {
// 	return sgl.sgl_input.mouse_x;
// }
//
// static inline f32
// sgl_mouse_y(void)
// {
// 	return sgl.sgl_input.mouse_y;
// }
//
// static inline f32
// sgl_mouse_wheel_x(void)
// {
// 	return sgl.sgl_input.mouse_wheel_x;
// }
//
// static inline f32
// sgl_mouse_wheel_y(void)
// {
// 	return sgl.sgl_input.mouse_wheel_y;
// }


static inline struct sgl_mouse
sgl_get_mouse(void)
{
	return (struct sgl_mouse){
		.x = sgl.sgl_input.mouse_x,
		.y = sgl.sgl_input.mouse_y,
		.dx = sgl.sgl_input.mouse_dx,
		.dy = sgl.sgl_input.mouse_dy,
		.wheel_x = sgl.sgl_input.mouse_wheel_x,
		.wheel_y = sgl.sgl_input.mouse_wheel_y,
		.flags = sgl.sgl_input.mouse_mask,
	};
}
/*@MOUSE_END*/


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

void sgl_build_text_atlas(int first_char, int last_char)
{
	FT_Face face = sgl.cfg_init_time.ui.ft_face;
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
		sgl.glyphs.atlas = atlas;
	}

	atlas.width  = atlas_w;
	atlas.height = atlas_h;
	atlas.ascent = (f32)(face->size->metrics.ascender >> 6);
	atlas.line_height = (f32)(face->size->metrics.height >> 6);

	u8 *pixels = calloc((size_t)atlas.width * (size_t)atlas.height, 1);
	if (!pixels) {
		fprintf(stderr, "atlas pixel alloc failed\n");
		sgl.glyphs.atlas = atlas;
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

	sgl.glyphs.atlas = atlas;
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
	u64 commit = sizeof(struct quad) * SGL_UI_MAX_QUADS;
	if (stc_commit(sgl.ui.quads, commit) == NULL) {
		perror("mprotect");
		exit(1);
	}
	sgl.ui.cmted_bytes_quads = commit;
	sgl.ui.quads_cap = SGL_UI_MAX_QUADS;


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
	sgl.glyphs.verts_cap = SGL_VERTS_GLYPHS_CAP;
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
	sgl.ui.verts_cap = SGL_VERTS_UI_CAP;
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



static const char *sgl_default_font_candidates[] = {
	FONT_PATH_DEJAVU_SANS,
	"assets/ttf/DejaVuSans.ttf",
	"assets/fonts/ttf/DejaVuSans.ttf",
	"../assets/ttf/DejaVuSans.ttf",
	"../assets/fonts/ttf/DejaVuSans.ttf",
};

bool32 sgl_try_load_font(const char *path)
{
	if (path == NULL) {
		return false;
	}

	if (FT_New_Face(sgl.cfg_init_time.ui.ft_lib, path, 0, &sgl.cfg_init_time.ui.ft_face) == 0) {
		sgl.cfg_init_time.ui.txt_font = (u8 *)path;
		return true;
	}

	return false;
}

bool32 sgl_try_load_font_from_stormlibc_assets(void)
{
	static char path[4096];
	const char *source_path = __FILE__;
	const char *suffix = "../assets/ttf/DejaVuSans.ttf";
	u64 source_dir_len = 0;
	u64 suffix_len = 0;

	for (u64 i = 0; source_path[i] != 0; ++i) {
		if (source_path[i] == '/' || source_path[i] == '\\') {
			source_dir_len = i + 1;
		}
	}

	if (source_dir_len == 0) {
		return false;
	}

	while (suffix[suffix_len] != 0) {
		++suffix_len;
	}

	if (source_dir_len + suffix_len + 1 > STC_ARRCOUNT(path)) {
		return false;
	}

	stc_memcpy(path, source_path, source_dir_len);
	stc_memcpy(path + source_dir_len, suffix, suffix_len);
	path[source_dir_len + suffix_len] = 0;

	return sgl_try_load_font(path);
}

void sgl_init_freetype(void)
{
	if (FT_Init_FreeType(&sgl.cfg_init_time.ui.ft_lib))
	{
		fprintf(stderr, "Could not init FreeType Library");
		exit(1);
	}

	if (!sgl_try_load_font((const char *)sgl.cfg_init_time.ui.txt_font)) {
		for (u64 i = 0; i < STC_ARRCOUNT(sgl_default_font_candidates); ++i) {
			if (sgl_try_load_font(sgl_default_font_candidates[i])) {
				goto font_loaded;
			}
		}

		if (sgl_try_load_font_from_stormlibc_assets()) {
			goto font_loaded;
		}

		fprintf(stderr, "Failed to load font. Tried:\n");
		fprintf(stderr, "  %s\n", (const char *)sgl.cfg_init_time.ui.txt_font);
		for (u64 i = 0; i < STC_ARRCOUNT(sgl_default_font_candidates); ++i) {
			fprintf(stderr, "  %s\n", sgl_default_font_candidates[i]);
		}
		fprintf(stderr, "  <stormlibc source dir>/../assets/ttf/DejaVuSans.ttf\n");
		exit(1);
	}

font_loaded:
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
	sgl.ww = window_width;
	sgl.wh = window_height;

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

	_sgl_create_pipeline(SGL_PIPELINE_UI);
	_sgl_create_pipeline(SGL_PIPELINE_GLYPHS);
	_sgl_create_pipeline(SGL_PIPELINE_TEX_GENERIC);
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

	if (params.ct_attribs < 0 || params.ct_attribs > SGL_MAX_ATTRIBS) {
		stc_println_err("SGL shader attribute count {u32} exceeds {u32}",
			params.ct_attribs, SGL_MAX_ATTRIBS);
		exit(1);
	}

	FILE *vertf = fopen((const char *)params.vert_filepath.str, "rb");
	if (!vertf) {
		stc_println_err("Failed to open {string}", params.vert_filepath);
		stc_exit(1);
	}
	if(fseek(vertf, 0, SEEK_END) != 0) {
		perror("fseek");
		stc_exit(1);
	}
	i32 len_shader_vert = ftell(vertf);
	if (len_shader_vert < 0) {
		perror("ftell");
		stc_exit(1);
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



void sgl_draw_ui_box(struct ui_box r)
{
	sgl_touch_pipeline(SGL_PIPELINE_UI);

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






void _sgl_create_pipeline(enum sgl_pipeline_type pipeline_type)
{
	struct stc_strbldr temp = stc_strbldr_emit(1llu << 22, 4096);
	struct stc_string8 path_vs = {};
	struct stc_string8 path_fs = {};
	stc_global_stack_start();
	path_vs.str = stc_global_alloc(char, 4096);
	path_fs.str = stc_global_alloc(char, 4096);
	switch (pipeline_type) {
	default:
		fprintf(stderr, "Unknown Pipeline Type Code: %d", pipeline_type);
		exit(1);
	case SGL_PIPELINE_UI:
		stc_strbldr_append(&temp, "{cstring}/base/ui_vert_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_vs.str, temp.ptr, temp.off);
		stc_strbldr_reset(&temp);
		stc_strbldr_append(&temp, "{cstring}/base/ui_frag_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_fs.str, temp.ptr, temp.off);
		sgl_init_vertices_ui();
		sgl_init_quads_ui();
		sgl.ui.pipeline = sgl_make_pipeline(
		    .vert_filepath = path_vs,
		    .frag_filepath = path_fs,
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
		stc_strbldr_append(&temp, "{cstring}/base/glyph_vert_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_vs.str, temp.ptr, temp.off);
		stc_strbldr_reset(&temp);
		stc_strbldr_append(&temp, "{cstring}/base/glyph_frag_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_fs.str, temp.ptr, temp.off);

		sgl_init_vertices_glyphs();

		sgl.glyphs.pipeline = sgl_make_pipeline(
		    .vert_filepath = path_vs,
		    .frag_filepath = path_fs,

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
		/*BUILD ATLAS TOGETHER WITH GLYPHS*/
		sgl_build_text_atlas(32, 127);
		break;
	case SGL_PIPELINE_TEX:
		break;
	case SGL_PIPELINE_TEX_GENERIC:
		stc_strbldr_append(&temp, "{cstring}/base/tex_generic_vert_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_vs.str, temp.ptr, temp.off);
		stc_strbldr_reset(&temp);
		stc_strbldr_append(&temp, "{cstring}/base/tex_generic_frag_shader.glsl", STORMC_ROOT);
		stc_memcpy(path_fs.str, temp.ptr, temp.off);

		sgl_init_vertices_texture_generic();
		sgl_init_quads_texture_generic();
		sgl.textures_generic.pipeline = sgl_make_pipeline(
		    .vert_filepath = path_vs,
		    .frag_filepath = path_fs,

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
		    .ct_attribs = 3,);
		break;
	}
	stc_global_stack_end();
	stc_strbldr_free(&temp);
}


void sgl_draw_text(struct stc_string8 text, f32 x, f32 y, f32 size, struct color color)
{
	if (!text.str || text.len == 0) {
		return;
	}

	sgl_touch_pipeline(SGL_PIPELINE_GLYPHS);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_SCISSOR_TEST);
	sgl.current_pipeline = SGL_PIPELINE_CT;
}

void sgl_scissor_begin(f32 x, f32 y, f32 w, f32 h)
{
	sgl_flush_current_pipeline();

	glEnable(GL_SCISSOR_TEST);

	i32 sx = (i32)x;
	i32 sy = sgl.wh - (i32)(y + h); /* top-left UI -> bottom-left GL */
	i32 sw = (i32)w;
	i32 sh = (i32)h;

	glScissor(sx, sy, sw, sh);
}

void sgl_scissor_end(void)
{
	sgl_flush_current_pipeline();

	glDisable(GL_SCISSOR_TEST);
}


static inline void sgl_clear_batch(enum sgl_pipeline_type type)
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


static inline void sgl_flush_current_pipeline(void)
{
	if (sgl.current_pipeline == SGL_PIPELINE_CT) {
		return;
	}

	sgl_dispatch_pipeline(sgl.current_pipeline);
	sgl.current_pipeline = SGL_PIPELINE_CT;
}


static inline void sgl_touch_pipeline(enum sgl_pipeline_type next)
{
	if (sgl.current_pipeline != SGL_PIPELINE_CT &&
	    sgl.current_pipeline != next) {
		sgl_dispatch_pipeline(sgl.current_pipeline);
	}

	sgl.current_pipeline = next;
}


static inline void sgl_dispatch_pipeline(enum sgl_pipeline_type pipeline_type)
{

	switch (pipeline_type) {
	default:
		fprintf(stderr, "Unknown Pipeline Type Code: %d", pipeline_type);
		exit(1);
	case SGL_PIPELINE_UI:
	{
		if (sgl.ui.ct_quads == 0) goto exit;
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
		if (sgl.glyphs.ct_vertices == 0) goto exit;
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
		if (sgl.textures.ct_vertices == 0) goto exit;
		struct sgl_pipeline *textures = &sgl.textures.pipeline;
		break;
	}
	case SGL_PIPELINE_TEX_GENERIC:
	{
		if (sgl.textures_generic.ct_quads == 0) goto exit;
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
exit:
	sgl_clear_batch(pipeline_type);
}


void sgl_end_draw(void)
{
	sgl_flush_current_pipeline();

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

	sgl.sgl_input.mouse_wheel_x = 0.0f;
	sgl.sgl_input.mouse_wheel_y = 0.0f;
	sgl.sgl_input.files_drop_count = 0;
	sgl.sgl_input.mouse_mask = 0;
	// sgl.sgl_input.text_data_len = 0;
	// sgl.sgl_input.text_data[0] = '\0';

	Uint32 down = SDL_GetMouseState(&sgl.sgl_input.mouse_x, &sgl.sgl_input.mouse_y);
	SDL_GetRelativeMouseState(&sgl.sgl_input.mouse_dx, &sgl.sgl_input.mouse_dy);

	if (down & SDL_BUTTON_MASK(SDL_BUTTON_LEFT))   sgl.sgl_input.mouse_mask |= SGL_MOUSEF_LDOWN;
	if (down & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT))  sgl.sgl_input.mouse_mask |= SGL_MOUSEF_RDOWN;
	if (down & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE)) sgl.sgl_input.mouse_mask |= SGL_MOUSEF_MDOWN;
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
		switch (sgl.events.button.button) {
		case SDL_BUTTON_LEFT:   sgl.sgl_input.mouse_mask |= SGL_MOUSEF_LPRESS; break;
		case SDL_BUTTON_RIGHT:  sgl.sgl_input.mouse_mask |= SGL_MOUSEF_RPRESS; break;
		case SDL_BUTTON_MIDDLE: sgl.sgl_input.mouse_mask |= SGL_MOUSEF_MPRESS; break;
	}
	break;

	case SDL_EVENT_MOUSE_BUTTON_UP:
		switch (sgl.events.button.button) {
		case SDL_BUTTON_LEFT:   sgl.sgl_input.mouse_mask |= SGL_MOUSEF_LRELEASE; break;
		case SDL_BUTTON_RIGHT:  sgl.sgl_input.mouse_mask |= SGL_MOUSEF_RRELEASE; break;
		case SDL_BUTTON_MIDDLE: sgl.sgl_input.mouse_mask |= SGL_MOUSEF_MRELEASE; break;
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
		if (path == NULL) {
			break;
		}

		u64 path_len = sstrlenx((const  u8*)path);
		if (sgl.sgl_input.files_drop_count < SGL_MAX_DROPS) {
			u32 drop_idx = sgl.sgl_input.files_drop_count;
			u64 path_cap = sizeof(sgl.sgl_input.files_dropped_paths[drop_idx]);
			if (path_len >= path_cap) {
				fprintf(stderr, "Dropped file path exceeds %llu bytes\n", (unsigned long long)(path_cap - 1));
				break;
			}

			stc_memcpy(sgl.sgl_input.files_dropped_paths[drop_idx], path, path_len);
			sgl.sgl_input.files_dropped_paths[drop_idx][path_len] = '\0';
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



static inline i32  sgl_window_width(void)  { return sgl.ww; }
static inline i32  sgl_window_height(void) { return sgl.wh; }
static inline bool32 sgl_running(void)     { return sgl.running; }

static inline u64  sgl_text_input_len(void) { return sgl.sgl_input.text_data_len; }
static inline const char *sgl_text_input_data(void) { return sgl.sgl_input.text_data; }

static inline u32  sgl_files_dropped_count(void) { return sgl.sgl_input.files_drop_count; }


static inline bool32 sgl_any_text_input(void)
{
	return sgl.sgl_input.text_data_len > 0;
}

static inline bool32 sgl_is_mouse_in_rect(struct rect r)
{
	return sgl_col_rec_point(r, (struct vec2){sgl.sgl_input.mouse_x, sgl.sgl_input.mouse_y});
}

static inline bool32 sgl_has_keyboard_focus(void)
{
	return SDL_GetKeyboardFocus() == sgl.window;
}

static inline bool32 sgl_has_mouse_focus(void)
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

	stc_memcpy(s->str + s->len, sgl.sgl_input.text_data, n);
	s->len += n;
	s->str[s->len] = '\0';

	sgl.sgl_input.text_data_len = 0;
	sgl.sgl_input.text_data[0] = '\0';
}

void sgl_draw_circle(f32 cx, f32 cy, f32 radius, struct color c)
{
	f32 d = radius * 2.0f;

	sgl_draw_ui_box((struct ui_box){
		.x = cx - radius,
		.y = cy - radius,
		.w = d,
		.h = d,
		.color = c,
		.radius = d * 0.5f,
		.border_thickness = 0.0f,
		.border_color = SGL_WHITE100
	});
}

void sgl_draw_circle_ex(
	f32 cx, f32 cy, f32 radius,
	struct color fill,
	f32 border_thickness,
	struct color border_color)
{
	f32 x = cx - radius;
	f32 y = cy - radius;
	f32 d = radius * 2.0f;

	sgl_draw_ui_box((struct ui_box){
		.x = x,
		.y = y,
		.w = d,
		.h = d,
		.color = fill,
		.radius = radius,
		.border_thickness = border_thickness,
		.border_color = border_color,
	});
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


static inline bool32 sgl_items_dropped(void)
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

	u64 size = (u64)w * (u64)h * 4;
	tex.data = stc_alloc(size);
	stc_memcpy(tex.data, data, size);

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



static inline const char *sgl_dropped_path(u32 index)
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
	sgl_draw_texture_region(texture, x, y, w, h, 0.0f, 0.0f, 1.0f, 1.0f, color);
}
