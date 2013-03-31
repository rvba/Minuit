/* 
 * Copyright (c) 2012 Milovann Yanatchkov 
 *
 * This file is part of Minuit, a free software
 * licensed under the GNU General Public License v2
 * see /LICENSE for more information
 *
 */

#include "util.h"

t_file *LOG_FILE;

void log_init(void)
{
	t_file *file = file_new("mn.log");
	//file->file=fopen(file->path,"w");
	file->file=fopen(file->location,"w");
	fprintf(file->file,"LOG\n");
	file_close(file);
	LOG_FILE=file;
}

void __log__(int status,char *fmt, ...)
{
	if(status)
	{
		t_file *file=LOG_FILE;
		//file->file=fopen(file->path,"a");
		file->file=fopen(file->location,"a");

		va_list ap;
		va_start(ap,fmt);
		vfprintf(file->file,fmt,ap);
		va_end(ap);

		file_close(file);
	}
}

inline void negate_int(void *_dst)
{
	int *dst = _dst;
	*dst = - (*dst);
}

inline void negate_float(void *_dst)
{
	float *dst = _dst;
	*dst = - (*dst);
}

inline void set_int(void *_ptr,int i)
{
	int *ptr = (int *)_ptr;
	*ptr=i;
}

inline void set_float(void *_ptr,float i)
{
	float *ptr = (float *)_ptr;
	*ptr=i;
}

inline void flow_int_int(void *_dst, void *_src)
{
	int *dst = _dst;
	int *src = _src;

	*dst = *src;
}

inline void flow_int_float(void *_dst, void *_src)
{
	int *dst = _dst;
	float *src = _src;

	*dst = (int) *src;
}

inline void flow_float_float(void *_dst, void *_src)
{
	float *dst = _dst;
	float *src = _src;

	*dst = *src;
}

inline void flow_float_int(void *_dst, void *_src)
{
	float *dst = _dst;
	int *src = _src;

	*dst = (float)*src;
}

inline int drf_int(void *ptr)
{
	return *((int *)ptr);
}

inline float drf_float(void *ptr)
{
	return *((float *)ptr);
}

inline char drf_char(void *ptr)
{
	return *((char *)ptr);
}

inline char *drf_string(void *ptr)
{	
	return (char *)ptr;
}

void set_name(char *dst,const char *src)
{
	strncpy(dst,src,_NAME_);
	dst[_NAME_-1]='\0';
}

void set_name_long(char *dst,const char *src)
{
	strncpy(dst,src,_NAME_LONG_);
	dst[_NAME_LONG_-1]='\0';
}

void set_path(char *dst,const char *src)
{
	strncpy(dst,src,_PATH_);
	dst[_PATH_-1]='\0';
}

inline int is(const char a[],const char b[])
{
	if(strcmp(a,b)==0) return 1;
	else return 0;
}

void clock_init(t_clock *clock)
{
	struct timeval tv;
	gettimeofday(&clock->start,NULL);
	gettimeofday(&tv,NULL);
	clock->start_time=tv.tv_sec * 1000 + tv.tv_usec/1000;
	clock->limit=0.05;
}

// CLOCK

t_clock *clock_new(void)
{
	t_clock *clock = (t_clock *)malloc(sizeof(t_clock));

	clock->freq=1.0;
	clock->delta=0;
	clock->factor=0;
	clock->limit = PROCESS_LIMIT;
	clock->now.tv_sec=0;
	clock->now.tv_usec=0;
	clock->before.tv_sec=0;
	clock->before.tv_usec=0;

	clock->framerate=25;
	clock->frame_before.tv_sec=0; 
	clock->frame_before.tv_usec=0; 
	clock->frame_now.tv_sec=0;
	clock->frame_now.tv_usec=0;
	
	clock->start.tv_sec=0;
	clock->start.tv_usec=0;

	clock->msec=0;
	clock->sec=0;
	clock->min=0;

	return clock;
}








