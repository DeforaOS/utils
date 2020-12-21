/* $Id$ */
/* Copyright (c) 2020 Pierre Pronchery <khorben@defora.org> */
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



#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"getconf"
#endif


/* getconf */
/* private */
/* types */
typedef struct _getconf_catalog
{
	long name;
	char const * string;
} getconf_catalog;


/* constants */
static const getconf_catalog _getconf_catalog_confstr[] =
{
#ifdef _CS_PATH
	{ _CS_PATH,	"_CS_PATH"	},
#endif
};

static const getconf_catalog _getconf_catalog_limits[] =
{
#ifdef _SC_AIO_LISTIO_MAX
	{ _SC_AIO_LISTIO_MAX,	"AIO_LISTIO_MAX"},
#endif
#ifdef _SC_AIO_MAX
	{ _SC_AIO_MAX,		"AIO_MAX"	},
#endif
#ifdef _SC_ARG_MAX
	{ _SC_ARG_MAX,		"ARG_MAX"	},
#endif
#ifdef _SC_ATEXIT_MAX
	{ _SC_ATEXIT_MAX,	"ATEXIT_MAX"	},
#endif
#ifdef _SC_CHILD_MAX
	{ _SC_CHILD_MAX,	"CHILD_MAX"	},
#endif
#ifdef _SC_DELAYTIMER_MAX
	{ _SC_DELAYTIMER_MAX,	"DELAYTIMER_MAX"},
#endif
#ifdef _SC_EXPR_NEST_MAX
	{ _SC_EXPR_NEST_MAX,	"EXPR_NEST_MAX"	},
#endif
#ifdef _SC_HOST_NAME_MAX
	{ _SC_HOST_NAME_MAX,	"HOST_NAME_MAX"	},
#endif
#ifdef _SC_IOV_MAX
	{ _SC_IOV_MAX,		"IOV_MAX"	},
#endif
#ifdef _SC_LINE_MAX
	{ _SC_LINE_MAX,		"LINE_MAX"	},
#endif
#ifdef _SC_LOGIN_NAME_MAX
	{ _SC_LOGIN_NAME_MAX,	"LOGIN_NAME_MAX"},
#endif
#ifdef _SC_NGROUPS_MAX
	{ _SC_NGROUPS_MAX,	"NGROUPS_MAX"	},
#endif
#ifdef _SC_OPEN_MAX
	{ _SC_OPEN_MAX,		"OPEN_MAX"	},
#endif
#ifdef _SC_PAGE_SIZE
	{ _SC_PAGE_SIZE,	"PAGE_SIZE"	},
#endif
#ifdef _SC_PAGESIZE
	{ _SC_PAGESIZE,		"PAGESIZE"	},
#endif
#ifdef _SC_STREAM_MAX
	{ _SC_STREAM_MAX,	"STREAM_MAX"	},
#endif
#ifdef _SC_SYMLOOP_MAX
	{ _SC_SYMLOOP_MAX,	"SYMLOOP_MAX"	},
#endif
#ifdef _SC_TIMER_MAX
	{ _SC_TIMER_MAX,	"TIMER_MAX"	},
#endif
#ifdef _SC_TTYNAME_MAX
	{ _SC_TTYNAME_MAX,	"TTYNAME_MAX"	},
#endif
#ifdef _SC_TZNAME_MAX
	{ _SC_TZNAME_MAX,	"TZNAME_MAX"	},
#endif
};

