/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#ifndef __SCREEN_H_
#define __SCREEN_H_

#include "common.h"

struct Scene;
struct MINscreen;

typedef struct MINscreen
{
	int id;
	int id_chunk;
	short users;
	char name[_NAME_];

	int idcol[3];

	int is_active;
	int is_visible;
	int width;
	int height;
	int zoom;
	int pan_x;
	int pan_y;

	void (* draw) (struct MINscreen *screen);
	void (* keymap) (unsigned char key);

}t_screen;

// SCREEN BROWSER.C

void screen_browser_make(void);

// SCREEN_INIT.C

struct Node *screen_new_generic(char *name);
void screen_main_make(void);
void screen_sets_make(void);
void screen_bricks_make(void);

void screen_sets(t_screen *screen);

// SCREEN.C
void screen_on(t_screen *screen);
void screen_off(t_screen *screen);

void screen_switch_by_name(char *name);
void screen_switch_to_main(void);


void screen_bricks(t_screen *screen);
void screen_generic(t_screen *screen);
void screen_main(t_screen *screen);
void screen_free(t_screen *screen);
t_screen *screen_rebind(struct Scene *scene, void *ptr);
t_screen *screen_new(const char *name);
void screen_init(void);

#endif
