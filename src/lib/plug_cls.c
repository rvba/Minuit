/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "op.h"

#define db_main 0


void cls_plug_make_float(t_plug *plug);
void cls_plug_make_int(t_plug *plug);
void cls_plug_make_string(t_plug *plug);
void cls_plug_make_pointer(t_plug *plug);
void cls_plug_make_mesh(t_plug *plug);
void cls_plug_make_vertex(t_plug *plug);
void cls_plug_make_face(t_plug *plug);
void cls_plug_make_vlst(t_plug *plug);
void cls_plug_make_lst(t_plug *plug);
void cls_plug_make_camera(t_plug *plug);
void cls_plug_make_char(t_plug *plug);
void cls_plug_make_object(t_plug *plug);
void cls_plug_make_selector(t_plug *plug);
void cls_plug_make_trigger(t_plug *plug);
void cls_plug_make_operator(t_plug *plug);
void cls_plug_make_vector(t_plug *plug);

void cls_plug_connect_general(t_plug_mode mode, t_plug *self, t_plug *dst);
void cls_plug_disconnect_general(t_plug_mode mode, t_plug *self);

void plug_debug(t_plug *plug)
{
	t_data_type type = plug->data_type;
	void *data = plug->data;

	switch(type)
	{
		case dt_int: term_log("%d", drf_int(data)); break;
		case dt_float: term_log("%f", drf_float(data)); break;
		case dt_vector: vector_show(data); break;
		case dt_vlst: vlst_show(data); break;
		default:
			term_log("unknown type %s", data_name_get(type));
			break;
	}
}

