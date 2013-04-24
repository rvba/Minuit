/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#ifndef _PROCESS_H
#define _PROCESS_H

typedef struct Process t_process;

struct Process
{
	int id;
	int id_chunk;
	short users;
	char name[_NAME_];

	pthread_t thread;
	t_clock *clock;

	void *(* func)(void *ptr);
	void *(* loop)(void *ptr);
	void *(* exec)(void *ptr);

	int exit;
	int limit;
	int play;
	int cycle;
	int done;
	int busy;
};

void process_free(t_process *process);

#endif
