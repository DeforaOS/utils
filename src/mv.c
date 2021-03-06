/* $Id$ */
/* Copyright (c) 2007-2020 Pierre Pronchery <khorben@defora.org> */
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



#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <errno.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"mv"
#endif


/* mv */
/* types */
typedef unsigned int Prefs;
#define MV_PREFS_f 0x1
#define MV_PREFS_i 0x2


/* prototypes */
static int _mv_error(char const * message, int ret);

static int _mv_single(Prefs * prefs, char const * src, char const * dst);
static int _mv_multiple(Prefs * prefs, int filec, char * const filev[]);


/* functions */
/* mv */
static int _mv(Prefs * prefs, int filec, char * filev[])
{
	struct stat st;

	if(stat(filev[filec - 1], &st) != 0)
	{
		if(errno != ENOENT)
			return _mv_error(filev[filec - 1], 1);
		if(filec > 2)
		{
			errno = ENOTDIR;
			return _mv_error(filev[filec - 1], 1);
		}
	}
	else if(S_ISDIR(st.st_mode))
		return _mv_multiple(prefs, filec, filev);
	else if(filec > 2)
	{
		errno = ENOTDIR;
		return _mv_error(filev[filec - 1], 1);
	}
	return _mv_single(prefs, filev[0], filev[1]);
}

static int _mv_confirm(char const * message)
{
	int c;
	int tmp;

	fprintf(stderr, "%s%s%s", PROGNAME ": ", message, ": Overwrite? ");
	if((c = fgetc(stdin)) == EOF)
		return 0;
	while(c != '\n' && (tmp = fgetc(stdin)) != EOF && tmp != '\n');
	return c == 'y';
}


/* mv_error */
static int _mv_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	perror(message);
	return ret;
}


/* mv_single */
static int _mv_single_dir(Prefs * prefs, char const * src, char const * dst,
		mode_t mode);
static int _mv_single_recurse(Prefs * prefs, char const * src, char const * dst,
		mode_t mode);
static int _mv_single_fifo(char const * src, char const * dst, mode_t mode);
static int _mv_single_nod(char const * src, char const * dst, mode_t mode,
		dev_t rdev);
static int _mv_single_symlink(char const * src, char const * dst);
static int _mv_single_regular(char const * src, char const * dst, mode_t mode);
static int _mv_single_p(char const * dst, struct stat const * st);