void cls_plug_connect_int(t_plug_mode mode, t_plug *self,t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_int(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_float(t_plug_mode mode, t_plug *self,t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_float(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_string(t_plug_mode mode, t_plug *self,t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_string(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_pointer(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_pointer(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_mesh(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_mesh(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_vertex(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_vertex(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_face(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_face(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_vlst(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_vlst(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_lst(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_lst(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_camera(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_camera(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_char(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_char(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_object(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_object(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_selector(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_selector(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_trigger(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_trigger(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

void cls_plug_connect_operator(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	// General
	cls_plug_connect_general(mode,self,dst);
}

void cls_plug_disconnect_operator(t_plug_mode mode, t_plug *plug)
{
	// General
	cls_plug_disconnect_general(mode,plug);
}

// Set all Branch In Loop
void set_in_loop(t_brick *brick, int state)
{
	t_block *block = brick->block;

	t_lst *lst = lst_new("lst");
	block_branch_get(lst,block);

	if(lst->first)
	{
		t_link *link;
		t_brick *brick;
		t_plug *plug;

		for(link = lst->first; link; link = link->next)
		{
			int i;
			i=0;
			i++;
			brick = link->data;
			plug = &brick->plug_intern;
			plug->is_in_loop = state;
		}
	}


	t_context *C = ctx_get();
	if(C->event->debug_loop)
	{
		term_log("set in loop %s",brick->name);
		list_show(lst);
	}

	lst_free(lst);

}

// CONNECT GENERAL

void cls_plug_connect_general(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	t_brick *brick = self->brick;
	t_plug *plug_in = &brick->plug_in;
	t_plug *plug_out = &brick->plug_out;

	t_brick *brick_dst = dst->brick;
	t_plug *plug_dst_in = &brick_dst->plug_in;
	t_plug *plug_dst_out = &brick_dst->plug_out;
	
	// Mode In
	if(mode == mode_in)
	{
		// Connect Plugs
		plug_in->src = plug_dst_out;
		plug_in->is_connected = 1;

		// If Versatil
		if(brick->state.is_versatil)
		{
			if(self->data_type != dst->data_type)
			{
				// Change Type
				brick_type_change(brick,dst);
			}
		}
	}
	// Mode Out
	else
	{
		// Connect Plugs
		plug_out->dst = plug_dst_in;
		plug_out->is_connected = 1;
	}

	// Close flow in (Clone)
	if(dst->close_flow_in && self->use_flow)
	{
		t_plug *plug_in = &brick->plug_in;
		plug_in->flow_in = 0;
	}

	// Set in Loop
	if(!self->is_a_loop)
	{
		if(dst->is_a_loop || dst->is_in_loop)
		{
			set_in_loop(brick,1);
		}
	}
}

// DISCONNECT GENERAL

void cls_plug_disconnect_general(t_plug_mode mode, t_plug *self)
{
	t_brick *brick = self->brick;
	t_plug *plug_in = &brick->plug_in;
	t_plug *plug_out = &brick->plug_out;

	// Restore Flow In
	if(self->use_flow)
		plug_in->flow_in = 1;


	// Mode In
	if(mode == mode_in)
	{
		// Disconnect
		plug_in->src = NULL;
		plug_in->is_connected = 0;
	}
	// Mode Out
	else
	{
		// Set Out of Loop
		set_in_loop(brick,0);

		// Disconnect
		plug_out->dst = NULL;
		plug_out->is_connected = 0;
	}
}

// CONNECT VECTOR

void cls_plug_connect_vector(t_plug_mode mode, t_plug *self, t_plug *dst)
{
	t_brick *brick = self->brick;
	t_block *block = brick->block;
	t_plug *plug_in = &brick->plug_in;
	t_plug *plug_out = &brick->plug_out;

	t_brick *brick_x = block_brick_get(block,"x");
	t_brick *brick_y;
	t_brick *brick_z;
	t_plug *plug_x; 
	t_plug *plug_y; 
	t_plug *plug_z; 

	// Get XYZ
	if(brick_x)
	{
		brick_y = block_brick_get(block,"y");
		brick_z = block_brick_get(block,"z");

		plug_x = &brick_x->plug_intern;
		plug_y = &brick_y->plug_intern;
		plug_z = &brick_z->plug_intern;
	}


	// General
	cls_plug_connect_general(mode,self,dst);

	// If Dst Volatil && Mode Out (For/Get  Vector)
	if(dst->is_volatil && mode == mode_out)
	{
		// Open & Close Plugs
		if(self->is_state_volatil) // For Vector
		{
			// Close Flow In
			plug_in->flow_in = 0;
			plug_in->open_in = 1;

			// Open Dst Flow In
			plug_out->open_out = 0;
			plug_out->flow_out = 1;
			plug_out->open_in = 1;
		}
			
		// Don't Store Pointers
		// CLOSE
		if(brick_x)
		{
			plug_x->store_data = 0;
			plug_y->store_data = 0;
			plug_z->store_data = 0;

			/*
			brick_x->state.draw_value = 0;
			brick_y->state.draw_value = 0;
			brick_z->state.draw_value = 0;
			*/

			// Close XYZ

			t_plug *plug_x_in = &brick_x->plug_in;
			t_plug *plug_y_in = &brick_y->plug_in;
			t_plug *plug_z_in = &brick_z->plug_in;

			plug_x_in->flow_in = 0;
			plug_y_in->flow_in = 0;
			plug_z_in->flow_in = 0;

			plug_x->data = NULL;
			plug_y->data = NULL;
			plug_z->data = NULL;

		}
	}

	// Vector Target
	if(
		brick_x
		&&
		(
			// Mode Out : For Vector
			dst->is_parent 
		||
			// Mode In : Vector
			(
				(dst->data_type == dt_vector)
				&&
				(mode == mode_in)
			)
		)
	)
	{
		// Remove Vectors' XYZ Parents 
		plug_child_remove_all_parents(self);

		t_context *C = ctx_get();

		// Set XYZ to be Childs of Vector
		C->scene->store = 1;
		plug_add_parent(plug_x,self);
		plug_add_parent(plug_y,self);
		plug_add_parent(plug_z,self);
		C->scene->store = 0;
	}
}

void cls_plug_disconnect_vector(t_plug_mode mode, t_plug *plug)
{
	t_brick *brick = plug->brick;
	t_block *block = brick->block;
	t_plug *plug_in = &brick->plug_in;
	t_plug *plug_out = &brick->plug_out;
	t_plug *plug_dst;
	t_vector *vector = plug->data;

	if(mode == mode_in)
		plug_dst = plug_in->src;
	else
		plug_dst = plug_out->dst;

	t_brick *brick_x = block_brick_get(block,"x");
	t_brick *brick_y;
	t_brick *brick_z;
	t_plug *plug_x; 
	t_plug *plug_y; 
	t_plug *plug_z; 

	if(brick_x)
	{
		brick_y = block_brick_get(block,"y");
		brick_z = block_brick_get(block,"z");

		plug_x = &brick_x->plug_intern;
		plug_y = &brick_y->plug_intern;
		plug_z = &brick_z->plug_intern;
	}


	// General
	cls_plug_disconnect_general(mode,plug);

	// change plug state
	if(plug->is_state_volatil)
	{
		plug_in->flow_in = 1;
		plug_in->open_in = 0;
		plug_out->open_out = 1;
		plug_out->flow_out = 0;
		plug_out->open_in = 0;
	}
	// For Vector
	else
	{
		plug_in->flow_in = 0;
		plug_in->open_in = 1;
	}

	if(brick_x)
	{
		plug_x->data = plug_x->data_memory;
		plug_y->data = plug_y->data_memory;
		plug_z->data = plug_z->data_memory;

		brick_x->state.draw_value = 1;
		brick_y->state.draw_value = 1;
		brick_z->state.draw_value = 1;

		// Remove XYZ's Parents
		plug_child_remove_all_parents(plug_x);
		plug_child_remove_all_parents(plug_y);
		plug_child_remove_all_parents(plug_z);

		t_context *C = ctx_get();

		// Set Vector Child of XYZ
		C->scene->store = 1;
		plug_add_parent(plug, plug_x);
		plug_add_parent(plug, plug_y);
		plug_add_parent(plug, plug_z);
		C->scene->store = 0;
	}

	// If Dst Volatil, Reset Pointer
	if(plug_dst->is_volatil)
	{
		vector->pointer = NULL;
	}
}

void plug_data_reset(t_plug *plug)
{
	int *zero;
	zero=0;

	switch (plug->data_type)
	{
		case (dt_int): flow_int_int(plug->data,zero); break;
		case (dt_float): flow_float_int(plug->data,zero); break;
		default: break;
	}
}

void plug_data_set(t_plug *plug,t_data_type type,void *data)
{
	switch (plug->data_type)
	{
		case (dt_int):

			switch(type)
			{
				case(dt_int): flow_int_int(plug->data,data); break;
				case(dt_float): flow_int_float(plug->data,data); break;
				default: break;
			}

			break;

		case (dt_float):

			switch(type)
			{
				case(dt_int): flow_float_int(plug->data,data); break;
				case(dt_float): flow_float_float(plug->data,data); break;
				default: break;
			}

			break;

		default:
			break;
	}
}

void plug_data_negate(t_plug *plug)
{
	switch (plug->data_type)
	{
		case (dt_int): negate_int(plug->data); break;
		case (dt_float): negate_float(plug->data); break;
		default: break;
	}
}

// input: 	plug_intern 
// return: 	plug_intern
t_plug *plug_get_src(t_plug *plug)
{
	// get plug_in
	t_plug *plug_src=plug->src;
	// get plug_out
	t_plug *plug_src_out=plug_src->src;

	if(plug_src_out)
	{
		//get plug_intern of out
		t_plug *plug_source=plug_src_out->src;

		// return target's plug intern
		return plug_source;
	}
	else
	{
		return NULL;
	}
}

t_plug *plug_get_dst(t_plug *plug)
{
	// get plug_out
	t_plug *plug_dst = plug->dst;
	// get dst
	t_plug *plug_dst_out = plug_dst->dst;

	if(plug_dst_out)
	{
		// get plug_intern
		t_plug *plug_distant = plug_dst_out->dst;

		return plug_distant;
	}
	else
	{
		return NULL;
	}
}

void plug_warning(t_plug *dst_plug,t_plug *src_plug)
{
	/*
	t_context *C=ctx_get();
	char msg[40];
	char *src_plug_type=data_name_get(src_plug->data_type);
	char *dst_plug_type=data_name_get(dst_plug->data_type);

	sprintf(msg,"%d(%s)(%s)-(%s)(%s)",C->app->frame,src_plug->name,src_plug_type,dst_plug->name,dst_plug_type);
	term_print(C->term,msg);
	*/
}

// FLOW

void _cls_flow_(t_plug *plug,void (* f)(t_plug_mode mode,t_plug *p1,t_plug *p2))
{
	t_brick *brick=plug->brick;

	t_plug *plug_in=&brick->plug_in;
	t_plug *plug_out=&brick->plug_out;

	// IN

	if(plug_in->is_connected)
	{
		t_plug *plug_origin = plug_in->src;

		if(plug_origin->open_out)
		{
			t_plug *src_plug=plug_get_src(plug);

			if(plug_in->flow_in)
			{
				f(mode_in,plug,src_plug);
			}
		}
	}
	else
	{
		f(mode_in,plug,NULL);
	}

	// OUT

	if(plug_out->is_connected)
	{
		t_plug *plug_origin = plug_out->dst;

		if(plug_origin->open_in)
		{
			t_plug *src_plug=plug_get_dst(plug);

			if(plug_out->flow_out)
			{
				f(mode_out,plug,src_plug);
			}
		}
	}
	else
	{
		f(mode_out,plug,NULL);
	}
}

// FLOAT

void __cls_plug_flow_float(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		float *data=plug->data;

		float increment=plug->brick->var.increment;

		if(data)
		{
			switch(src_type)
			{
				case dt_int:

					*data=(float)drf_int(src_plug->data);
					break;

				case dt_float:

					*data=drf_float(src_plug->data);
					break;
				default:
					plug_warning(plug,src_plug);
					break;
			}

			if(increment) *data=*data * increment;  
		}
	}

}

void cls_plug_flow_float(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_float);
}

// INT

void __cls_plug_flow_int(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		int *data=plug->data;

		float increment=plug->brick->var.increment;

		switch(src_type)
		{
			case dt_int:

				*data=drf_int(src_plug->data);
				break;

			case dt_float:

				*data=(int)drf_float(src_plug->data);
				break;
			case dt_lst:
				break;

			default:
				plug_warning(plug,src_plug);
				break;
		}

		if(increment) *data=*data * increment;  
	}
}


void cls_plug_flow_int(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_int);
}

// LST

void __cls_plug_flow_lst(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		t_brick *src_brick=src_plug->brick;

		switch(src_type)
		{
			// + LST
			case dt_lst:
				//copy pointer
				plug->data=src_plug->data;
				break;

			// +INT (REWIND)
			case dt_int:

				if(is(src_brick->name,"rewind"))
				{
					int *state = src_plug->data;

					if(*state == 1)
					{
						t_lst *lst=(t_lst *)plug->data;
						lst->current=lst->first;
					}
				}

				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_lst(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_lst);
}

// VLST

void __cls_plug_flow_vlst(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		switch(src_type)
		{
			// + LST
			case dt_vlst:
				//copy pointer
				plug->data=src_plug->data;
				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_vlst(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_vlst);
}

// VERTEX

void __cls_plug_flow_vertex(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		t_mesh *mesh;

		switch(src_type)
		{
			// + VLST
			case dt_vlst:

				mesh=plug->data;

				mesh->vertex=src_plug->data;
				mesh->state.need_update=1;

				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_vertex(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_vertex);
}

// MESH

void __cls_plug_flow_mesh(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		switch(src_type)
		{
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_mesh(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_mesh);
}

// OBJECT

void __cls_plug_flow_object(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		// node (pointer)
		t_node *node=plug->data;
		// object
		t_object *object=node->data;

		t_mesh *mesh;

		t_camera *camera_src;
		t_camera *camera_dst;

		switch(src_type)
		{
			// + MESH
			case dt_mesh:

				if(is(object->type,"mesh"))
				{
					mesh=src_plug->data;
					object->mesh=mesh;
				}

				break;

			// + CAMERA
			case dt_camera:

				if(is(object->type,"camera"))
				{
					if(src_plug->open_out)
					{
						camera_src=src_plug->data;
						camera_dst=object->data;
						camera_copy(camera_dst,camera_src);
					}
				}

				break;

			case dt_lst:
				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_object(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_object);
}

// POINTER

void __cls_plug_flow_pointer(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		t_object *object;

		switch(src_type)
		{
			// + MESH
			case dt_mesh:

				object=plug->data;
				object->mesh=src_plug->data;

				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_pointer(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_pointer);
}

// FOR 

void set_for_loop(t_block *block ,int state)
{
	t_context *C =ctx_get();
	// get branch (all bricks)
	t_lst *lst = block_branch_src_get(C,block);

	t_link *l;
	t_brick *b;
	t_plug *p;

	for(l=lst->first;l;l=l->next)
	{
		b=l->data;
		p=&b->plug_intern;
		p->is_in_loop = state;
	}

	lst_free(lst);
}

void __cls_plug_for_add_bricks(t_context *C, t_block *block)
{
	t_lst *lst=lst_new("lst");
	block_branch_get(lst,block);

	// reset states
	ctx_links_reset(C,lst);

	// add to loop
	t_lst *BRICKS = ctx_links_lst_get();

	t_link *l;
	t_brick *b;

	for(l=lst->first;l;l=l->next)
	{
		b = l->data;
		lst_add(BRICKS,l->data,b->name);
	}

	// free
	lst_free(lst);
}

// FOR

void __cls_plug_flow_operator_for(t_plug_mode mode,t_plug *plug,t_plug *plug_src)
{
	t_context *C =ctx_get();

	t_plug *plug_in = plug->src;
	t_brick *brick = plug->brick;

	// get bricks
	t_block *block = brick->block;
	t_brick *brick_indice = block_brick_get(block,"indice");
	t_brick *brick_vector = block_brick_get(block,"vector");

	t_plug *plug_indice = &brick_indice->plug_intern;
	t_plug *plug_indice_in = &brick_indice->plug_in;
	t_plug *plug_vector = &brick_vector->plug_intern;
	t_plug *plug_vector_in = &brick_vector->plug_in;

	int *data_indice = plug_indice->data;
	t_vector *vector = plug_vector->data;

	// IN
	if(mode == mode_in)
	{
		// reset vector
		vector->pointer = NULL;

		// if for connected
		if(plug_in->is_connected)
		{
			// get src
			t_plug *src_plug = plug_get_src(plug);
			t_data_type src_type = src_plug->data_type;

			t_vlst *vlst=NULL;

			switch(src_type)
			{
				// + vlst
				case dt_vlst:

					// set vlst
					vlst = src_plug->data;

					// Set vector
					if(vlst)
					{
						vector->pointer = vlst->data;
						vector->type = vlst->data_type;
						vector->length = vlst->length;
					}

					break;
					
				default:
					plug_warning(plug,src_plug);
					break;
			}

			// set vector
			if(plug_vector_in->is_connected)
			{
				if(vlst)
				{
					plug_indice_in->open_in = 1;

					if(brick->counter < vlst->count)
					{
						if(C->ui->show_step) term_log("[FOR][%d]",brick->counter);

						// Unlock Loop 
						set_for_loop(block,0);

						// Get Vlst Pointer
						float *ptr = vlst->data;

						// Set Vector Pointer
						vector->pointer = ptr + (vlst->length * brick->counter);

						// Set Indice
						*data_indice=brick->counter;

						// Add Loop
						__cls_plug_for_add_bricks(C,block);

						// Counter ++
						brick->counter++;
					}
					// Last Loop : counter > vlst
					else
					{
						if(C->ui->show_step)  term_log("[FOR][%d] END LOOP",brick->counter); 

						// reset vector
						vector->pointer = NULL;

						// reset counter
						brick->counter = 0;

						// reset init
						plug->is_init = 0;

						// reset indice
						*data_indice = 0;

						// reset is_in_loop
						set_for_loop(block,1);
					}
				}
				// no vlst
				else
				{
					// set loop
					set_for_loop(block,0);
					//
					plug_indice_in->open_in = 0;
				}
			}
			// plug vector in not connected
			else
			{
				*data_indice = 0;
				// set loop
				set_for_loop(block,0);
			}
		}
		// for not connected
		else
		{
			// set loop
			set_for_loop(block,0);
			//
			plug_indice_in->open_in = 0;
		}
	}
}

// GET

void __cls_plug_flow_operator_get(t_plug_mode mode,t_plug *plug,t_plug *plug_src)
{
	t_brick *brick = plug->brick;

	t_block *block = brick->block;

	t_brick *brick_indice = block_brick_get(block,"indice");
	t_brick *brick_result = block_brick_get(block,"result");

	t_plug *plug_result = &brick_result->plug_intern;
	t_plug *plug_indice = &brick_indice->plug_intern;

	t_lst *lst;
	t_vlst *vlst;

	// IN
	if(plug_src && mode == mode_in)
	{
		switch(plug_src->data_type)
		{
			// + LST
			case (dt_lst):
				
				// get lst
				lst = plug_src->data;

				// if lst
				if(lst)
				{
					if(!lst->current)
					{
						// set first
						if(lst->first)
						{
							lst->current = lst->first;
						}
					}
					else
					{
						t_link *link = lst->current;

						if(link->next)
						{
							lst->current = link->next;
						}
						else
						{
							//
						}

						//XXX change type

						plug_result->data_type=dt_camera;
						t_camera *camera=link->data;
						plug_result->data=camera;

					}
				}

				break;

			// +VLST

			case(dt_vlst):
				
				// get vlst
				vlst = plug_src->data;

				if(vlst)
				{
					t_plug _plug;
					_plug.data_type = dt_vector;

					// change type to vector
					if(brick_result->plug_intern.data_type != dt_vector)
						brick_type_change(brick_result,&_plug);

					// get indice
					int i = drf_int(plug_indice->data);

					// if < indice
					if(i < vlst->count)
					{
						t_vector *vector = plug_result->data;

						// get pointer
						float *ptr = vlst->data;
						// do pointer arithmetic
						vector->pointer = ptr + (vlst->length * i);

					}
					else
					{
						t_vector *vector = plug_result->data;
						set_int(plug_indice->data,vlst->count-1);
						float *ptr = vlst->data;
						vector->pointer = ptr + (vlst->length * (vlst->count-1));
					}

					t_plug *plug_result_out = &brick_result->plug_out;

					//XXX
					// open vector
					if(plug_result_out->is_connected)
					{
						t_plug *plug_vector = plug_get_dst(plug_result);

						if(plug_vector->data_type == dt_vector)
						{
							t_brick *brick_vector = plug_vector->brick;
							t_plug *plug_vector_in = &brick_vector->plug_in;

							// FLOW IN
							plug_vector_in->flow_in=1;

							t_block *block_vector = brick_vector->block;

							t_brick *brick_x = block_brick_get(block_vector,"x");

							if(brick_x)
							{
								t_brick *brick_y = block_brick_get(block_vector,"y");
								t_brick *brick_z = block_brick_get(block_vector,"z");

								brick_x->state.draw_value=1;
								brick_y->state.draw_value=1;
								brick_z->state.draw_value=1;

								brick_x->action = op_slider;
								brick_y->action = op_slider;
								brick_z->action = op_slider;
							}
						}
					}
				}

				break;
				

			default:
				printf(">> %s\n",data_name_get(plug_src->data_type));
				break;
		}
	}
}

// OPERATOR


void cls_plug_flow_operator(t_plug *plug)
{
	switch(plug->operator_type)
	{
		case(ot_null):
			break;
		case(ot_for):
			_cls_flow_(plug,__cls_plug_flow_operator_for);
			break;
		case(ot_get):

			_cls_flow_(plug,__cls_plug_flow_operator_get);
			break;
		default:
			break;
	}
}

// VECTOR

void __cls_plug_flow_vector(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	t_context *C = ctx_get();

	t_brick *brick = plug->brick;
	t_block *block = brick->block;

	t_brick *brick_x;
	t_brick *brick_y;
	t_brick *brick_z;

	t_plug *plug_x;
	t_plug *plug_y;
	t_plug *plug_z;

	t_plug *plug_x_in;
	t_plug *plug_y_in;
	t_plug *plug_z_in;

	t_vector *vector_self = plug->data;
	t_vector *vector_src;

	// Get XYZ
	brick_x = block_brick_get(block,"x");
	if(brick_x) 
	{
		brick_y = block_brick_get(block,"y");
		brick_z = block_brick_get(block,"z");

		plug_x = &brick_x->plug_intern;
		plug_y = &brick_y->plug_intern;
		plug_z = &brick_z->plug_intern;

		plug_x_in = &brick_x->plug_in;
		plug_y_in = &brick_y->plug_in;
		plug_z_in = &brick_z->plug_in;

	}

	// If Src or Dst
	if(src_plug)
	{
		t_data_type type = src_plug->data_type;

		switch(type)
		{
			// case VECTOR
			case dt_vector:

				// Get Vector Src
				vector_src = src_plug->data;

				// If Vector Pointer
				if(vector_src->pointer)
				{
					// Copy Pointer
					vector_self->pointer = vector_src->pointer;

					float *vector_pointer = vector_self->pointer;

					if(brick_x)
					{
						// XYZ Point To Pointer
						plug_x->data = vector_pointer;
						plug_y->data = vector_pointer+1;
						plug_z->data = vector_pointer+2;

						// Open XYZ
						plug_x_in->flow_in = 1;
						plug_y_in->flow_in = 1;
						plug_z_in->flow_in = 1;
					}

					if(C->ui->show_step) term_log("[VECTOR] set pointer %p",vector_self->pointer);
				}
				// Else if Mode In
				else if(mode == mode_in)
				{
					t_vlst *vlst_src = vector_src->vector;
					t_vlst *vlst_dst = vector_self->vector;

					float *v_src = vlst_src->data;
					float *v_dst = vlst_dst->data;

					// Copy Data
					vcp(v_dst,v_src);

					// If XYZ
					if(brick_x)
					{
						// Set XYZ Value
						plug_x->data = v_dst;
						plug_y->data = v_dst+1;
						plug_z->data = v_dst+2;

						plug_x->store_data = 0;
						plug_y->store_data = 0;
						plug_z->store_data = 0;
					}
				}


				break;
				
			default:
				break;
		}
	}
	else
	{
		if(mode == mode_in)
		{
			// If XYZ   
			if(brick_x)
			{
				// Flow XYZ to Vector Data 
				if(plug_x->data)
				{
					t_vlst *vlst = vector_self->vector;
					float *vector_data = vlst->data;

					vector_data[0] = drf_float(plug_x->data);
					vector_data[1] = drf_float(plug_y->data);
					vector_data[2] = drf_float(plug_z->data);
				}
			}
		}
	}
}

void cls_plug_flow_vector(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_vector);
}

// TRIGGER

void __cls_plug_flow_trigger(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
	t_brick *brick=plug->brick;

	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		int data;

		switch(src_type)
		{
			case(dt_int):

				data=drf_int(src_plug->data);
				if(data == 1)
					brick->action(brick);
				break;
				
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
	}
}

void cls_plug_flow_trigger(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_trigger);
}


// GENERIC

void cls_plug_flow_generic(t_plug *plug)
{
	t_plug *plug_in=plug->src;

	if(plug_in->is_connected)
	{
		t_plug *src_plug=plug_get_src(plug);
		t_data_type src_type=src_plug->data_type;

		switch(src_type)
		{
			default:
				plug_warning(plug,src_plug);
				break;
		}

	}

}

// CAMERA

void __cls_plug_flow_camera(t_plug_mode mode,t_plug *plug,t_plug *src_plug)
{
	if(src_plug)
	{
		t_data_type src_type=src_plug->data_type;

		t_camera *camera;

		switch(src_type)
		{
			case(dt_camera):
				camera = src_plug->data;
				plug->data = camera;

				break;
			default:
				plug_warning(plug,src_plug);
				break;
		}
	}
}

void cls_plug_flow_camera(t_plug *plug)
{
	_cls_flow_(plug,__cls_plug_flow_camera);
}

// CLS

// FLOAT

t_plug_class plug_float ={
	.cls_type="plug",
	.type=dt_float,
	.make=cls_plug_make_float,
	.flow=cls_plug_flow_float,
	.connect = cls_plug_connect_float,
	.disconnect = cls_plug_disconnect_float,
};

// INT

t_plug_class plug_int ={
	.cls_type="plug",
	.type=dt_int,
	.make=cls_plug_make_int,
	.flow=cls_plug_flow_int,
	.connect = cls_plug_connect_int,
	.disconnect = cls_plug_disconnect_int,
};

// STRING

t_plug_class plug_string ={
	.cls_type="plug",
	.type=dt_string,
	.make=cls_plug_make_string,
	.flow=cls_plug_flow_generic, //XXX
	.connect = cls_plug_connect_string,
	.disconnect = cls_plug_disconnect_string,
};

// POINTER

t_plug_class plug_pointer ={
	.cls_type="plug",
	.type=dt_pointer,
	.make=cls_plug_make_string,
	.flow=cls_plug_flow_pointer, //XXX
	.connect = cls_plug_connect_pointer,
	.disconnect = cls_plug_disconnect_pointer,
};

// MESH

t_plug_class plug_mesh ={
	.cls_type="plug",
	.type=dt_mesh,
	.make=cls_plug_make_mesh,
	.flow=cls_plug_flow_mesh, 
	.connect = cls_plug_connect_mesh,
	.disconnect = cls_plug_disconnect_mesh,
};

// VERTEX

t_plug_class plug_vertex ={
	.cls_type="plug",
	.type=dt_vertex,
	.make=cls_plug_make_vertex,
	.flow=cls_plug_flow_vertex, 
	.connect = cls_plug_connect_vertex,
	.disconnect = cls_plug_disconnect_vertex,
};

// FACE

t_plug_class plug_face ={
	.cls_type="plug",
	.type=dt_face,
	.make=cls_plug_make_face,
	.flow=cls_plug_flow_generic, //XXX
	.connect = cls_plug_connect_face,
	.disconnect = cls_plug_disconnect_face,
};

// VLST

t_plug_class plug_vlst ={
	.cls_type="plug",
	.type=dt_vlst,
	.make=cls_plug_make_vlst,
	.flow=cls_plug_flow_vlst, 
	.connect = cls_plug_connect_vlst,
	.disconnect = cls_plug_disconnect_vlst,
};

// LST

t_plug_class plug_lst ={
	.cls_type="plug",
	.type=dt_lst,
	.make=cls_plug_make_lst,
	.flow=cls_plug_flow_lst, 
	.connect = cls_plug_connect_lst,
	.disconnect = cls_plug_disconnect_lst,
};

// CAMERA

t_plug_class plug_camera ={
	.cls_type="plug",
	.type=dt_camera,
	.make=cls_plug_make_camera,
	.flow=cls_plug_flow_camera, 
	.connect = cls_plug_connect_camera,
	.disconnect = cls_plug_disconnect_camera,
};

// CHAR

t_plug_class plug_char ={
	.cls_type="plug",
	.type=dt_char,
	.make=cls_plug_make_char,
	.flow=cls_plug_flow_generic, //XXX
	.connect = cls_plug_connect_char,
	.disconnect = cls_plug_disconnect_char,
};

// OBJECT

t_plug_class plug_object ={
	.cls_type="plug",
	.type=dt_object,
	.make=cls_plug_make_object,
	.flow=cls_plug_flow_object, 
	.connect = cls_plug_connect_object,
	.disconnect = cls_plug_disconnect_object,
};

// SELECTOR

t_plug_class plug_selector ={
	.cls_type="plug",
	.type=dt_selector,
	.make=cls_plug_make_selector,
	.flow=cls_plug_flow_object, 
	.connect = cls_plug_connect_selector,
	.disconnect = cls_plug_disconnect_selector,
};

// TRIGGER

t_plug_class plug_trigger ={
	.cls_type="plug",
	.type=dt_trigger,
	.make=cls_plug_make_trigger,
	.flow=cls_plug_flow_trigger, 
	.connect = cls_plug_connect_trigger,
	.disconnect = cls_plug_disconnect_trigger,
};

// OPERATOR

t_plug_class plug_operator ={
	.cls_type="plug",
	.type=dt_operator,
	.make=cls_plug_make_operator,
	.flow=cls_plug_flow_operator, 
	.connect = cls_plug_connect_operator,
	.disconnect = cls_plug_disconnect_operator,
};

// VECTOR

t_plug_class plug_vector ={
	.cls_type="vector",
	.type=dt_vector,
	.make=cls_plug_make_vector,
	.flow=cls_plug_flow_vector,  
	.connect = cls_plug_connect_vector,
	.disconnect = cls_plug_disconnect_vector,
};


void cls_plug_make_float(t_plug *plug)
{
	plug->cls=&plug_float;
}

void cls_plug_make_int(t_plug *plug)
{
	plug->cls=&plug_int;
}

void cls_plug_make_string(t_plug *plug)
{
	plug->cls=&plug_int;
}

void cls_plug_make_pointer(t_plug *plug)
{
	plug->cls=&plug_pointer;
}


void cls_plug_make_mesh(t_plug *plug)
{
	plug->cls=&plug_mesh;
}

void cls_plug_make_vertex(t_plug *plug)
{
	plug->cls=&plug_vertex;
}

void cls_plug_make_face(t_plug *plug)
{
	plug->cls=&plug_face;
}

void cls_plug_make_vlst(t_plug *plug)
{
	plug->cls=&plug_vlst;
}

void cls_plug_make_lst(t_plug *plug)
{
	plug->cls=&plug_lst;
}

void cls_plug_make_camera(t_plug *plug)
{
	plug->cls=&plug_camera;
}

void cls_plug_make_char(t_plug *plug)
{
	plug->cls=&plug_char;
}

void cls_plug_make_object(t_plug *plug)
{
	plug->cls=&plug_object;
}

void cls_plug_make_selector(t_plug *plug)
{
	plug->cls=&plug_selector;
}

void cls_plug_make_trigger(t_plug *plug)
{
	plug->cls=&plug_trigger;
}

void cls_plug_make_operator(t_plug *plug)
{
	plug->cls=&plug_operator;
}

void cls_plug_make_vector(t_plug *plug)
{
	plug->cls=&plug_vector;
}

t_plug_class *plugs[] = {
	&plug_float,
	&plug_int,
	&plug_char,
	&plug_string,
	&plug_mesh,
	&plug_vertex,
	&plug_face,
	&plug_vlst,
	&plug_lst,
	&plug_camera,
	&plug_object,
	&plug_selector,
	&plug_trigger,
	&plug_operator,
	&plug_vector,
	};


// cls

void plug_cls_init(t_plug *plug)
{
	int i;
	int n = sizeof(plugs)/sizeof(plugs[0]);
	int found=0;

	for(i=0;i<n;i++)
	{
		if(plug->data_type==plugs[i]->type)
		{
			plugs[i]->make(plug);
			found=1;
			break;
		}
	}

	if(!found)
	{
		char *type=data_name_get(plug->data_type);
		printf("[ERROR:plug_cls_init] Unknown plug type [%s]\n",type);
	}
}

