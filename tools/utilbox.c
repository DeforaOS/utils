/* $Id$ */
/* Copyright (c) 2011-2025 Pierre Pronchery <khorben@defora.org> */
/* This file is part of DeforaOS Unix utils */
/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */



#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include "utilbox.h"

/* constants */
#ifndef PROGNAME
# define PROGNAME	"utilbox"
#endif


/* utilbox */
/* private */
/* prototypes */
static int _utilbox(char const * name, int argc, char * argv[]);
static int _utilbox_error(char const * message, int ret);
static int _utilbox_list(Call * calls);
static int _utilbox_usage(void);


/* functions */
/* utilbox */
static int _utilbox(char const * name, int argc, char * argv[])
{
	size_t i;

	for(i = 0; calls[i].name != NULL; i++)
		if(strcmp(calls[i].name, name) == 0)
			return calls[i].call(argc, argv);
	return -1;
}


/* utilbox_error */
static int _utilbox_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}


/* utilbox_list */
static int _utilbox_list(Call * calls)
{
	size_t i;

	for(i = 0; calls[i].name != NULL; i++)
		puts(calls[i].name);
	return 0;
}


/* utilbox_usage */
static int _utilbox_usage(void)
{
	fputs("Usage: " PROGNAME " program [arguments...]\n"
"       " PROGNAME " -l\n"
"  -l	List available programs\n", stderr);
	return 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int ret;
	char * p;
	char const * q;
	int o;

	if((p = strdup(argv[0])) == NULL)
		return _utilbox_error(NULL, 2);
	q = basename(p);
	ret = _utilbox(q, argc, argv);
	free(p);
	if(ret >= 0)
		return ret;
	while((o = getopt(argc, argv, "l")) != -1)
		switch(o)
		{
			case 'l':
				return _utilbox_list(calls);
			default:
				return _utilbox_usage();
		}
	if(optind == argc)
		return _utilbox_usage();
	if((ret = _utilbox(argv[optind], argc - optind, &argv[optind])) >= 0)
		return ret;
	fprintf(stderr, "%s: %s: command not found\n", PROGNAME, argv[optind]);
	return 127;
}
