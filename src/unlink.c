/* $Id$ */
/* Copyright (c) 2004-2020 Pierre Pronchery <khorben@defora.org> */
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

/* constants */
#ifndef PROGNAME
# define PROGNAME	"unlink"
#endif


/* unlink */
static int _unlink(char const * file)
{
	if(unlink(file) == -1)
	{
		fputs(PROGNAME ": ", stderr);
		perror(file);
		return 1;
	}
	return 0;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " file\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int o;

	while((o = getopt(argc, argv, "")) != -1)
		switch(o)
		{
			default:
				return _usage();
		}
	if(optind != argc - 1)
		return _usage();
	return (_unlink(argv[optind]) == 0) ? 0 : 2;
}
