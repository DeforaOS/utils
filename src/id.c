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



#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"id"
#endif


/* id */
static int _id_error(char const * message, int ret);
static int _id_G(char const * user, int flagn);
static int _id_g(char const * user, int flagn, int flagr);
static int _id_u(char const * user, int flagn, int flagr);
static int _id_all(char const * user);
static gid_t * _id_getgroups(int * n);

static int _id(char const * user, int flag, int flagn, int flagr)
{
	if(flag == 'G')
		return _id_G(user, flagn);
	if(flag == 'g')
		return _id_g(user, flagn, flagr);
	if(flag == 'u')
		return _id_u(user, flagn, flagr);
	return _id_all(user);
}

/* _id_error */
static int _id_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}

/* _id_G */
static int _id_G(char const * user, int flagn)
{
	gid_t * groups;
	int n;
	int i;
	struct group * gr;
	struct passwd * pw;
	char * g;
	char ** p;

	if(user == NULL)
	{
		if((groups = _id_getgroups(&n)) == NULL && n < 0)
			return 1;
		for(i = 0; i < n; i++)
			if(flagn != 0 && (gr = getgrgid(groups[i])) != NULL)
				printf("%s%s", (i > 0) ? " " : "", gr->gr_name);
			else
				printf("%s%u", (i > 0) ? " " : "", groups[i]);
		putchar('\n');
		free(groups);
		return 0;
	}
	if((pw = getpwnam(user)) == NULL)
		return _id_error(user, 1);
	if((gr = getgrgid(pw->pw_gid)) == NULL)
		return _id_error("getgrgid", 1);
	if(flagn == 0)
		printf("%u", (unsigned)gr->gr_gid);
	else
		fputs(gr->gr_name, stdout);
	if((g = strdup(gr->gr_name)) == NULL)
		return _id_error(gr->gr_name, 1);
	setgrent();
	for(gr = getgrent(); gr != NULL; gr = getgrent())
		for(p = gr->gr_mem; p != NULL && *p != NULL; p++)
		{
			if(strcmp(pw->pw_name, *p) != 0
					|| strcmp(g, gr->gr_name) == 0)
				continue;
			if(flagn == 0)
				printf(" %u", (unsigned)gr->gr_gid);
			else
				printf(" %s", gr->gr_name);
		}
	putchar('\n');
	endgrent();
	free(g);
	return 0;
}

/* _id_g */
static int _id_g(char const * user, int flagn, int flagr)
{
	struct group * gr;

	if(user == NULL)
	{
		if(flagn == 0)
		{
			printf("%u\n", flagr ? (unsigned)getegid()
					: (unsigned)getgid());
			return 0;
		}
		if((gr = getgrgid(flagr ? getegid() : getgid())) == NULL)
			return _id_error("getgrgid", 1);
		printf("%s\n", gr->gr_name);
		return 0;
	}
	if((gr = getgrnam(user)) == NULL)
		return _id_error(user, 1);
	if(flagn == 0)
		printf("%u\n", (unsigned)gr->gr_gid);
	else
		printf("%s\n", gr->gr_name);
	return 0;
}

/* _id_u */
static int _id_u(char const * user, int flagn, int flagr)
{
	struct passwd * passwd;

	if(user == NULL)
	{
		if(flagn == 0)
		{
			printf("%u\n", flagr ? geteuid() : getuid());
			return 0;
		}
		if((passwd = getpwuid(flagr ? geteuid() : getuid())) == NULL)
			return _id_error("getpwuid", 1);
		printf("%s\n", passwd->pw_name);
		return 0;
	}
	if((passwd = getpwnam(user)) == NULL)
		return _id_error(user, 1);
	if(flagn == 0)
		printf("%u\n", passwd->pw_uid);
	else
		printf("%s\n", passwd->pw_name);
	return 0;
}

/* _id_all */
static struct group * _print_gid(gid_t gid);

