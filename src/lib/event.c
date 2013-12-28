/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "context.h"
#include "event.h"
#include "util.h"
#include "screen.h"

t_main_event *main_event_new(void)
{
	t_main_event *event = (t_main_event *) mem_malloc( sizeof( t_main_event));

	bzero(&event->ui,sizeof(t_state_event_ui));

	event->update_connections=0;

	event->state=event_idle;
	event->is_background_button_left_pressed=0;
	event->is_background_button_left_released=0;

	event->ui.is_menu_pressed=0;
	event->ui.is_menu_released=0;
	event->ui.is_menu_show=0;
	event->ui.is_menu_mouse_show=0;
	event->ui.is_menu_fixed = 0;
	event->ui.typing_start = 0;
	event->ui.typing_end = 0;
	event->ui.use_point_global_width = 1;
	event->ui.use_line_global_width = 1;
	event->ui.use_scale = 1;

	event->ui.pan = 0;
	event->ui.zoom = 0;
	event->ui.pan_x = 0;
	event->ui.pan_y = 0;

	event->is_selection=0;

	event->is_brick_transformed=0;
	event->is_brick_pressed=0;
	event->is_brick_moving=0;
	event->is_mouse_over_brick=0;
	event->is_typing=0;
	event->action=NULL;
	event->with_texture=1;
	event->with_polygon_offset=EVENT_WITH_POLYGON_OFFSET;
	event->with_clear=1;
	event->with_normal=1;
	event->with_light=1;
	event->with_depth=1;
	event->with_face=1;
	event->with_face_outline=0;
	event->with_point=0;
	event->with_edge = 0;
	event->with_edge_color = 0;
	event->with_point_id=0;
	event->with_highlight=WITH_HIGHLIGHT;
	event->sketch_with_scale=SKETCH_WITH_SCALE;
	event->with_blend=1;

	event->is_drawing=0;

	event->color[0] = 0;
	event->color[1] = 0;
	event->color[2] = 0;

	event->rec=0;
	event->rec_save=0;
	event->recording=0;
	event->show_term=CTX_SHOW_TERM;

	event->debug_select=CTX_DEBUG_SELECT;
	event->debug_mouse=CTX_DEBUG_MOUSE;
	event->debug_process=DEBUG_PROCESS;
	event->debug_console=DEBUG_CONSOLE;
	event->debug_terminal=DEBUG_TERMINAL;
	event->debug_loop = DEBUG_LOOP;
	event->debug_key = DEBUG_KEY;
	event->debug_plug = DEBUG_PLUG;
	event->debug_all = DEBUG_ALL;
	event->debug_to_file = DEBUG_TO_FILE;

	event->free_scene=FREE_SCENE;

	vset(event->color_front,1,1,1);
	vset(event->color_back,0,0,0);
	event->color_buffer=0;

	event->last_frame=0;

	bzero(&event->buffer_char[0],20);
	event->buffer_char_counter=0;
	
	event->callback=NULL;
	event->standby_int=0;
	event->standby_char='\0';
	event->standby_string=NULL;
	event->video_record = 0;
	event->video_store = 0;
	event->video_init = 0;
	event->video_frame =0;
	event->video_frame_number =0;
	event->video_stop = 0;
	event->video_stop_call = 0;
	event->video_frames_in_memory = 0;

	event->brick_delete = 0;

	event->switch_plug_in_flow_in = 0;
	event->switch_plug_in_flow_out = 0;
	event->switch_plug_in_open_in = 0;
	event->switch_plug_in_open_out = 0;
	event->switch_plug_in_follow_in = 0;
	event->switch_plug_in_follow_out = 0;

	event->switch_plug_out_flow_in = 0;
	event->switch_plug_out_flow_out = 0;
	event->switch_plug_out_open_in = 0;
	event->switch_plug_out_open_out = 0;
	event->switch_plug_out_follow_in = 0;
	event->switch_plug_out_follow_out = 0;

	event->switch_brick_debug = 0;

	event->camera_rotation = 0;
	event->brick_copying = 0;
	event->brick_cloning = 0;
	event->brick_cloning_start = 0;

	event->loop_step = 0;
	event->load_error = 0;

	event->use_threading = 1;
	event->rhizome_init = 0;

	event->color_transition = 0;
	event->color_transition_use = 1;
	event->color_transition_set = 0;
	event->color_transition_count = 0;

	event->events = lst_new( "events");

	return event;
}

void event_add( t_main_event *main_event, t_screen *screen, int x, int y, int type)
{
	t_event *event = event_new( "event");
	event->screen = screen;
	event->x = x;
	event->y = y;
	event->type = type;

	lst_add( main_event->events, event, event->id.name);
}

