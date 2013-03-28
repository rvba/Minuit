/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "context.h"

#ifdef MIDI
#include "midi.h"
#endif

int main(int argc, char **argv)
{
	t_context *C = ctx_init(argc,argv);
	
	app_launch(C->app);

	return 0;
}
