/* $Id$ */
/* Copyright (c) 2009 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Unix utils */
/* utils is not free software; you can redistribute it and/or modify it under
 * the terms of the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * Unported as published by the Creative Commons organization.
 *
 * utils is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the Creative Commons Attribution-NonCommercial-
 * ShareAlike 3.0 Unported license for more details.
 *
 * You should have received a copy of the Creative Commons Attribution-
 * NonCommercial-ShareAlike 3.0 along with utils; if not, browse to
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ */



#include <unistd.h>
#include <stdio.h>


/* rmdir */
static int _rmdir_error(char const * message, int ret);

static int _rmdir_p(char * pathname);
static int _rmdir(int flagp, int filec, char * filev[])
{
	int ret = 0;
	int i;

	for(i = 0; i < filec; i++)
	{
		if(rmdir(filev[i]) != 0)
			ret |= _rmdir_error(filev[i], 1);
		if(flagp && _rmdir_p(filev[i]) != 0)
			ret |= 1;
	}
	return ret;
}

static int _rmdir_error(char const * message, int ret)
{
	fputs("rmdir: ", stderr);
	perror(message);
	return ret;
}

static int _rmdir_p(char * pathname)
{
	char * str;

	for(str = pathname; *str != '\0'; str++);
	for(str--; str > pathname && *str == '/'; str--);
	while(--str > pathname)
	{
		if(*str != '/')
			continue;
		for(*str = '\0'; --str > pathname && *str == '/'; *str = '\0');
		if(*str == '\0')
			return 0;
		if(rmdir(pathname) == -1)
			return _rmdir_error(pathname, 1);
	}
	return 0;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: rmdir [-p] dir...\n\
  -p	Remove all directories in a pathname\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int flagp = 0;
	int o;

	while((o = getopt(argc, argv, "p")) != -1)
		switch(o)
		{
			case 'p':
				flagp = 1;
				break;
			default:
				return _usage();
		}
	if(optind == argc)
		return _usage();
	return (_rmdir(flagp, argc - optind, &argv[optind]) == 0) ? 0 : 2;
}