void event_print( int state)
{
	switch( state)
	{
		case AKEY: printf("a"); break;
		case BKEY: printf("b"); break;
		case CKEY: printf("c"); break;
		case DKEY: printf("d"); break;
		case EKEY: printf("e"); break;
		case FKEY: printf("f"); break;
		case GKEY: printf("g"); break;
		case HKEY: printf("h"); break;
		case IKEY: printf("i"); break;
		case JKEY: printf("j"); break;
		case KKEY: printf("k"); break;
		case LKEY: printf("l"); break;
		case MKEY: printf("m"); break;
		case NKEY: printf("n"); break;
		case OKEY: printf("o"); break;
		case PKEY: printf("p"); break;
		case QKEY: printf("q"); break;
		case RKEY: printf("r"); break;
		case SKEY: printf("s"); break;
		case TKEY: printf("t"); break;
		case UKEY: printf("u"); break;
		case VKEY: printf("v"); break;
		case WKEY: printf("w"); break;
		case XKEY: printf("x"); break;
		case YKEY: printf("y"); break;
		case ZKEY: printf("z"); break;

		case UP_AKEY: printf("A"); break;
		case UP_BKEY: printf("B"); break;
		case UP_CKEY: printf("C"); break;
		case UP_DKEY: printf("D"); break;
		case UP_EKEY: printf("E"); break;
		case UP_FKEY: printf("F"); break;
		case UP_GKEY: printf("G"); break;
		case UP_HKEY: printf("H"); break;
		case UP_IKEY: printf("I"); break;
		case UP_JKEY: printf("J"); break;
		case UP_KKEY: printf("K"); break;
		case UP_LKEY: printf("L"); break;
		case UP_MKEY: printf("M"); break;
		case UP_NKEY: printf("N"); break;
		case UP_OKEY: printf("O"); break;
		case UP_PKEY: printf("P"); break;
		case UP_QKEY: printf("Q"); break;
		case UP_RKEY: printf("R"); break;
		case UP_SKEY: printf("S"); break;
		case UP_TKEY: printf("T"); break;
		case UP_UKEY: printf("U"); break;
		case UP_VKEY: printf("V"); break;
		case UP_WKEY: printf("W"); break;
		case UP_XKEY: printf("X"); break;
		case UP_YKEY: printf("Y"); break;
		case UP_ZKEY: printf("Z"); break;

		case STARKEY: printf("*"); break;
		case DOTKEY: printf("."); break;
		case F1KEY: printf("F1"); break;
		case F2KEY: printf("F2"); break;
		case F3KEY: printf("F3"); break;

		case TABKEY: printf("TAB"); break;
		case RETURNKEY: printf("RETURN"); break;
		case BACKSPACEKEY: printf("BACKSPACE"); break;

		case PADZERO: printf("PAD 0"); break;
		case PADONE: printf("PAD 1"); break;
		case PADTWO: printf("PAD 2"); break;
		case PADTHREE: printf("PAD 3"); break;
		case PADFOUR: printf("PAD 4"); break;
		case PADFIVE: printf("PAD 5"); break;
		case PADSIX: printf("PAD 6"); break;
		case PADSEVEN: printf("PAD 7"); break;
		case PADEIGHT: printf("PAD 8"); break;
		case PADNINE: printf("PAD 9"); break;

		case MOUSE_STATIC: printf("MOUSE STATIC"); break;
		case MOUSE_MOTION_PASSIVE: printf("MOUSE MOTION PASSIVE"); break;
		case MOUSE_MOTION: printf("MOUSE MOTION"); break;
		case MOUSE_BUTTON_LEFT_PRESSED: printf("MOUSE BUTTON LEFT PRESSED"); break;
		case MOUSE_BUTTON_LEFT_RELEASED: printf("MOUSE BUTTON LEFT RELEASED"); break;
		case MOUSE_BUTTON_RIGHT_PRESSED: printf("MOUSE BUTTON RIGHT PRESSED"); break;
		case MOUSE_BUTTON_RIGHT_RELEASED: printf("MOUSE BUTTON RIGHT RELEASED"); break;
		case MOUSE_BUTTON_MIDDLE_PRESSED: printf("MOUSE BUTTON MIDDLE PRESSED"); break;
		case MOUSE_BUTTON_MIDDLE_RELEASED: printf("MOUSE BUTTON MIDDLE RELEASED"); break;

		case SHIFTKEY: printf("SHIFTKEY"); break;
		case ALTKEY: printf("ALTKEY"); break;
		case CTRLKEY: printf("CTRLKEY"); break;
		default: printf("? %d", state); break;
	}
}

void event_show( t_event *event)
{
	printf("event ");
	event_print( event->type);
	printf(" %d %d\n", event->x, event->y);
}

void event_free( t_event *event)
{
	mem_free( event, sizeof( t_event));
}

t_event *event_new( const char *name)
{
	t_event *event = mem_malloc( sizeof( t_event));
	id_init( &event->id, name);

	event->screen = NULL;
	event->x = 0;
	event->y = 0;

	return event;
}
