/* $Id$ */
/* Copyright (c) 2005-2020 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"renice"
#endif


/* renice */
static int _renice_error(char const * message, int ret);

static int _renice(int nice, int type, int argc, char * argv[])
{
	int i;
	int ret = 0;
	int id;
	char * p;

	for(i = 0; i < argc; i++)
	{
		id = strtol(argv[i], &p, 10);
		if(argv[i][0] == '\0' || *p != '\0')
		{
			fprintf(stderr, "%s%s%s", PROGNAME ": ", argv[i],
					"Invalid ID\n");
			ret |= 1;
			continue;
		}
		if(setpriority(type, id, nice) != 0)
			ret |= _renice_error(argv[i], 1);
	}
	return ret;
}

static int _renice_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " -n increment [-g | -p | -u] ID...\n\
  -n	Priority to set\n\
  -g	Process group IDs\n\
  -p	Integer process IDs\n\
  -u	User IDs\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int nice = 0;
	int type = PRIO_PROCESS;
	int o;
	char * p;

	while((o = getopt(argc, argv, "n:gpu")) != -1)
		switch(o)
		{
			case 'n':
				nice = strtol(optarg, &p, 10);
				if(*optarg == '\0' || *p != '\0')
					return _usage();
				break;
			case 'g':
				type = PRIO_PGRP;
				break;
			case 'p':
				type = PRIO_PROCESS;
				break;
			case 'u':
				type = PRIO_USER;
				break;
			default:
				return _usage();
		}
	if(argc - optind < 1)
		return _usage();
	return (_renice(nice, type, argc - optind, &argv[optind]) == 0) ? 0 : 2;
}
