/* $Id$ */
/* Copyright (c) 2014 Pierre Pronchery <khorben@defora.org> */
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
#include <time.h>


/* date */
/* private */
/* prototypes */
static int _date(void);
static int _date_error(char const * message, int ret);
static int _usage(void);


/* functions */
/* date */
static int _date(void)
{
	time_t t;
	struct tm tm;
	char buf[128];

	tzset();
	if((t = time(NULL)) == -1)
		return -_date_error("time", 1);
	if(localtime_r(&t, &tm) == NULL)
		return -_date_error("localtime_r", 1);
	if(strftime(buf, sizeof(buf), "%a %b %e %H:%M:%S %Z %Y", &tm) == 0)
		return -_date_error("strftime", 1);
	puts(buf);
	return 0;
}


/* error */
static int _date_error(char const * message, int ret)
{
	fputs("date: ", stderr);
	perror(message);
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: date\n", stderr);
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
	if(argc - optind != 0)
		return _usage();
	return (_date() == 0) ? 0 : 2;
}
