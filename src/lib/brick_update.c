/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "context.h"
#include "node.h"
#include "scene.h"
#include "op.h"
#include "action.h"
#include "ctx.h"
#include "app.h"
#include "event.h"
#include "term.h"
#include "ui.h"
#include "dict.h"
#include "list.h"
#include "event.h"
#include "brick.h"
#include "block.h"
#include "binding.h"
#include "rhizome.h"
#include "set.h"
#include "event.h"

int is_vec_stored=0;
float v[3];
float vec[3];

void state_brick_slider_default( t_brick *brick, t_event *e);
void state_brick_default( t_brick *brick, t_event *e);
void state_brick_edit( t_brick *brick, t_event *e);

int brick_check_viewport( t_brick *brick)
{
	t_context *C=ctx_get();
	if(C->scene->has_generic_viewport) return 1;
	else return 0;
}

int brick_check_loop(t_brick *brick)
{
	t_context *C = ctx_get();

	int frame = C->app->frame;

	if(brick->brick_state.frame_loop != frame)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// SET UPDATED

void brick_set_updated(t_brick *brick)
{
	t_plug *plug = &brick->plug_intern;

	// Bindings
	if(plug->bindings)
	{
		t_link *link;
		for(link = plug->bindings->first; link; link = link->next)
		{
			t_binding *binding = link->data;
			binding_update(binding,plug->data);
		}
	}

	// Set Updated
	brick->plug_in.state.is_updated = 1;
	brick->plug_intern.state.is_updated = 1;
	brick->plug_out.state.is_updated = 1;

	// Set Setup
	if(brick->mode == bm_triggering)
	{
		t_block *block = brick->block;
		t_set *set = block->set;
		if(set) set_setup(set);
	}
}

/*
	**************************	CONNECT / DISCONNECT   **************************** 
*/

// CONNECT

void cls_brick_connect(t_brick *brick_in ,t_brick *brick_out)
{
	t_context *C = ctx_get();
	C->ui->do_connect = 1;
	C->ui->connect_brick_in = brick_in;
	C->ui->connect_brick_out = brick_out;
}

void _cls_brick_connect(t_brick *brick_in ,t_brick *brick_out)
{
	t_plug *plug_brick_in = &brick_in->plug_intern;
	t_plug *plug_brick_out = &brick_out->plug_intern;

	// first Out
	plug_brick_out->cls->connect(mode_out, plug_brick_out, plug_brick_in);
	// Then In
	plug_brick_in->cls->connect(mode_in, plug_brick_in, plug_brick_out);
}

// DISCONNECT

void _cls_brick_disconnect(t_brick *self)
{
	t_brick *brick_in = self;
	t_plug *plug_target = brick_in->plug_in.src;
	if( plug_target)
	{
		t_brick *brick_out = plug_target->brick;
		t_plug *plug_out = &brick_out->plug_intern;
		t_plug *plug_in = &brick_in->plug_intern;

		plug_out->cls->disconnect(mode_out ,plug_out);
		plug_in->cls->disconnect(mode_in , plug_in);

		// Split Graph
		brick_rhizome_split(brick_in, brick_out);
	}
}

void cls_brick_disconnect(t_brick *self)
{
	t_context *C = ctx_get();
	C->ui->do_disconnect = 1;
	C->ui->connect_brick_in = self;
}

// MOUSE

int brick_release_cloning(t_brick *brick)
{
	t_context *C=ctx_get();
	if( C->ui->mouse_state == UI_LEFT_RELEASED) return 1;
	else return 0;
}

int brick_start_cloning(t_context *C,int mouse_over)
{
	if(
		mouse_over
		&& !C->event->ui.is_menu_show
		&& (C->ui->mouse_state == UI_LEFT_PRESSED)
		&& (C->app->keyboard->ctrl || C->app->keyboard->shift)
		)

		return 1;
	else 
		return 0;
}

/*
	**************************	TRIGGER **************************** 
*/

// SLIDER
void cls_brick_trigger_slider( t_brick *brick)
{
	brick->act(brick);
	brick_set_updated(brick);
}

// SWITCH
void cls_brick_trigger_switch(t_brick *brick)
{
	if(brick->brick_state.is_idle)
	{
		brick->act(brick);
		brick_set_updated(brick);
	}
}

// SELECTOR
void cls_brick_trigger_selector(t_brick *brick)
{
	brick->act(brick);
	brick_set_updated(brick);
}

// MENU
void cls_brick_trigger_menu(t_brick *brick)
{
	brick_set_updated(brick);
}

// TRIGGER
void cls_brick_trigger_trigger(t_brick *brick)
{
	t_context *C = ctx_get();

	// trigger
	if(brick->brick_state.is_mouse_over)
	{
		// brick pressed
		if( C->ui->mouse_state == UI_LEFT_PRESSED && brick->brick_state.is_released)
		{
			if(!brick->brick_state.is_idle)
			{
			brick->brick_state.is_released=0;
			brick->act(brick);
			}
		}
	}

	// release
	if(!brick->brick_state.is_released && C->ui->mouse_state == UI_LEFT_RELEASED)
	{
		// hide menu
		if(C->event->ui.is_menu_mouse_show && !C->ui->fixed_menu)
		{
			ctx_ui_menu_hide(C);
		}

		// release brick
		brick->brick_state.is_released=1;
		brick_release(brick);
	}

	brick_set_updated(brick);
}

// RELEASE

void brick_release(t_brick *brick)
{
	t_context *C = ctx_get();
	brick->mode=bm_idle;
	C->event->is_brick_transformed=0;
	C->ui->brick_selected=NULL;
}

// REMOVE

void brick_remove(t_action *action)
{
	t_context *C = ctx_get();
	t_dict *args = action->args;

	t_brick *brick = dict_pop_data(args,"brick");
	t_block *block = brick->block;

	if(!block_is_connected("in",block) && !block_is_connected("out",block))
	{
		//t_lst *lst = get_target_list(C);
		t_set *set = get_current_set(C);
		t_lst *lst = set->blocks;

		list_remove_by_ptr(lst,block);
		scene_delete(C->scene,block);
	}
}


// UPDATE


void cls_brick_update(t_brick *brick)
{
#if 0
	t_context *C = ctx_get();
	t_brick_mode mode = brick->mode;

	t_plug *plug_in = &brick->plug_in;
	t_plug *plug_out = &brick->plug_out;

	int mouse_over = ctx_mouse_hover_brick(C,brick);
	int brick_clic=0;

	int edit = 0;
	if(mouse_over && (C->ui->mouse_state == UI_MIDDLE_PRESSED))
	{
		edit = 1;
		C->event->is_mouse_over_brick = 1;
	}
	

	float mouse_pos[3];
	vset(mouse_pos,0,0,0);

	if(	 mouse_over 
		&& (C->ui->mouse_state == UI_LEFT_PRESSED)
		&& (brick->brick_state.is_mouse_over_plug_in==0)
		&& (brick->brick_state.is_mouse_over_plug_out==0)
		)
	{
		brick_clic=1;
	}

	// IDLE

	if(!brick->brick_state.is_idle)
	{
		if( C->ui->mouse_state == UI_LEFT_RELEASED)
		{
			brick->brick_state.is_idle=1;
		}
	}
		
	// DELETE

	if(mouse_over && C->event->brick_delete) 
	{
		t_action *action = action_new("action");

		action->act = brick_remove;

		t_dict *dict = dict_make("args");
		action->args = dict;
		action->brick = brick;

		dict_symbol_add(action->args,"brick",dt_null,brick);

		exe_add_action(action);
	}

	// PLUGS
	t_main_event *event = C->event;

	if(mouse_over)
	{
		     if(event->switch_plug_in_flow_in)		plug_in->state.flow_in = switch_int(plug_in->state.flow_in);
		else if(event->switch_plug_in_open_in)		plug_in->state.open_in = switch_int(plug_in->state.open_in);
		else if(event->switch_plug_in_follow_in)	plug_in->state.follow_in  = switch_int(plug_in->state.follow_in);
		else if(event->switch_plug_in_flow_out)		plug_in->state.flow_out  = switch_int(plug_in->state.flow_out);
		else if(event->switch_plug_in_open_out)		plug_in->state.open_out  = switch_int(plug_in->state.open_out);
		else if(event->switch_plug_in_follow_out)	plug_in->state.follow_out  = switch_int(plug_in->state.follow_out);

		else if(event->switch_plug_out_flow_in)		plug_out->state.flow_in  = switch_int(plug_out->state.flow_in);
		else if(event->switch_plug_out_open_in)		plug_out->state.open_in  = switch_int(plug_out->state.open_in);
		else if(event->switch_plug_out_follow_in)	plug_out->state.follow_in  = switch_int(plug_out->state.follow_in);
		else if(event->switch_plug_out_flow_out)	plug_out->state.flow_out  = switch_int(plug_out->state.flow_out);
		else if(event->switch_plug_out_open_out)	plug_out->state.open_out  = switch_int(plug_out->state.open_out);
		else if(event->switch_plug_out_follow_out)	plug_out->state.follow_out  = switch_int(plug_out->state.follow_out);

		else if(event->switch_brick_debug)		
		{
			if(brick->brick_state.debug)
			{
				term_log("%s: debug off",brick->id.name);
				brick->brick_state.debug = 0;
			}
			else
			{
				term_log("%s: debug on",brick->id.name);
				brick->brick_state.debug = 1;
			}
		}
	}

	// Debug

	if(brick->brick_state.is_mouse_over && brick->brick_state.debug)
	{
		t_plug *plug = &brick->plug_intern;
		term_log("%d) brick %s",C->app->frame, brick->id.name);
		plug_debug(plug);
	}

	//printf("%d %d %d\n",C->event->ui.pan,C->event->camera_rotation,C->event->ui.zoom);

	// MODES

	if(!C->event->ui.pan && !C->event->camera_rotation && !C->event->ui.zoom)
	{
		switch(mode)
		{
			case bm_idle:

				// STORE BRICK_IN
				if(C->event->is_brick_transformed)
				{

					if(is_mouse_over_plug(C,&brick->plug_in) && C->ui->mouse_state == UI_LEFT_PRESSED)
					{
						C->ui->brick_in=brick;
					}

				}

				if(!C->event->is_brick_transformed)
				{
					// START CLONING
					if(brick_start_cloning(C,mouse_over))
					{
						// start moving
						if(C->event->brick_cloning_start)
						{
							C->event->is_brick_transformed=1;
							C->ui->brick_selected=brick;
							brick->mode=bm_moving;
						}
						// start cloning
						else
						{
							if(!C->event->ui.is_menu_mouse_show)
							{
								C->event->is_brick_transformed=1;
								C->ui->brick_selected=brick;
								brick->mode=bm_cloning;

								// Copy or Clone
								if(C->app->keyboard->shift)
									C->event->brick_copying = 1;
								else if(C->app->keyboard->ctrl)
									C->event->brick_cloning = 1;
							}
						}
					}
					// START MOVING
					else if(mouse_over && C->ui->mouse_state == UI_RIGHT_PRESSED) 
					{
						if(!C->event->ui.is_menu_mouse_show)
						{
							C->event->is_brick_transformed=1;
							C->ui->brick_selected=brick;
							brick->mode=bm_moving;
						}
					}

					// START LINKING
					else if(is_mouse_over_plug(C,&brick->plug_out) && C->ui->mouse_state == UI_LEFT_PRESSED)
					{
						if(!C->event->ui.is_menu_mouse_show)
						{
							C->event->is_brick_transformed=1;
							C->ui->brick_selected=brick;
							brick->mode=bm_linking;
							C->ui->brick_out=brick;
						}
					}

					// START UNLINKING
					else if(is_mouse_over_plug(C,&brick->plug_in) && C->ui->mouse_state == UI_LEFT_PRESSED)
					{
						C->ui->brick_in=brick;

						if(plug_in->state.is_connected)
						{
							if(!C->event->ui.is_menu_mouse_show)
							{
								C->event->is_brick_transformed=1;
								C->ui->brick_selected=brick;
								brick->mode=bm_unlinking;
							}
						}
					}

					// START TYPING
					else if( edit)
					{
						C->event->is_brick_transformed=1;
						C->ui->brick_selected=brick;
						brick->mode=bm_typing;
						C->event->ui.typing_start = 1;
						C->event->is_typing=1;

						set_name_long( C->event->buffer_char, brick->txt_data.name);
						C->event->buffer_char_counter = strlen( brick->txt_data.name);
					}

					// START TRIGGER 
					else 
					{
						if(brick->brick_state.is_clicable)
						{
							if(brick_clic)
							{
								int trigger;

								if(plug_in->state.is_connected)
								{
									if(plug_in->state.flow_in == 0)
										trigger = 1;
									else
										trigger = 0;
								}
								else
								{
									trigger = 1;
								}

								if(trigger)
								{
									brick->brick_state.is_idle=0;
									C->event->is_brick_transformed=1;
									C->ui->brick_selected=brick;
									brick->mode=bm_triggering;
								}
							}
						}
					}
				}

				break;

			case bm_moving:

				// cloning
				if(C->event->brick_cloning_start)
				{
					// release
					if(brick_release_cloning(brick))
					{
						is_vec_stored=0;
						C->event->brick_cloning_start=0;
						C->event->brick_copying = 0;
						C->event->brick_cloning = 0;
						brick_release(brick);
					}

					t_block *block=brick->block;
					float *block_pos=block->pos;
					ctx_get_mouse_pos(C,mouse_pos);

					if(!is_vec_stored)
					{
						is_vec_stored=1;
						ctx_ui_menu_hide(C);
						vsub(vec,block_pos,mouse_pos);
					}
					else
					{
						ctx_ui_menu_hide(C);
						vadd(v,mouse_pos,vec);
						vcp(block_pos,v);
					}
				}
				// moving
				else
				{
					// release
					if( C->ui->mouse_state == UI_RIGHT_RELEASED)
					{
						is_vec_stored=0;
						brick_release(brick);
					}
					// move
					else
					{
						t_block *block=brick->block;

						if(block->block_state.is_moveable)
						{
							float *block_pos=block->pos;
							ctx_get_mouse_pos(C,mouse_pos);

							if(!is_vec_stored)
							{
								is_vec_stored=1;
								ctx_ui_menu_hide(C);
								vsub(vec,block_pos,mouse_pos);
							}
							else
							{
								ctx_ui_menu_hide(C);
								vadd(v,mouse_pos,vec);
								vcp(block_pos,v);
							}
						}
					}
				}

				break;

			case bm_cloning:

				if(!C->event->brick_cloning_start)
				{
					t_block *clone_block;

					if(C->event->brick_cloning)
						clone_block = block_dupli(brick->block);
					else
						clone_block = block_copy(brick->block);

					t_brick *clone_brick=clone_block->bricks->first->data;

					clone_brick->brick_state.is_mouse_over=1;
					clone_block->block_state.is_mouse_over=0;
					clone_brick->mode=bm_moving;

					brick_release(brick);
					C->event->is_brick_transformed=1;

					C->event->brick_cloning_start=1;
				}

				break;


			case bm_linking:
				
				// release linking
				if( C->ui->mouse_state == UI_LEFT_RELEASED)
				{
					// connect
					if(C->ui->brick_in)
					{
						t_brick *brick_in=C->ui->brick_in;
						t_plug *plug_in=&brick_in->plug_in;
						if(!plug_in->src)
						{
							t_brick *brick_in = C->ui->brick_in;
							t_brick *brick_out = C->ui->brick_out;

							brick_in->cls->connect(brick_in,brick_out);
						}

					}

					// reset

					C->ui->brick_out=NULL;
					C->ui->brick_in=NULL;

					C->event->is_drawing=0;

					C->event->state=event_idle;
					brick->brick_state.is_linking=0;

					// release
					brick_release(brick);

				}
				else
				{
					t_brick *brick_out=C->ui->brick_out;
					t_plug *plug_out=&brick_out->plug_out;

					// if plug out isn't yet plugged
					if(!plug_out->state.is_connected)
					{
						// init linking
						if(!brick->brick_state.is_linking)
						{
							brick->brick_state.is_linking=1;

							ctx_get_mouse_pos(C,mouse_pos);

							t_block *block=brick->block;

							float width = brick_get_width(brick);
							//width+=brick->geom.height*2;

							float x=block->pos[0];
							float y=block->pos[1];

							float pos_x= x	+  width ;
							float pos_y= y + (brick->geom.block_pos*brick->geom.height) +(brick->geom.height/2);

							C->event->start_x=pos_x; 
							C->event->start_y=pos_y;


							C->event->is_drawing=1;
							C->event->state=event_linking;
						}
					}

					// else release
					else
					{
						brick->mode=bm_idle;
						C->event->is_brick_transformed=0;
					}
				}

				break;
		
			case bm_unlinking:
				brick->cls->disconnect(brick);
				break;

			case bm_triggering:
				brick->cls->trigger(brick);
				break;

			case bm_typing:

				//release

				if(
					(C->event->is_typing==0)
					||
					(C->event->ui.typing_start && C->event->ui.typing_end)
					)
				{
					brick->mode=bm_idle;
					C->event->is_brick_transformed=0;
					C->event->is_typing=0;
					bzero(&C->event->buffer_char[0],20);
					C->event->buffer_char_counter=0;
					C->event->ui.typing_start = 0;
					C->event->ui.typing_end = 0;

				}
				// change data
				else
				{
					t_plug *plug = &brick->plug_intern;

					if(plug->data_type==dt_int)
					{
						int *dt=plug->data;
						*dt=atoi(C->event->buffer_char);
					}
					else if(plug->data_type==dt_float)
					{
						float *dt=plug->data;
						*dt=atof(C->event->buffer_char);
					}
					
				}

				break;
		}
	}
#endif
}


void brick_hover_set( t_brick *brick)
{
	t_context *C = ctx_get();
	if( ctx_mouse_hover_brick_left( C, brick))	 	brick->state_pressed = BRICK_LEFT;
	else if( ctx_mouse_hover_brick_right( C, brick)) 	brick->state_pressed = BRICK_RIGHT;
	else if( ctx_mouse_hover_brick_plug_in( C, brick))	brick->state_pressed = BRICK_PLUG_IN;
	else if( ctx_mouse_hover_brick_plug_out( C, brick))	brick->state_pressed = BRICK_PLUG_OUT;
	else							brick->state_pressed = BRICK_NULL;
}

/*	**********************************
	:EDIT
	**********************************	*/


void brick_edit_name( t_context *C, t_brick *brick)
{
	t_plug *plug = &brick->plug_intern;

	if(plug->data_type==dt_int)
	{
		int *dt=plug->data;
		*dt=atoi(C->event->buffer_char);
	}
	else if(plug->data_type==dt_float)
	{
		float *dt=plug->data;
		*dt=atof(C->event->buffer_char);
	}
}


typedef void (* State_Func) (struct Brick *, struct Event *);
State_Func brick_state_set_default( t_brick *brick)
{
	switch( brick->type)
	{
		case bt_switch: return 		&state_brick_switch_default; break;
		case bt_slider: return 		&state_brick_slider_default; break;
		default: return 		&state_brick_default; break;
	}
}

void brick_edit_start( t_context *C, t_brick *brick)
{
	C->event->ui.typing_start = 1;
	BRICK_SWAP( brick, state_brick_edit);
}

void brick_edit_stop( t_context *C, t_brick *brick)
{
	C->event->ui.typing_start = 0;
	brick->state = brick_state_set_default( brick );
	ctx_event_add( UI_BRICK_RELEASED);
}

void state_brick_edit( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_default");
	t_context *C = ctx_get();
	switch( e->type)
	{
		case RETURNKEY:
			C->event->ui.typing_start = 0;
			ctx_ui_buffer_clear( C);
			brick_edit_stop( C, brick);
			break;
		default:
			brick_edit_name( C, brick);
			break;
	}
}


/*	**********************************
	SLIDER
	**********************************	*/

void state_brick_slider_drag( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_slider_drag");
	t_context *C = ctx_get();
	if( e->type == MOUSE_LEFT_RELEASED)
	{
		ctx_event_add( UI_BRICK_RELEASED);
		BRICK_SWAP( brick, state_brick_slider_default);
	}
	else
	{
		if( C->ui->mouse_delta_x >= 0) brick->state_pressed = BRICK_RIGHT;
		else brick->state_pressed = BRICK_LEFT;
		brick->act( brick);
	}
}

void state_brick_slider_trigger( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_slider_trigger");
	switch( e->type)
	{
		case MOUSE_LEFT_RELEASED:
			brick->act( brick);
			ctx_event_add( UI_BRICK_RELEASED);
			BRICK_SWAP( brick, state_brick_slider_default);
			break;

		case MOUSE_MOTION:
			BRICK_SWAP( brick, state_brick_slider_drag);
			break;
	}
}

void state_brick_slider_default( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_slider_default");
	switch( e->type)
	{
		case MOUSE_LEFT_PRESSED:
			brick_hover_set( brick);
			BRICK_SWAP( brick, state_brick_slider_trigger);
			brick->cls->dispatch( brick);
			break;

		case MOUSE_MIDDLE_PRESSED:
			brick_hover_set( brick);
			BRICK_SWAP( brick, state_brick_slider_trigger);
			break;
	}
}

/*	**********************************
	SWITCH
	**********************************	*/


void state_brick_switch_default( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_switch_default");
	switch( e->type)
	{
		case MOUSE_LEFT_PRESSED:
			brick->act( brick);
			break;

		case MOUSE_LEFT_RELEASED:
			ctx_event_add( UI_BRICK_RELEASED); 
			BRICK_SWAP( brick, state_brick_switch_default);
			break;
	}
}
					
void state_brick_default( t_brick *brick, t_event *e)
{
	ctx_ui_log( "brick_default");
	switch( e->type)
	{
		case MOUSE_LEFT_PRESSED:
			brick->act( brick);
			break;

		case MOUSE_LEFT_RELEASED:
			ctx_event_add( UI_BRICK_RELEASED); 
			break;

		case MOUSE_MIDDLE_PRESSED:
			break;
	}
}

/*	**********************************
	DISPATCH
	**********************************	*/

void cls_brick_dispatch( t_brick *brick)
{
	t_context *C = ctx_get();
	t_link *l;
	t_event *e;
	for(l=C->event->events_swap->first;l;l=l->next)
	{
		e = l->data;
		brick->state( brick, e);
	}
}
