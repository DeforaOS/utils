/* $Id$ */
/* Copyright (c) 2004-2014 Pierre Pronchery <khorben@defora.org> */
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
#include <stdio.h>
#include <libgen.h>
#include <string.h>

#ifndef PROGNAME
# define PROGNAME "basename"
#endif


/* basename */
/* private */
/* prototypes */
static int _basename(char * arg, char const * suf);

static int _basename_usage(void);


/* functions */
/* basename */
static int _basename(char * arg, char const * suf)
{
	char * str;
	int slen;
	int alen;

	str = basename(arg);
	if(suf != NULL)
	{
		slen = strlen(str);
		alen = strlen(suf);
		if(alen < slen && strcmp(suf, &str[slen - alen]) == 0)
			str[slen - alen] = '\0';
	}
	puts(str);
	return 0;
}


/* basename_usage */
static int _basename_usage(void)
{
	fputs("Usage: " PROGNAME " string [suffix]\n", stderr);
	return 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int o;

	while((o = getopt(argc, argv, "")) != -1)
		switch(o)
		{
			default:
				return _basename_usage();
		}
	if(optind != argc - 1 && optind != argc - 2)
		return _basename_usage();
	return (_basename(argv[optind], argv[optind + 1]) == 0) ? 0 : 2;
}
