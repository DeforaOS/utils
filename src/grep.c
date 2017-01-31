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


/* prototypes */
static int _grep(Prefs * prefs, int flags, char const * pattern,
		int filec, char * filev[]);

static int _usage(void);


/* functions */
/* grep */
static int _grep_error(char const * message, int ret);
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

static int _grep_files(Prefs * prefs, regex_t * reg, int filec, char * filev[])
{
	int ret = 1;
	int i;
	char const * filename;
	FILE * fp;
	char buf[128];

	for(i = 0; i < filec; i++)
	{
		if(strcmp(filev[i], "-") == 0)
		{
			filename = NULL;
			fp = stdin;
		}
		else if((fp = fopen(filev[i], "r")) == NULL)
		{
			if(prefs != NULL && (*prefs & GREP_PREFS_s)
					&& (errno == ENOENT || errno == EACCES))
				ret = 2;
			else
			{
				snprintf(buf, sizeof(buf), "%s: %s", filev[i],
						strerror(errno));
				ret = _grep_error(buf, 2);
			}
			continue;
		}
		else
			filename = (filec == 1) ? "" : filev[i];
		if(_grep_stream(prefs, reg, fp, filename) == 0 && ret == 1)
			ret = 0;
		if(filename != NULL && fclose(fp) != 0)
		{
			snprintf(buf, sizeof(buf), "%s: %s", filename,
					strerror(errno));
			ret = _grep_error(buf, 2);
		}
	}
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
		if((e = regexec(reg, buf, 1, &match, 0)) == 0)
		{
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
		else if(e != REG_NOMATCH)
		{
			regerror(e, reg, buf, sizeof(buf));
			ret = -_grep_error(buf, 1);
		}
	return ret;
}


/* usage */
static int _usage(void)
{
	fputs("Usage: " PROGNAME " [-Einqs][file...]\n", stderr);
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

	while((o = getopt(argc, argv, "Einqs")) != -1)
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
			default:
				return _usage();
		}
	if(optind == argc)
		return _usage();
	return _grep(&prefs, flags, argv[optind], argc - optind - 1,
			&argv[optind + 1]);
}