static const getconf_catalog _getconf_catalog_pathconf[] =
{
#ifdef _PC_2_SYMLINKS
	{ _PC_2_SYMLINKS,	"POSIX2_SYMLINKS"			},
#endif
#ifdef _PC_ALLOC_SIZE_MIN
	{ _PC_ALLOC_SIZE_MIN,	"POSIX_ALLOC_SIZE_MIN"			},
#endif
#ifdef _PC_ASYNC_IO
	{ _PC_ASYNC_IO,		"_POSIX_ASYNC_IO"			},
#endif
#ifdef _PC_CHOWN_RESTRICTED
	{ _PC_CHOWN_RESTRICTED,	"POSIX_CHOWN_RESTRICTED"		},
#endif
#ifdef _PC_FILESIZEBITS
	{ _PC_FILESIZEBITS,	"FILESIZEBITS"				},
#endif
#ifdef _PC_LINK_MAX
	{ _PC_LINK_MAX,		"LINK_MAX"				},
#endif
#ifdef _PC_MAX_CANON
	{ _PC_MAX_CANON,	"MAX_CANON"				},
#endif
#ifdef _PC_MAX_INPUT
	{ _PC_MAX_INPUT,	"MAX_INPUT"				},
#endif
#ifdef _PC_NAME_MAX
	{ _PC_NAME_MAX,		"NAME_MAX"				},
#endif
#ifdef _PC_NO_TRUNC
	{ _PC_NO_TRUNC,		"POSIX_NO_TRUNC"			},
#endif
#ifdef _PC_PATH_MAX
	{ _PC_PATH_MAX,		"PATH_MAX"				},
#endif
#ifdef _PC_PIPE_BUF
	{ _PC_PIPE_BUF,		"PIPE_BUF"				},
#endif
#ifdef _PC_PRIO_IO
	{ _PC_PRIO_IO,		"_POSIX_PRIO_IO"			},
#endif
#ifdef _PC_REC_INCR_XFER_SIZE
	{ _PC_REC_INCR_XFER_SIZE,"POSIX_REC_INCR_XFER_SIZE"		},
#endif
#ifdef _PC_REC_MAX_XFER_SIZE
	{ _PC_REC_MAX_XFER_SIZE,"POSIX_REC_MAX_XFER_SIZE"		},
#endif
#ifdef _PC_REC_MIN_XFER_SIZE
	{ _PC_REC_MIN_XFER_SIZE,"POSIX_REC_MIN_XFER_SIZE"		},
#endif
#ifdef _PC_REC_XFER_ALIGN
	{ _PC_REC_XFER_ALIGN,	"POSIX_REC_XFER_ALIGN"			},
#endif
#ifdef _PC_SYMLINK_MAX
	{ _PC_SYMLINK_MAX,	"SYMLINK_MAX"				},
#endif
#ifdef _PC_SYNC_IO
	{ _PC_SYNC_IO,		"_POSIX_SYNC_IO"			},
#endif
#ifdef _PC_TIMESTAMP_RESOLUTION
	{ _PC_TIMESTAMP_RESOLUTION,"_POSIX_TIMESTAMP_RESOLUTION"	},
#endif
#ifdef _PC_VDISABLE
	{ _PC_VDISABLE,		"_POSIX_VDISABLE"			},
#endif
};

static const getconf_catalog _getconf_catalog_values[] =
{
#ifdef _POSIX2_BC_BASE_MAX
	{ _POSIX2_BC_BASE_MAX,		"POSIX2_BC_BASE_MAX"		},
#endif
#ifdef _POSIX2_BC_DIM_MAX
	{ _POSIX2_BC_DIM_MAX,		"POSIX2_BC_DIM_MAX"		},
#endif
#ifdef _POSIX2_BC_SCALE_MAX
	{ _POSIX2_BC_SCALE_MAX,		"POSIX2_BC_SCALE_MAX"		},
#endif
#ifdef _POSIX2_BC_STRING_MAX
	{ _POSIX2_BC_STRING_MAX,	"POSIX2_BC_STRING_MAX"		},
#endif
#ifdef _POSIX2_C_BIND
	{ _POSIX2_C_BIND,		"POSIX2_C_BIND"			},
#endif
#ifdef _POSIX2_C_DEV
	{ _POSIX2_C_DEV,		"POSIX2_C_DEV"			},
#endif
#ifdef _POSIX2_CHAR_TERM
	{ _POSIX2_CHAR_TERM,		"POSIX2_CHAR_TERM"		},
#endif
#ifdef _POSIX2_COLL_WEIGHTS_MAX
	{ _POSIX2_COLL_WEIGHTS_MAX,	"POSIX2_COLL_WEIGHTS_MAX"	},
#endif
#ifdef _POSIX2_EXPR_NEST_MAX
	{ _POSIX2_EXPR_NEST_MAX,	"POSIX2_EXPR_NEST_MAX"		},
#endif
#ifdef _POSIX2_FORT_DEV
	{ _POSIX2_FORT_DEV,		"POSIX2_FORT_DEV"		},
#endif
#ifdef _POSIX2_FORT_RUN
	{ _POSIX2_FORT_RUN,		"POSIX2_FORT_RUN"		},
#endif
#ifdef _POSIX2_LINE_MAX
	{ _POSIX2_LINE_MAX,		"POSIX2_LINE_MAX"		},
#endif
#ifdef _POSIX2_LOCALEDEF
	{ _POSIX2_LOCALEDEF,		"POSIX2_LOCALEDEF"		},
#endif
#ifdef _POSIX2_RE_DUP_MAX
	{ _POSIX2_RE_DUP_MAX,		"POSIX2_RE_DUP_MAX"		},
#endif
#ifdef _POSIX2_SW_DEV
	{ _POSIX2_SW_DEV,		"POSIX2_SW_DEV"			},
#endif
#ifdef _POSIX2_UPE
	{ _POSIX2_UPE,			"POSIX2_UPE"			},
#endif
#ifdef _POSIX2_VERSION
	{ _POSIX2_VERSION,		"POSIX2_VERSION"		},
#endif
};