static int _id_all(char const * user)
{
	struct passwd * pw;
	struct group * gr;
	char * u;
	int n;
	gid_t * groups;
	int i;

	if(user == NULL)
	{
		if((pw = getpwuid(getuid())) == NULL)
		{
			putchar('\n');
			return _id_error("getpwuid", 1);
		}
		printf("uid=%u(%s) ", (unsigned)pw->pw_uid, pw->pw_name);
		if((gr = _print_gid(pw->pw_gid)) == NULL)
			return 1;
		if((u = strdup(gr->gr_name)) == NULL)
		{
			putchar('\n');
			return _id_error(gr->gr_name, 1);
		}
		if(geteuid() != getuid())
		{
			if((pw = getpwuid(geteuid())) == NULL)
			{
				putchar('\n');
				free(u);
				return _id_error("getpwuid", 1);
			}
			printf(" euid=%u(%s) e", (unsigned)pw->pw_uid,
					pw->pw_name);
			if(_print_gid(pw->pw_gid) == NULL)
			{
				free(u);
				return 1;
			}
		}
	}
	else
	{
		if((pw = getpwnam(user)) == NULL)
			return _id_error(user, 1);
		printf("uid=%u(%s) ", (unsigned)pw->pw_uid, pw->pw_name);
		if((gr = _print_gid(pw->pw_gid)) == NULL)
			return 1;
		if((u = strdup(gr->gr_name)) == NULL)
		{
			putchar('\n');
			return _id_error(gr->gr_name, 1);
		}
	}
	if((groups = _id_getgroups(&n)) == NULL && n < 0)
		return 1;
	printf("%s", " groups=");
	for(i = 0; i < n; i++)
		if((gr = getgrgid(groups[i])) == NULL)
			printf("%s%u", (i == 0) ? "" : ",",
					(unsigned)gr->gr_gid);
		else
			printf("%s%u(%s)", (i == 0) ? "" : ",",
					(unsigned)gr->gr_gid, gr->gr_name);
	putchar('\n');
	free(groups);
	free(u);
	return 0;
}

/* _print_gid */
static struct group * _print_gid(gid_t gid)
{
	struct group * gr;

	if((gr = getgrgid(gid)) == NULL)
	{
		putchar('\n');
		_id_error("getgrgid", 0);
	}
	else
		printf("gid=%u(%s)", gr->gr_gid, gr->gr_name);
	return gr;
}

static gid_t * _id_getgroups(int * n)
{
	gid_t * groups;

	if((*n = getgroups(0, NULL)) < 0)
	{
		_id_error("getgroups", 1);
		return NULL;
	}
	if(*n == 0)
		groups = NULL;
	else if((groups = malloc(sizeof(*groups) * (*n))) == NULL)
	{
		_id_error("malloc", 1);
		return NULL;
	}
	if((*n = getgroups(*n, groups)) < 0)
	{
		free(groups);
		_id_error("getgroups", 1);
		return NULL;
	}
	return groups;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-Ggu][-nr] [user]\n\
  -G	Output all different group IDs\n\
  -g	Output only the effective group ID\n\
  -u	Output only the effective user ID\n\
  -n	Output the name as a string\n\
  -r	Output the real ID instead of the effective ID\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int o;
	int flag = 0;
	int flagn = 0;
	int flagr = 0;

	while((o = getopt(argc, argv, "Ggunr")) != -1)
		switch(o)
		{
			case 'G':
			case 'g':
			case 'u':
				flag = o;
				break;
			case 'n':
				flagn = 1;
				break;
			case 'r':
				flagr = 1;
				break;
			default:
				return _usage();
		}
	if(optind == argc)
		return _id(NULL, flag, flagn, flagr) == 0 ? 0 : 2;
	if(optind + 1 == argc)
		return _id(argv[optind], flag, flagn, flagr) == 0 ? 0 : 2;
	return _usage();
}
