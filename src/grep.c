/* $Id$ */
/* Copyright (c) 2017 Pierre Pronchery <khorben@defora.org> */
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <errno.h>

/* constants */
#ifndef PROGNAME
# define PROGNAME	"grep"
#endif


/* grep */
/* private */
/* types */
/* Prefs */
typedef int Prefs;
#define GREP_PREFS_n 0x1
#define GREP_PREFS_q 0x2
#define GREP_PREFS_s 0x4
#define GREP_PREFS_v 0x8


/* prototypes */
static int _grep(Prefs * prefs, int flags, char const * pattern,
		int filec, char * filev[]);

static int _usage(void);


/* functions */
/* grep */
static int _grep_error(char const * message, int ret);
static int _grep_file(Prefs * prefs, regex_t * reg, char const * filename);
static int _grep_files(Prefs * prefs, regex_t * reg, int filec, char * filev[]);
static int _grep_stream(Prefs * prefs, regex_t * reg, FILE * fp,
		char const * filename);

static int _grep(Prefs * prefs, int flags, char const * pattern,
		int filec, char * filev[])
{
	int ret;
	regex_t reg;
	int e;
	char buf[128];
	int n;

	if((e = regcomp(&reg, pattern, flags)) != 0)
	{
		n = snprintf(buf, sizeof(buf), "%s: ", pattern);
		if(n >= 0 && (unsigned)n < sizeof(buf))
			regerror(e, &reg, &buf[n], sizeof(buf) - n);
		else
			regerror(e, &reg, buf, sizeof(buf));
		return _grep_error(buf, 2);
	}
	if(filec == 0)
		ret = _grep_stream(prefs, &reg, stdin, NULL);
	else
		ret = _grep_files(prefs, &reg, filec, filev);
	regfree(&reg);
	return ret;
}

static int _grep_error(char const * message, int ret)
{
	fprintf(stderr, "%s: %s\n", PROGNAME, message);
	return ret;
}

static int _grep_file(Prefs * prefs, regex_t * reg, char const * filename)
{
	int ret;
	FILE * fp;
	char buf[128];

	if(strcmp(filename, "-") == 0)
	{
		filename = NULL;
		fp = stdin;
	}
	else if((fp = fopen(filename, "r")) == NULL)
	{
		if(prefs != NULL && (*prefs & GREP_PREFS_s)
				&& (errno == ENOENT || errno == EACCES))
			return 2;
		snprintf(buf, sizeof(buf), "%s: %s", filename, strerror(errno));
		return _grep_error(buf, 2);
	}
	ret = _grep_stream(prefs, reg, fp, filename);
	if(filename != NULL && fclose(fp) != 0)
	{
		snprintf(buf, sizeof(buf), "%s: %s", filename,
				strerror(errno));
		return _grep_error(buf, 2);
	}
	return ret;
}

static int _grep_files(Prefs * prefs, regex_t * reg, int filec, char * filev[])
{
	int ret = 1;
	int i;
	int r;

	if(filec == 1)
	{
		if(strcmp(filev[0], "-") == 0)
			return _grep_stream(prefs, reg, stdin, NULL);
		else
			return _grep_file(prefs, reg, filev[0]);
	}
	for(i = 0; i < filec; i++)
		if((r = _grep_file(prefs, reg, filev[i])) > 1 || r < 0)
			ret = 2;
		else if(r == 0)
			ret = (ret == 1) ? 0 : ret;
	return ret;
}

static int _grep_stream(Prefs * prefs, regex_t * reg, FILE * fp,
		char const * filename)
{
	int ret = 1;
	size_t line;
	char buf[BUFSIZ];
	regmatch_t match;
	int e;

	for(line = 1; fgets(buf, sizeof(buf), fp) != NULL; line++)
	{
		if((e = regexec(reg, buf, 1, &match, 0)) != 0
				&& e != REG_NOMATCH)
		{
			regerror(e, reg, buf, sizeof(buf));
			ret = -_grep_error(buf, 1);
			continue;
		}
		if(prefs != NULL && *prefs & GREP_PREFS_v)
			e = (e == 0) ? REG_NOMATCH : 0;
		if(e == REG_NOMATCH)
			continue;
		if(prefs != NULL && !(*prefs & GREP_PREFS_q))
		{
			if(filename != NULL && filename[0] != '\0')
				printf("%s:", filename);
			if(prefs != NULL && *prefs & GREP_PREFS_n)
				printf("%zd:", line);
			printf("%s", buf);
		}
		if(ret == 1)
			ret = 0;
	}
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-Einqsv][file...]\n", stderr);
	return 1;
}


/* public */
/* functions */
/* main */
int main(int argc, char * argv[])
{
	int o;
	Prefs prefs = 0;
	int flags = 0;

	while((o = getopt(argc, argv, "Einqsv")) != -1)
		switch(o)
		{
			case 'E':
				flags |= REG_EXTENDED;
				break;
			case 'i':
				flags |= REG_ICASE;
				break;
			case 'n':
				prefs |= GREP_PREFS_n;
				break;
			case 'q':
				prefs |= GREP_PREFS_q;
				break;
			case 's':
				prefs |= GREP_PREFS_s;
				break;
			case 'v':
				prefs |= GREP_PREFS_v;
				break;
			default:
				return _usage();
		}
	if(optind == argc)
		return _usage();
	return _grep(&prefs, flags, argv[optind], argc - optind - 1,
			&argv[optind + 1]);
}
