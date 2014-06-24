 /*
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "node.h"
#include "util.h"
#include "ctx.h"
#include "op.h"
#include "mesh.h"
#include "object.h"
#include "camera.h"
#include "list.h"
#include "vlst.h"
#include "set.h"
#include "set.h"
#include "block.h"
#include "brick.h"
#include "vector.h"
#include "ui.h"
#include "memory.h"
#include "datum.h"
#include "scene.h"

void object_default(t_node *node){}
void cls_object_link(t_object *self,t_node *target);
void cls_object_show(t_object *object);
void cls_object_init(t_object *object)
{
}

t_object_class object_point =
{
	.type=dt_point,
	.init=cls_object_init,
	.link=cls_object_link,
	.show=cls_object_show,
	.draw=cls_object_draw_point
};

t_object_class object_generic =
{
	.type=dt_object,
	.init=cls_object_init,
	.link=cls_object_link,
	.show=cls_object_show,
	.draw=cls_object_draw_mesh
};

t_object_class object_light =
{
	.type=dt_light,
	.init=cls_object_init,
	.link=cls_object_link,
	.show=cls_object_show,
	.draw=cls_object_draw_light
};

t_object_class object_camera =
{
	.type=dt_camera,
	.init=cls_object_init,
	.link=cls_object_link,
	.show=cls_object_show,
	.draw=cls_object_draw_camera
};

t_object_class object_image =
{
	.type=dt_image,
	.init=cls_object_init,
	.link=cls_object_link,
	.show=cls_object_show,
	.draw=cls_object_draw_image
};

void cls_object_show(t_object *object)
{
	printf("[OBJECT]\n");
	printf("name:[%s]\n",object->id.name);
	printf("idcol:");vprint3i(object->idcol,'\n');
	printf("loc:");vprint3f(object->loc,'\n');
	printf("rot:");vprint3f(object->rot,'\n');
	printf("size:");vprint3f(object->size,'\n');
}

void cls_object_link(t_object *self,t_node *target)
{
	if(target->type==dt_mesh)
	{
		t_mesh *mesh=target->data;
		self->mesh=mesh;
		target->users++;

	}
	else if(target->type==dt_list)
	{
		t_lst *lst=target->data;
		self->blocks=lst;
		target->users++;
	}
	else if(target->type==dt_camera)
	{
		t_camera *camera=target->data;
		self->data=camera;
		target->users++;
	}
	else printf("[ERROR:cls_object_link] Unknown node type %s",data_name_get(target->type));
}

void object_build( t_object *object, t_data_type type)
{
	if( type == dt_mesh)
	{
		object->cls=&object_generic;
	}
	else if( type == dt_light)
	{
		object->cls=&object_light;
	}
	else if( type == dt_camera)
	{
		object->cls=&object_camera;
	}
	else if( type == dt_point)
	{
		object->cls=&object_point;
	}
	else if( type == dt_image)
	{
		object->cls=&object_image;
	}
	else
	{
		printf("[ERROR object_build] Unknown type %s\n", data_name_get( type));
	}

	// Store object type
	object->type = type;
}

void object_draw_add(t_node *node,void (* func)(t_node *node))
{
	t_object *object = node->data;
	object->draw=func;
}

void object_method_add(t_node *node,const char method[],void (*func)(t_node *n))
{
	t_object *object = node->data;
	if(is(method,"action"))
	{
		object->action=func;
	}
	if(is(method,"update"))
	{
		object->update=func;
	}
}

void object_data_add(t_node *node,void *ptr)
{
	t_object *object = node->data;
	object->data=ptr;
}

void object_block_add( t_object *object, t_block *block)
{
	if( block)
	{
		list_add_data( object->blocks, block);
	}
}

t_block *object_block_get( t_object *object, const char *name)
{
	t_link *l;
	t_block *block;
	t_lst *lst = object->blocks;
	if( lst)
	{
		for( l = lst->first; l; l = l->next)
		{
			block = l->data;
			if( is( block->id.name, name)) return block;
		}
	}

	return NULL;
}

void *object_member_add( t_object *object, t_data_type type, const char *name, void *data)
{
	t_datum *datum = datum_add( type, name, data);
	
	list_add_data( object->members, datum);
	return datum->data;
}

t_datum *object_member_get( t_object *object, const char *name)
{
	t_link *l = lst_link_find_by_name( object->members, name);
	if( l) return l->data;
	else return NULL;
}

// REF

void *object_get_ref(t_object *object, const char *ref)
{
	void *p;

	if(is(ref,"loc_x"))  p=&object->loc[0]; 
	else if(is(ref,"loc_y"))  	p=&object->loc[1]; 
	else if(is(ref,"loc_z"))  	p=&object->loc[2]; 
	else if(is(ref,"rot_x"))  	p=&object->rot[0]; 
	else if(is(ref,"rot_y"))  	p=&object->rot[1]; 
	else if(is(ref,"rot_z"))  	p=&object->rot[2]; 
	else if(is(ref,"scl_x"))  	p=&object->size[0]; 
	else if(is(ref,"scl_y"))  	p=&object->size[1]; 
	else if(is(ref,"scl_z"))  	p=&object->size[2]; 
	else
	{
		printf("[ERROR object_get_ref] Unknown ref %s \n",ref);
		return NULL;
	}

	return p;
}

// REMOVE

void _object_free(t_object *object)
{
	if(object->mesh) _mesh_free(object->mesh);
	// object->data is NULL 
	// object->ref is NULL
	// object->blocks is NULL
}

// FREE

void object_free(t_object *object)
{
	t_context *C=ctx_get();
	t_scene *sc=C->scene;

	// free data
	scene_remove_data_node( sc, object->id.node);

	// free ref block 
	if(object->ref)
	{
		// remove from global list
		//t_lst *lst = get_target_list(C);
		t_set *set = object->ref->set;
		t_lst *lst = set->blocks;

		list_remove_by_ptr(lst,object->ref);
		// free block
		scene_delete(sc,object->ref);
	}

	if(object->mesh) scene_delete(sc,object->mesh);
	if(object->data) scene_delete(sc,object->data);
	if(object->blocks)
	{
		list_cleanup(object->blocks);
		scene_delete(sc,object->blocks);
	}

	mem_free( object, sizeof( t_object));
}


// CLONE

t_object *object_clone(t_object *object)
{
	if(object)
	{
		t_object *clone = object_new(object->id.name);

		vcp3f(clone->loc,object->loc);
		vcp3f(clone->rot,object->rot);
		vcp3f(clone->size,object->size);
		vcp3i(clone->idcol,object->idcol);
		
		clone->mesh = mesh_clone(object->mesh);
		clone->data = NULL;
		clone->blocks = NULL;
		clone->ref = NULL;

		clone->is_selected = object->is_selected;

		clone->update = object->update;
		clone->action = object->action;
		clone->draw = object->draw;

		clone->cls = object->cls;

		return clone;
	}
	else
	{
		return NULL;
	}
}

// REBIND

void object_rebind(t_scene *sc,void *ptr)
{
	t_object *object=(t_object *)ptr;

	object_build( object, object->type);
	
	rebind(sc,"object","mesh",(void **)&object->mesh);
	rebind(sc,"object","blocks",(void **)&object->blocks);
	rebind(sc,"object","members",(void **)&object->members);
	rebind(sc,"object","ref",(void **)&object->ref);
	rebind(sc,"object","data",(void **)&object->data);

	object->action=NULL;
	object->update=NULL;
}

// ADD

t_node *object_add( t_data_type type, const char *name)
{
	t_context *C = ctx_get();

	// make object
	t_node *node = object_make( type, name);
	t_object *object = node->data;

	if(C->ui->add_bricks)
	{
		// add data node
		scene_add_data_node(C->scene,"app_node","object",name,node);

		// New Block
		t_node *node_block=add_block(C,name);
		t_block *block=node_block->data;

		object->ref=block;

		// add selector
		add_part_selector(C,block,name,node,dt_object);

		// Add Offset
		add_block_offset(C,block);
	}

	return node;
}

// MAKE

t_node *object_make( t_data_type type, const char *name)
{
	t_context *C = ctx_get();
	t_scene *sc = C->scene;

	// new object
	t_node *node = scene_add( C->scene, dt_object, name);
	t_object *object=node->data;

	// build cls
	object_build( object, type);

	// new list (bricks list)
	t_node *list = scene_add(C->scene,dt_list,"object_blocks");


	// bind list
	object->cls->link(object,list);

	// Members
	t_node *node_members = scene_add(C->scene,dt_list,"object_members");
	t_lst *lst = node_members->data;
	object->members = lst;

	int col[3];
	scene_color_get(sc,col);
	vcp3i(object->idcol,col);

	return node;
}

// NEW

void *object_new(const char *name)
{
	t_object *object = (t_object *)mem_malloc(sizeof(t_object));

	id_init(&object->id, name);

	vset(object->loc,0,0,0);
	vset(object->rot,0,0,0);
	vset(object->size,1,1,1);
	vseti(object->idcol,0,0,0);
	
	object->mesh=NULL;
	object->data=NULL;
	object->blocks=NULL;
	object->ref=NULL;
	object->members = NULL;

	object->is_selected = 0;
	object->hover = 0;
	object->is_edit_mode = 0;

	object->update=object_default;
	object->action=NULL;
	object->draw=NULL;
	object->draw_screen=NULL;
	object->shader = NULL;

	return object;
}
