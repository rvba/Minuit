/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#ifndef __EVENT_H
#define __EVENT_H

#define EVENT_WITH_POLYGON_OFFSET 0
#define SKETCH_WITH_SCALE 1

#define CTX_SHOW_TERM 1
#define CTX_FIXED_BUTTON 0
#define CTX_DEBUG_MOUSE 0
#define CTX_DEBUG_SELECT 0

#define WITH_HIGHLIGHT 0
#define FREE_SCENE 0

#include "common.h"

struct MINscreen;

#define AKEY		'a' 
#define BKEY		'b'
#define CKEY		'c'
#define DKEY		'd'
#define EKEY		'e'
#define FKEY		'f'
#define GKEY		'g'
#define HKEY		'h'
#define IKEY		'i'
#define JKEY		'j'
#define KKEY		'k'
#define LKEY		'l'
#define MKEY		'm'
#define NKEY		'n'
#define OKEY		'o'
#define PKEY		'p'
#define QKEY		'q'
#define RKEY		'r'
#define SKEY		's'
#define TKEY		't'
#define UKEY		'u'
#define VKEY		'v'
#define WKEY		'w'
#define XKEY		'x'
#define YKEY		'y'
#define ZKEY		'z'

#define ZEROKEY		'0'
#define ONEKEY		'1'
#define TWOKEY		'2'
#define THREEKEY	'3'
#define FOURKEY		'4'
#define FIVEKEY		'5'
#define SIXKEY		'6'
#define SEVENKEY	'7'
#define EIGHTKEY	'8'
#define NINEKEY		'9'

#define UP_AKEY		'A'
#define UP_BKEY		'B'
#define UP_CKEY		'C'
#define UP_DKEY		'D'
#define UP_EKEY		'E'
#define UP_FKEY		'F'
#define UP_GKEY		'G'
#define UP_HKEY		'H'
#define UP_IKEY		'I'
#define UP_JKEY		'J'
#define UP_KKEY		'K'
#define UP_LKEY		'L'
#define UP_MKEY		'M'
#define UP_NKEY		'N'
#define UP_OKEY		'O'
#define UP_PKEY		'P'
#define UP_QKEY		'Q'
#define UP_RKEY		'R'
#define UP_SKEY		'S'
#define UP_TKEY		'T'
#define UP_UKEY		'U'
#define UP_VKEY		'V'
#define UP_WKEY		'W'
#define UP_XKEY		'X'
#define UP_YKEY		'Y'
#define UP_ZKEY		'Z'

#define STARKEY		'*'
#define DOTKEY		'.'

#define ESCKEY		27
#define TABKEY		9

#define	F1KEY 		1
#define	F2KEY 		2
#define	F3KEY 		3

#define RETURNKEY 	13
#define BACKSPACEKEY	8

#define PADZERO		48
#define PADONE		49
#define PADTWO		50
#define PADTHREE	51
#define PADFOUR		52
#define PADFIVE		53
#define PADSIX		54
#define PADSEVEN	55
#define PADEIGHT	56
#define PADNINE		57

#define SHIFTKEY	200
#define ALTKEY		201
#define CTRLKEY		202

#define KEYBOARD_STOP	203

#define MOUSE_START 700
#define MOUSE_STATIC 800
#define MOUSE_MOTION_PASSIVE 801
#define MOUSE_MOTION 802
#define MOUSE_BUTTON_LEFT_PRESSED 803
#define MOUSE_BUTTON_LEFT_RELEASED 840
#define MOUSE_BUTTON_RIGHT_PRESSED 841
#define MOUSE_BUTTON_RIGHT_RELEASED 842
#define MOUSE_BUTTON_MIDDLE_PRESSED 843
#define MOUSE_BUTTON_MIDDLE_RELEASED 844
#define MOUSE_END 850

#define EVENT_KEYBOARD( event) ( event >= 0 && event <= KEYBOARD_STOP)
#define EVENT_MOUSE( event) ( event >= MOUSE_START && event <= MOUSE_END)


typedef enum EventState
{
	event_idle,
	event_linking,
	event_unlinking,
}t_event_state;

