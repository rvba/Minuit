/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "lo.h"

int osc_server_done = 0;
int osc_debug = 0;

void osc_error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
}

int osc_handler_generic( const char *path, const char *types, lo_arg ** argv, int argc, void *data, void *user_data)
{
	if( osc_debug)
	{
		int i;
		printf("path: <%s>\n", path);
		for (i = 0; i < argc; i++)
		{
			printf("arg %d '%c' ", i, types[i]);
			lo_arg_pp((lo_type)types[i], argv[i]);
			printf("\n");
		}
	}

	return 1;
}

int osc_handler_vector(const char *path, const char *types, lo_arg ** argv, int argc, void *data, void *user_data)
{
    printf("[OSC SERVER][VECTOR %f %f %f]\n", argv[0]->f, argv[1]->f, argv[2]->f);

    return 0;
}

int osc_handler_quit(const char *path, const char *types, lo_arg ** argv, int argc, void *data, void *user_data)
{
    osc_server_done = 1;
    printf("[OSC SERVER] exit\n");

    return 0;
}

int osc_server( int port)
{
	char sport[8];

	if( !port)
	{
		printf("[OSC SERVER] No valid port\n");
		return 0;
	}
	else
	{
		snprintf( sport, 8, "%d", port);
		printf("[OSC SERVER] Init server at %d\n", port);
	}

	lo_server_thread st = lo_server_thread_new( sport, osc_error);

	lo_server_thread_add_method(st, NULL, NULL, osc_handler_generic, NULL);
	lo_server_thread_add_method(st, "/a/b/c", "fff", osc_handler_vector, NULL);
	lo_server_thread_add_method(st, "/quit", "", osc_handler_quit, NULL);

	lo_server_thread_start(st);

	while ( !osc_server_done)
	{
		usleep(1000);
	}

	lo_server_thread_free(st);

	return 0;
}


// CLIENT


int osc_send( const char *port, const char *msg)
{
	lo_address t = lo_address_new(NULL, port);

	if( !lo_send( t, "/msg" , "s", msg))
	{
		printf("OSC error %d: %s\n", lo_address_errno(t),
		lo_address_errstr(t));
	}

	return 0;
}

int osc_send_quit( const char *port)
{
	lo_address t = lo_address_new(NULL, port);

	if( !lo_send( t, "/quit" , ""))
	{
		printf("OSC error %d: %s\n", lo_address_errno(t),
		lo_address_errstr(t));
	}

	return 0;
}

int osc_send_vector( const char *port, const char *msg)
{
	lo_address t = lo_address_new(NULL, port);

	if( !lo_send( t, "/a/b/c" , "fff" , 10.0f, 10.0f, 10.0f))
	{
		printf("OSC error %d: %s\n", lo_address_errno(t),
		lo_address_errstr(t));
	}

	return 0;
}

int osc_client( int port)
{
	char sport[8];
	int msg_size = 32;
	char msg[msg_size];
	int get_vector = 0;
	int send_vector = 0;

	if( !port)
	{
		printf("[OSC CLIENT] No valid port\n");
		return 0;
	}
	else
	{
		snprintf( sport, 8, "%d", port);
		printf("[OSC CLIENT] Init server at %d\n", port);
	}

	while( 1)
	{
		if( get_vector)
		{
			printf("vector:");
			get_vector = 0;
			send_vector = 1;
		}
		else
		{
			printf("msg:");
		}

		scanf( "%31s", msg);

		if( is( msg, "q"))
		{
			osc_send_quit( sport);
			return 1;
		}
		else if( is( msg, "vector")) get_vector = 1;

		if( get_vector)
		{
		}
		else if( send_vector)
		{
			osc_send_vector( sport, msg); 
			send_vector = 0;
		}
		else
		{
			osc_send( sport, msg); 
		}

		usleep(1000);
	}


	return 1;
}





