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



#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"file"
#endif


/* file */
/* types */
typedef unsigned int Prefs;
#define FILE_PREFS_h	1
#define FILE_PREFS_m	2
#define FILE_PREFS_M	4
#define FILE_PREFS_d	6
#define FILE_PREFS_i	8


/* functions */
/* file */
static int _file_do(Prefs * p, char const * filename);
static int _file(Prefs * p, int argc, char * argv[])
{
	int ret = 0;
	int i;

	for(i = 0; i < argc; i++)
		ret += _file_do(p, argv[i]);
	return ret;
}

static int _file_do(Prefs * p, char const * filename)
{
	struct stat st;
	int (*statfunc)(const char *, struct stat*) = *p & FILE_PREFS_h
		? lstat : stat;

	printf("%s: ", filename);
	if(statfunc(filename, &st) != 0)
	{
		puts("cannot open file");
		return 0;
	}
	if(S_ISLNK(st.st_mode))
		fputs("symbolic link to ", stdout);
	if(S_ISBLK(st.st_mode))
		fputs("block special ", stdout);
	else if(S_ISCHR(st.st_mode))
		fputs("character special ", stdout);
	else if(S_ISDIR(st.st_mode))
		fputs("directory ", stdout);
	else if(S_ISFIFO(st.st_mode))
		fputs("fifo ", stdout);
	else if(S_ISSOCK(st.st_mode))
		fputs("socket ", stdout);
	else
	{
		if(*p & FILE_PREFS_i)
			fputs("regular file ", stdout);
		else if(st.st_size == 0)
			fputs("empty ", stdout);
		if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
			fputs("executable ", stdout);
	}
	puts("data");
	return 0;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-dh][-M file][-m file] file ...\n\
       " PROGNAME " -i [-h] file ...\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	Prefs p = 0;
	int o;

	while((o = getopt(argc, argv, "dhM:m:i")) != -1)
		switch(o)
		{
			case 'd':
				if(p & FILE_PREFS_i)
					return _usage();
				p |= FILE_PREFS_d;
				break;
			case 'h':
				p |= FILE_PREFS_h;
				break;
			case 'i':
				if(p != 0)
					return _usage();
				p = FILE_PREFS_i;
				break;
			case 'M':
				if(p & FILE_PREFS_i)
					return _usage();
				p |= FILE_PREFS_M;
				break;
			case 'm':
				if(p & FILE_PREFS_i)
					return _usage();
				p |= FILE_PREFS_m;
				break;
			default:
				return _usage();
		}
	return _file(&p, argc - optind, &argv[optind]);
}