/* prototypes */
static int _getconf(char const * specification, char const * var,
		char const * path);
static int _getconf_error(char const * message, int ret);
static int _usage(void);


/* functions */
/* getconf */
static int _getconf_confstr(char const * var);
static int _getconf_limits(char const * var);
static int _getconf_pathconf(char const * var, char const * path);
static int _getconf_values(char const * var);

static int _getconf(char const * specification, char const * var,
		char const * path)
{
	if(path != NULL)
		return _getconf_pathconf(var, path);
	if(strncmp(var, "_SC_", 4) == 0)
		return _getconf_confstr(var);
	return _getconf_limits(var);
}

static int _getconf_confstr(char const * var)
{
	size_t i;
	size_t cnt = sizeof(_getconf_catalog_confstr)
		/ sizeof(*_getconf_catalog_confstr);
	char * buf;

	for(i = 0; i < cnt; i++)
		if(strcmp(_getconf_catalog_confstr[i].string, var) == 0)
			break;
	if(i == cnt)
		return _getconf_error(var, -ENOENT);
	/* obtain the required size */
	if((cnt = confstr(_getconf_catalog_confstr[i].name, NULL, 0)) == 0)
		return _getconf_error(var, 2);
	if((buf = malloc(cnt)) == NULL)
		return _getconf_error(var, 2);
	if((cnt = confstr(_getconf_catalog_confstr[i].name, buf, cnt)) == 0)
	{
		free(buf);
		return _getconf_error(var, 2);
	}
	printf("%s\n", buf);
	free(buf);
	return 0;
}

static int _getconf_limits(char const * var)
{
	size_t i;
	size_t cnt = sizeof(_getconf_catalog_limits)
		/ sizeof(*_getconf_catalog_limits);
	long value;

	for(i = 0; i < cnt; i++)
		if(strcmp(_getconf_catalog_limits[i].string, var) == 0)
			break;
	if(i == cnt)
		return _getconf_values(var);
	if((value = sysconf(_getconf_catalog_limits[i].name)) < 0)
		return _getconf_error(var, 2);
	printf("%ld\n", value);
	return 0;
}

static int _getconf_pathconf(char const * var, char const * path)
{
	size_t i;
	size_t cnt = sizeof(_getconf_catalog_pathconf)
		/ sizeof(*_getconf_catalog_pathconf);
	long value;

	for(i = 0; i < cnt; i++)
		if(strcmp(_getconf_catalog_pathconf[i].string, var) == 0)
			break;
	if(i == cnt)
		return _getconf_error(var, -ENOENT);
	if((value = pathconf(path, _getconf_catalog_pathconf[i].name)) < 0)
		return _getconf_error(var, 2);
	printf("%ld\n", value);
	return 0;
}

static int _getconf_values(char const * var)
{
	size_t i;
	size_t cnt = sizeof(_getconf_catalog_values)
		/ sizeof(*_getconf_catalog_values);

	for(i = 0; i < cnt; i++)
		if(strcmp(_getconf_catalog_values[i].string, var) == 0)
			break;
	if(i == cnt)
		return _getconf_error(var, -ENOENT);
	printf("%ld\n", _getconf_catalog_values[i].name);
	return 0;
}


/* error */
static int _getconf_error(char const * message, int ret)
{
	fputs(PROGNAME ": ", stderr);
	if(ret < 0)
	{
		fprintf(stderr, "%s%s%s\n", (message != NULL) ? message : "",
				(message != NULL) ? ": " : "", strerror(-ret));
		return -ret;
	}
	perror(message);
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-v specification] system_var\n"
"       " PROGNAME " [-v specification] path_var pathname\n", stderr);
	return 1;
}


/* main */
int main(int argc, char * argv[])
{
	int o;
	char const * specification = NULL;

	while((o = getopt(argc, argv, "v:")) != -1)
		switch(o)
		{
			case 'v':
				specification = optarg;
				break;
			default:
				return _usage();
		}
	if(optind + 1 != argc && optind + 2 != argc)
		return _usage();
	return (_getconf(specification, argv[optind], argv[optind + 1]) == 0)
		? 0 : 2;
}