static int _mv_single(Prefs * prefs, char const * src, char const * dst)
{
	int ret;
	struct stat st;

	if(lstat(src, &st) != 0 && errno == ENOENT) /* XXX TOCTOU */
		return _mv_error(src, 1);
	if(*prefs & MV_PREFS_i && (lstat(dst, &st) == 0 || errno != ENOENT)
			&& _mv_confirm(dst) != 1)
		return 0;
	if(rename(src, dst) == 0)
		return 0;
	if(errno != EXDEV)
		return _mv_error(src, 1);
	if(unlink(dst) != 0 && errno != ENOENT)
		return _mv_error(dst, 1);
	if(lstat(src, &st) != 0)
		return _mv_error(dst, 1);
	if(S_ISDIR(st.st_mode))
		ret = _mv_single_dir(prefs, src, dst, st.st_mode & 0777);
	else if(S_ISFIFO(st.st_mode))
		ret = _mv_single_fifo(src, dst, st.st_mode & 0666);
	else if(S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
		ret = _mv_single_nod(src, dst, st.st_mode, st.st_rdev);
	else if(S_ISLNK(st.st_mode))
		ret = _mv_single_symlink(src, dst);
	else if(S_ISREG(st.st_mode))
		ret = _mv_single_regular(src, dst, st.st_mode & 0777);
	else
	{
		errno = ENOSYS;
		return _mv_error(src, 1);
	}
	if(ret != 0)
		return ret;
	_mv_single_p(dst, &st);
	return 0;
}

static int _mv_single_dir(Prefs * prefs, char const * src, char const * dst,
		mode_t mode)
{
	if(_mv_single_recurse(prefs, src, dst, mode) != 0)
		return 1;
	if(rmdir(src) != 0) /* FIXME probably gonna fail, recurse before */
		_mv_error(src, 0);
	return 0;
}

static int _mv_single_recurse(Prefs * prefs, char const * src, char const * dst,
		mode_t mode)
{
	int ret = 0;
	size_t srclen;
	size_t dstlen;
	DIR * dir;
	struct dirent * de;
	char * ssrc = NULL;
	char * sdst = NULL;
	char * p;

	if(mkdir(dst, mode) != 0)
		return _mv_error(dst, 1);
	srclen = strlen(src);
	dstlen = strlen(dst);
	if((dir = opendir(src)) == NULL)
		return _mv_error(src, 1);
	while((de = readdir(dir)) != NULL)
	{
		if(de->d_name[0] == '.' && (de->d_name[1] == '\0'
					|| (de->d_name[1] == '.'
						&& de->d_name[2] == '\0')))
			continue;
		if((p = realloc(ssrc, srclen + strlen(de->d_name) + 2)) == NULL)
		{
			ret |= _mv_error(src, 1);
			continue;
		}
		ssrc = p;
		if((p = realloc(sdst, dstlen + strlen(de->d_name) + 2)) == NULL)
		{
			ret |= _mv_error(src, 1);
			continue;
		}
		sdst = p;
		sprintf(ssrc, "%s/%s", src, de->d_name);
		sprintf(sdst, "%s/%s", dst, de->d_name);
		ret |= _mv_single(prefs, ssrc, sdst);
	}
	closedir(dir);
	free(ssrc);
	free(sdst);
	return ret;
}

static int _mv_single_fifo(char const * src, char const * dst, mode_t mode)
{
	if(mkfifo(dst, mode) != 0)
		return _mv_error(dst, 1);
	if(unlink(src) != 0)
		_mv_error(src, 0);
	return 0;
}

static int _mv_single_nod(char const * src, char const * dst, mode_t mode,
		dev_t rdev)
{
	if(mknod(dst, mode, rdev) != 0)
		return _mv_error(dst, 1);
	if(unlink(src) != 0)
		_mv_error(src, 0);
	return 0;
}

static int _mv_single_symlink(char const * src, char const * dst)
{
	char buf[PATH_MAX];
	ssize_t len;

	if((len = readlink(src, buf, sizeof(buf) - 1)) == -1)
		return _mv_error(src, 1);
	buf[len] = '\0';
	if(symlink(buf, dst) != 0)
		return _mv_error(dst, 1);
	if(unlink(src) != 0)
		_mv_error(src, 0);
	return 0;
}

static int _mv_single_regular(char const * src, char const * dst, mode_t mode)
{
	int ret = 0;
	FILE * fsrc;
	int fd;
	FILE * fdst;
	char buf[BUFSIZ];
	size_t size;

	if((fsrc = fopen(src, "r")) == NULL)
		return _mv_error(dst, 1);
	if((fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, mode)) < 0
			|| (fdst = fdopen(fd, "w")) == NULL)
	{
		ret |= _mv_error(dst, 1);
		if(fd >= 0)
			close(fd);
		fclose(fsrc);
		return ret;
	}
	while((size = fread(buf, sizeof(char), sizeof(buf), fsrc)) > 0)
		if(fwrite(buf, sizeof(char), size, fdst) != size)
			break;
	if(!feof(fsrc))
		ret |= _mv_error(size == 0 ? src : dst, 1);
	if(fclose(fsrc) != 0)
		ret |= _mv_error(src, 1);
	if(fclose(fdst) != 0)
		ret |= _mv_error(dst, 1);
	if(unlink(src) != 0)
		_mv_error(src, 0);
	return ret;
}

static int _mv_single_p(char const * dst, struct stat const * st)
{
	struct timeval tv[2];

	if(lchown(dst, st->st_uid, st->st_gid) != 0) /* XXX TOCTOU */
	{
		_mv_error(dst, 0);
		if(lchmod(dst, st->st_mode & ~(S_ISUID | S_ISGID)) != 0)
			_mv_error(dst, 0);
	}
	else if(lchmod(dst, st->st_mode) != 0)
		_mv_error(dst, 0);
	tv[0].tv_sec = st->st_atime;
	tv[0].tv_usec = 0;
	tv[1].tv_sec = st->st_mtime;
	tv[1].tv_usec = 0;
	if(lutimes(dst, tv) != 0)
		_mv_error(dst, 0);
	return 0;
}


/* mv_multiple */
static int _mv_multiple(Prefs * prefs, int filec, char * const filev[])
{
	int ret = 0;
	int i;
	char * dst;
	size_t len;
	char * sdst = NULL;
	char * p;

	for(i = 0; i < filec - 1; i++)
	{
		dst = basename(filev[i]);
		len = strlen(filev[i]) + strlen(dst) + 2;
		if((p = realloc(sdst, len * sizeof(char))) == NULL)
		{
			ret |= _mv_error(filev[filec - 1], 1);
			continue;
		}
		sdst = p;
		sprintf(sdst, "%s/%s", filev[filec - 1], dst);
		ret |= _mv_single(prefs, filev[i], sdst);
	}
	free(sdst);
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-fi] source_file target_file\n\
       " PROGNAME " [-fi] source_file... target_file\n\
  -f	Do not prompt for confirmation if the destination path exists\n\
  -i	Prompt for confirmation if the destination path exists\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int o;
	Prefs prefs = MV_PREFS_f;

	while((o = getopt(argc, argv, "fi")) != -1)
		switch(o)
		{
			case 'f':
				prefs -= prefs & MV_PREFS_i;
				prefs |= MV_PREFS_f;
				break;
			case 'i':
				prefs -= prefs & MV_PREFS_f;
				prefs |= MV_PREFS_i;
				break;
			default:
				return _usage();
		}
	if(argc - optind < 2)
		return _usage();
	return (_mv(&prefs, argc - optind, &argv[optind]) == 0) ? 0 : 2;
}
