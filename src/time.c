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



#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"time"
#endif


/* time */
static int _time_error(char const * error, int ret);
static int _time_exec(char * argv[]);
static int _time_print(long real, long user, long sys);

static int _time(char * argv[])
{
	pid_t pid;
	int status;
	struct tms tmsbuf;
	clock_t cbefore, cafter;

	if((cbefore = times(&tmsbuf)) == (clock_t)-1)
		return _time_error("times", 2);
	if((pid = fork()) == -1)
		return _time_error("fork", 2);
	if(pid == 0)
		return _time_exec(argv);
	for(;;)
	{
		if(waitpid(pid, &status, 0) == -1)
			return _time_error("waitpid", 2);
		if(WIFEXITED(status))
			break;
	}
	if((cafter = times(&tmsbuf)) == (clock_t)-1)
		return _time_error("times", 2);
	return _time_print(cafter - cbefore,
			tmsbuf.tms_utime + tmsbuf.tms_cutime,
			tmsbuf.tms_stime + tmsbuf.tms_cstime);
}

static int _time_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}

static int _time_exec(char * argv[])
{
	execvp(argv[0], argv);
	if(errno == ENOENT)
		return _time_error(argv[0], 127);
	return _time_error(argv[0], 126);
}

static int _time_print(long real, long user, long sys)
{
	static const char * args[3] = { "real", "user", "sys" };
	long * argl[3];
	int i;
	long l;
	long r;

	argl[0] = &real;
	argl[1] = &user;
	argl[2] = &sys;
	if((r = sysconf(_SC_CLK_TCK)) == -1)
	{
		_time_error("sysconf", 0);
		r = 100;
	}
	for(i = 0; i < 3; i++)
	{
		l = *argl[i] / r;
		if(l * r > *argl[i])
			l--;
		/* FIXME */
		fprintf(stderr, "%s %ld.%02lds\n", args[i], l, *argl[i] % r);
	}
	return 0;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-p] utility [argument...]\n\
  -p	Force the POSIX locale\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int o;

	while((o = getopt(argc, argv, "p")) != -1)
	{
		if(o == 'p')
			continue;
		return _usage();
	}
	if(optind == argc)
		return _usage();
	return _time(&argv[optind]);
}
