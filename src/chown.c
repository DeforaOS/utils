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
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"chown"
#endif


/* chown */
/* types */
typedef unsigned int Prefs;
#define CHOWN_PREFS_h 0x1
#define CHOWN_PREFS_R 0x2
#define CHOWN_PREFS_H 0x4
#define CHOWN_PREFS_L 0x8
#define CHOWN_PREFS_P 0xc


/* functions */
/* chown */
static int _chown_error(char * message, int ret);
static int _chown_owner(char * owner, uid_t * uid, gid_t * gid);
static int _chown_do_recursive(Prefs * prefs, uid_t uid, gid_t gid,
		char * file);
static int _chown_do(Prefs * prefs, uid_t uid, gid_t gid, char * file);
static int _chown(Prefs * prefs, char * owner, int argc, char * argv[])
{
	int ret = 0;
	uid_t uid = 0;
	gid_t gid = 0;
	int i;

	if(_chown_owner(owner, &uid, &gid) != 0)
		return 2;
	if(*prefs & CHOWN_PREFS_R)
	{
		for(i = 0; i < argc; i++)
			ret |= _chown_do_recursive(prefs, uid, gid, argv[i]);
		return ret;
	}
	for(i = 0; i < argc; i++)
		ret |= _chown_do(prefs, uid, gid, argv[i]);
	return ret;
}

static int _chown_error(char * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}

/* PRE
 * POST
 * 		0	success
 * 		else	failure */
static uid_t _chown_uid(char * owner);
static gid_t _chown_gid(char * group);
static int _chown_owner(char * owner, uid_t * uid, gid_t * gid)
{
	int i;

	for(i = 0; owner[i] != 0; i++)
		if(owner[i] == ':')
		{
			owner[i++] = '\0';
			break;
		}
	if((*uid = _chown_uid(owner)) == (uid_t)-1)
		return 1;
	if(owner[i] != '\0' && (*gid = _chown_gid(&owner[i])) == (gid_t)-1)
		return 1;
	return 0;
}

static int _chown_id_error(char * message, char * unknown, int ret);
static uid_t _chown_uid(char * owner)
{
	struct passwd * pwd;
	char * p;
	int c;

	if((pwd = getpwnam(owner)) != NULL)
		return pwd->pw_uid;
	for(p = owner; (c = *p) != '\0' && isdigit(c); p++);
	if(*p != '\0' || *owner == '\0')
		return _chown_id_error(owner, "user", -1);
	return strtol(owner, NULL, 10);
}

static int _chown_id_error(char * message, char * unknown, int ret)
{
	if(errno != 0)
		return _chown_error(message, ret);
	fprintf(stderr, "%s%s%s%s%s", PROGNAME ": ", message, ": Unknown ",
			unknown, "\n");
	return ret;
}

static gid_t _chown_gid(char * group)
{
	struct group * grp;
	char * p;
	int c;

	if((grp = getgrnam(group)) != NULL)
		return grp->gr_gid;
	for(p = group; (c = *p) != '\0' && isdigit(c); p++);
	if(*p != '\0' || *group == '\0')
		return _chown_id_error(group, "group", -1);
	return strtol(group, NULL, 10);
}

static int _chown_do_recursive_do(Prefs * p, uid_t uid, gid_t gid, char * file);
static int _chown_do_recursive(Prefs * p, uid_t uid, gid_t gid, char * file)
{
	struct stat st;

	if(lstat(file, &st) != 0)
		return _chown_error(file, 1);
	if(!S_ISDIR(st.st_mode))
		return _chown_do(p, uid, gid, file);
	if(!S_ISLNK(st.st_mode))
		return _chown_do_recursive_do(p, uid, gid, file);
	return 0;
}

static int _chown_do_recursive_do(Prefs * prefs, uid_t uid, gid_t gid,
		char * file)
{
	DIR * dir;
	struct dirent * de;
	int len;
	char * s;
	char * p;

	if((dir = opendir(file)) == NULL)
		return _chown_error(file, 1);
	readdir(dir);
	readdir(dir);
	len = strlen(file);
	len += (len && file[len-1] == '/') ? 1 : 2;
	if((s = malloc(len)) == NULL)
	{
		closedir(dir);
		return _chown_error(file, 1);
	}
	strcpy(s, file);
	s[len-2] = '/';
	s[len-1] = '\0';
	while((de = readdir(dir)) != NULL)
	{
		if((p = realloc(s, len + strlen(de->d_name))) == NULL)
		{
			_chown_error("malloc", 0);
			continue;
		}
		s = p;
		strcat(s, de->d_name);
		_chown_do_recursive(prefs, uid, gid, s);
		s[len-1] = '\0';
	}
	free(s);
	closedir(dir);
	return 0;
}

static int _chown_do(Prefs * prefs, uid_t uid, gid_t gid, char * file)
{
	int res;

	if((*prefs & CHOWN_PREFS_h) == CHOWN_PREFS_h)
		res = lchown(file, uid, gid);
	else
		res = chown(file, uid, gid);
	if(res != 0)
		return _chown_error(file, 1);
	return 2;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-hR] owner[:group] file ...\n\
       " PROGNAME " -R [-H | -L | -P] owner[:group] file ...\n\
  -h	Set the user and group IDs on symbolic links\n\
  -R	Recursively change file user and group IDs\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	Prefs prefs = 0;
	int o;

	while((o = getopt(argc, argv, "hRHLP")) != -1)
		switch(o)
		{
			case 'h':
				prefs |= CHOWN_PREFS_h;
				break;
			case 'R':
				prefs |= CHOWN_PREFS_R;
				break;
			case 'H':
			case 'L':
			case 'P':
				fprintf(stderr, "%s%c%s", PROGNAME ": -", o,
						": Not yet implemented\n");
				return 2;
			default:
				return _usage();
		}
	if(argc - optind < 2)
		return _usage();
	return (_chown(&prefs, argv[optind], argc - optind - 1,
			&argv[optind + 1]) == 0) ? 0 : 2;
}