typedef struct State_Event_UI
{
	// mouse
	int is_mouse_left_pressed:1;
	int is_mouse_left_released:1;
	int is_mouse_over_brick:1;
	int start_x:1;
	int start_y:1;
	int end_x:1;
	int end_y:1;

	int pan:1;
	int zoom:1;

	// background

	int is_background_button_left_pressed:1;
	int is_background_button_left_released:1;
	
	int is_menu_show:1;
	int is_menu_mouse_show:1;
	int is_menu_pressed:1;
	int is_menu_released:1;
	int is_menu_fixed:1;
	
	int is_selection:1;

	// brick
	int is_brick_transformed:1;
	int is_brick_pressed:1;
	int is_brick_moving:1;
	int is_drawing:1;
	int is_linking:1;
	int is_linking_released:1;
	int typing_start:1;
	int typing_end:1;

	int use_point_global_width:1;
	int use_line_global_width:1;
	int use_scale:1;

	int pan_x;
	int pan_y;

}t_state_event_ui;

typedef struct Main_Event
{
	t_event_state state;

	t_state_event_ui ui;

	int update_connections;

	// color
	int color[4];
	float color_front[3];
	float color_back[3];
	int color_buffer;

	// mouse
	int is_mouse_left_pressed;
	int is_mouse_left_released;
	int is_mouse_over_brick;
	int start_x;
	int start_y;
	int end_x;
	int end_y;

	// background

	int is_background_button_left_pressed;
	int is_background_button_left_released;

	int is_selection;

	// brick
	int is_brick_transformed;
	int is_brick_pressed;
	int is_brick_moving;
	int is_drawing;
	int is_linking;
	int is_linking_released;
	int is_typing;

	char *action;

	// draw 
	int with_texture;
	int with_polygon_offset;
	int with_normal;
	int with_light;
	int with_clear;
	int with_depth;
	int with_point;
	int with_point_id;
	int with_edge;
	int with_edge_color;
	int with_face;
	int with_face_outline;
	int with_highlight;
	int with_blend;

	// sketch
	int sketch_with_scale;

	int rec;
	int recording;
	int rec_save;
	int frame_rec;
	int show_term;

	int debug_select;
	int debug_mouse;
	int debug_process;
	int debug_console;
	int debug_terminal;
	int debug_loop;
	int debug_key;
	int debug_plug;
	int debug_all;
	int debug_to_file;

	int free_scene;
	int last_frame; //last recorded camera

	char buffer_char[20];
	int buffer_char_counter;

	void (* callback)(void);
	int standby_int;
	char standby_char;
	char *standby_string;
	int video_record;
	int video_store;
	int video_stop_call;
	int video_stop;
	int video_init;
	int video_frame;
	int video_frame_number;
	int video_frames_in_memory;

	int brick_delete;

	int switch_plug_in_flow_in;
	int switch_plug_in_flow_out;
	int switch_plug_in_open_in;
	int switch_plug_in_open_out;
	int switch_plug_in_follow_in;
	int switch_plug_in_follow_out;

	int switch_plug_out_flow_in;
	int switch_plug_out_flow_out;
	int switch_plug_out_open_in;
	int switch_plug_out_open_out;
	int switch_plug_out_follow_in;
	int switch_plug_out_follow_out;

	int switch_brick_debug;

	int camera_rotation;
	int brick_copying;
	int brick_cloning;
	int brick_cloning_start;

	int loop_step;
	int load_error;

	int use_threading;
	int rhizome_updated;
	int rhizome_init;

	int color_transition;
	int color_transition_use;
	int color_transition_set;
	int color_transition_count;

	struct Lst *events;

}t_main_event;

typedef struct Event
{
	t_id id;
	struct MINscreen *screen;
	int type;
	int x;
	int y;

}t_event;

void 		event_show( t_event *event);
void		event_add( t_main_event *main_event, struct MINscreen *screen, int x, int y, int type);
void 		event_dispach( t_main_event *main_event);
t_event *	event_new( const char *name);
t_main_event *	main_event_new(void);

#endif
