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



#include "utilbox.h"


/* basename.c */
#define PROGNAME "basename"
#define main _basename_main
#define _usage _basename_usage
#define _Prefs _basename_Prefs
#define Prefs basename_Prefs
#define _prefs_parse _basename_prefs_parse
#define _basename __basename
#include "../src/basename.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _basename
#undef PROGNAME

/* cat.c */
#define PROGNAME "cat"
#define main _cat_main
#define _usage _cat_usage
#define _Prefs _cat_Prefs
#define Prefs cat_Prefs
#define _prefs_parse _cat_prefs_parse
#define _cat __cat
#include "../src/cat.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _cat
#undef PROGNAME

/* chgrp.c */
#define PROGNAME "chgrp"
#define main _chgrp_main
#define _usage _chgrp_usage
#define _Prefs _chgrp_Prefs
#define Prefs chgrp_Prefs
#define _prefs_parse _chgrp_prefs_parse
#define _chgrp __chgrp
#include "../src/chgrp.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _chgrp
#undef PROGNAME

/* chmod.c */
#define PROGNAME "chmod"
#define main _chmod_main
#define _usage _chmod_usage
#define _Prefs _chmod_Prefs
#define Prefs chmod_Prefs
#define _prefs_parse _chmod_prefs_parse
#define _chmod __chmod
#include "../src/chmod.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _chmod
#undef PROGNAME

/* chown.c */
#define PROGNAME "chown"
#define main _chown_main
#define _usage _chown_usage
#define _Prefs _chown_Prefs
#define Prefs chown_Prefs
#define _prefs_parse _chown_prefs_parse
#define _chown __chown
#include "../src/chown.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _chown
#undef PROGNAME

/* cksum.c */
#define PROGNAME "cksum"
#define main _cksum_main
#define _usage _cksum_usage
#define _Prefs _cksum_Prefs
#define Prefs cksum_Prefs
#define _prefs_parse _cksum_prefs_parse
#define _cksum __cksum
#include "../src/cksum.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _cksum
#undef PROGNAME

/* cmp.c */
#define PROGNAME "cmp"
#define main _cmp_main
#define _usage _cmp_usage
#define _Prefs _cmp_Prefs
#define Prefs cmp_Prefs
#define _prefs_parse _cmp_prefs_parse
#define _cmp __cmp
#include "../src/cmp.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _cmp
#undef PROGNAME

/* cp.c */
#define PROGNAME "cp"
#define main _cp_main
#define _usage _cp_usage
#define _Prefs _cp_Prefs
#define Prefs cp_Prefs
#define _prefs_parse _cp_prefs_parse
#define _cp __cp
#include "../src/cp.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _cp
#undef PROGNAME

/* date.c */
#define PROGNAME "date"
#define main _date_main
#define _usage _date_usage
#define _Prefs _date_Prefs
#define Prefs date_Prefs
#define _prefs_parse _date_prefs_parse
#define _date __date
#include "../src/date.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _date
#undef PROGNAME

/* df.c */
#define PROGNAME "df"
#define main _df_main
#define _usage _df_usage
#define _Prefs _df_Prefs
#define Prefs df_Prefs
#define _prefs_parse _df_prefs_parse
#define _df __df
#include "../src/df.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _df
#undef PROGNAME

/* dirname.c */
#define PROGNAME "dirname"
#define main _dirname_main
#define _usage _dirname_usage
#define _Prefs _dirname_Prefs
#define Prefs dirname_Prefs
#define _prefs_parse _dirname_prefs_parse
#define _dirname __dirname
#include "../src/dirname.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _dirname
#undef PROGNAME

/* du.c */
#define PROGNAME "du"
#define main _du_main
#define _usage _du_usage
#define _Prefs _du_Prefs
#define Prefs du_Prefs
#define _prefs_parse _du_prefs_parse
#define _du __du
#include "../src/du.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _du
#undef PROGNAME

/* echo.c */
#define PROGNAME "echo"
#define main _echo_main
#define _usage _echo_usage
#define _Prefs _echo_Prefs
#define Prefs echo_Prefs
#define _prefs_parse _echo_prefs_parse
#define _echo __echo
#include "../src/echo.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _echo
#undef PROGNAME

/* false.c */
#define PROGNAME "false"
#define main _false_main
#define _usage _false_usage
#define _Prefs _false_Prefs
#define Prefs false_Prefs
#define _prefs_parse _false_prefs_parse
#define _false __false
#include "../src/false.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _false
#undef PROGNAME

/* file.c */
#define PROGNAME "file"
#define main _file_main
#define _usage _file_usage
#define _Prefs _file_Prefs
#define Prefs file_Prefs
#define _prefs_parse _file_prefs_parse
#define _file __file
#include "../src/file.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _file
#undef PROGNAME

/* find.c */
#define PROGNAME "find"
#define main _find_main
#define _usage _find_usage
#define _Prefs _find_Prefs
#define Prefs find_Prefs
#define _prefs_parse _find_prefs_parse
#define _find __find
#include "../src/find.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _find
#undef PROGNAME

/* grep.c */
#define PROGNAME "grep"
#define main _grep_main
#define _usage _grep_usage
#define _Prefs _grep_Prefs
#define Prefs grep_Prefs
#define _prefs_parse _grep_prefs_parse
#define _grep __grep
#include "../src/grep.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _grep
#undef PROGNAME

/* head.c */
#define PROGNAME "head"
#define main _head_main
#define _usage _head_usage
#define _Prefs _head_Prefs
#define Prefs head_Prefs
#define _prefs_parse _head_prefs_parse
#define _head __head
#include "../src/head.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _head
#undef PROGNAME

/* id.c */
#define PROGNAME "id"
#define main _id_main
#define _usage _id_usage
#define _Prefs _id_Prefs
#define Prefs id_Prefs
#define _prefs_parse _id_prefs_parse
#define _id __id
#include "../src/id.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _id
#undef PROGNAME

/* kill.c */
#define PROGNAME "kill"
#define main _kill_main
#define _usage _kill_usage
#define _Prefs _kill_Prefs
#define Prefs kill_Prefs
#define _prefs_parse _kill_prefs_parse
#define _kill __kill
#include "../src/kill.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _kill
#undef PROGNAME

/* link.c */
#define PROGNAME "link"
#define main _link_main
#define _usage _link_usage
#define _Prefs _link_Prefs
#define Prefs link_Prefs
#define _prefs_parse _link_prefs_parse
#define _link __link
#include "../src/link.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _link
#undef PROGNAME

/* ln.c */
#define PROGNAME "ln"
#define main _ln_main
#define _usage _ln_usage
#define _Prefs _ln_Prefs
#define Prefs ln_Prefs
#define _prefs_parse _ln_prefs_parse
#define _ln __ln
#include "../src/ln.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _ln
#undef PROGNAME

/* locale.c */
#define PROGNAME "locale"
#define main _locale_main
#define _usage _locale_usage
#define _Prefs _locale_Prefs
#define Prefs locale_Prefs
#define _prefs_parse _locale_prefs_parse
#define _locale __locale
#include "../src/locale.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _locale
#undef PROGNAME

/* logname.c */
#define PROGNAME "logname"
#define main _logname_main
#define _usage _logname_usage
#define _Prefs _logname_Prefs
#define Prefs logname_Prefs
#define _prefs_parse _logname_prefs_parse
#define _logname __logname
#include "../src/logname.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _logname
#undef PROGNAME

/* ls.c */
#define PROGNAME "ls"
#define main _ls_main
#define _usage _ls_usage
#define _Prefs _ls_Prefs
#define Prefs ls_Prefs
#define _prefs_parse _ls_prefs_parse
#define _ls __ls
#include "../src/ls.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _ls
#undef PROGNAME

/* mkdir.c */
#define PROGNAME "mkdir"
#define main _mkdir_main
#define _usage _mkdir_usage
#define _Prefs _mkdir_Prefs
#define Prefs mkdir_Prefs
#define _prefs_parse _mkdir_prefs_parse
#define _mkdir __mkdir
#include "../src/mkdir.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _mkdir
#undef PROGNAME

/* mkfifo.c */
#define PROGNAME "mkfifo"
#define main _mkfifo_main
#define _usage _mkfifo_usage
#define _Prefs _mkfifo_Prefs
#define Prefs mkfifo_Prefs
#define _prefs_parse _mkfifo_prefs_parse
#define _mkfifo __mkfifo
#include "../src/mkfifo.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _mkfifo
#undef PROGNAME

/* more.c */
#define PROGNAME "more"
#define main _more_main
#define _usage _more_usage
#define _Prefs _more_Prefs
#define Prefs more_Prefs
#define _prefs_parse _more_prefs_parse
#define _more __more
#include "../src/more.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _more
#undef PROGNAME

/* mv.c */
#define PROGNAME "mv"
#define main _mv_main
#define _usage _mv_usage
#define _Prefs _mv_Prefs
#define Prefs mv_Prefs
#define _prefs_parse _mv_prefs_parse
#define _mv __mv
#include "../src/mv.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _mv
#undef PROGNAME

/* nice.c */
#define PROGNAME "nice"
#define main _nice_main
#define _usage _nice_usage
#define _Prefs _nice_Prefs
#define Prefs nice_Prefs
#define _prefs_parse _nice_prefs_parse
#define _nice __nice
#include "../src/nice.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _nice
#undef PROGNAME

/* pr.c */
#define PROGNAME "pr"
#define main _pr_main
#define _usage _pr_usage
#define _Prefs _pr_Prefs
#define Prefs pr_Prefs
#define _prefs_parse _pr_prefs_parse
#define _pr __pr
#include "../src/pr.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _pr
#undef PROGNAME

/* printf.c */
#define PROGNAME "printf"
#define main _printf_main
#define _usage _printf_usage
#define _Prefs _printf_Prefs
#define Prefs printf_Prefs
#define _prefs_parse _printf_prefs_parse
#define _printf __printf
#include "../src/printf.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _printf
#undef PROGNAME

/* ps.c */
#define PROGNAME "ps"
#define main _ps_main
#define _usage _ps_usage
#define _Prefs _ps_Prefs
#define Prefs ps_Prefs
#define _prefs_parse _ps_prefs_parse
#define _ps __ps
#include "../src/ps.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _ps
#undef PROGNAME

/* pwd.c */
#define PROGNAME "pwd"
#define main _pwd_main
#define _usage _pwd_usage
#define _Prefs _pwd_Prefs
#define Prefs pwd_Prefs
#define _prefs_parse _pwd_prefs_parse
#define _pwd __pwd
#include "../src/pwd.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _pwd
#undef PROGNAME

/* renice.c */
#define PROGNAME "renice"
#define main _renice_main
#define _usage _renice_usage
#define _Prefs _renice_Prefs
#define Prefs renice_Prefs
#define _prefs_parse _renice_prefs_parse
#define _renice __renice
#include "../src/renice.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _renice
#undef PROGNAME

/* rm.c */
#define PROGNAME "rm"
#define main _rm_main
#define _usage _rm_usage
#define _Prefs _rm_Prefs
#define Prefs rm_Prefs
#define _prefs_parse _rm_prefs_parse
#define _rm __rm
#include "../src/rm.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _rm
#undef PROGNAME

/* rmdir.c */
#define PROGNAME "rmdir"
#define main _rmdir_main
#define _usage _rmdir_usage
#define _Prefs _rmdir_Prefs
#define Prefs rmdir_Prefs
#define _prefs_parse _rmdir_prefs_parse
#define _rmdir __rmdir
#include "../src/rmdir.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _rmdir
#undef PROGNAME

/* sleep.c */
#define PROGNAME "sleep"
#define main _sleep_main
#define _usage _sleep_usage
#define _Prefs _sleep_Prefs
#define Prefs sleep_Prefs
#define _prefs_parse _sleep_prefs_parse
#define _sleep __sleep
#include "../src/sleep.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _sleep
#undef PROGNAME

/* strings.c */
#define PROGNAME "strings"
#define main _strings_main
#define _usage _strings_usage
#define _Prefs _strings_Prefs
#define Prefs strings_Prefs
#define _prefs_parse _strings_prefs_parse
#define _strings __strings
#include "../src/strings.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _strings
#undef PROGNAME

/* tail.c */
#define PROGNAME "tail"
#define main _tail_main
#define _usage _tail_usage
#define _Prefs _tail_Prefs
#define Prefs tail_Prefs
#define _prefs_parse _tail_prefs_parse
#define _tail __tail
#include "../src/tail.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _tail
#undef PROGNAME

/* test.c */
#define PROGNAME "test"
#define main _test_main
#define _usage _test_usage
#define _Prefs _test_Prefs
#define Prefs test_Prefs
#define _prefs_parse _test_prefs_parse
#define _test __test
#include "../src/test.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _test
#undef PROGNAME

/* time.c */
#define PROGNAME "time"
#define main _time_main
#define _usage _time_usage
#define _Prefs _time_Prefs
#define Prefs time_Prefs
#define _prefs_parse _time_prefs_parse
#define _time __time
#include "../src/time.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _time
#undef PROGNAME

/* touch.c */
#define PROGNAME "touch"
#define main _touch_main
#define _usage _touch_usage
#define _Prefs _touch_Prefs
#define Prefs touch_Prefs
#define _prefs_parse _touch_prefs_parse
#define _touch __touch
#include "../src/touch.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _touch
#undef PROGNAME

/* true.c */
#define PROGNAME "true"
#define main _true_main
#define _usage _true_usage
#define _Prefs _true_Prefs
#define Prefs true_Prefs
#define _prefs_parse _true_prefs_parse
#define _true __true
#include "../src/true.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _true
#undef PROGNAME

/* tty.c */
#define PROGNAME "tty"
#define main _tty_main
#define _usage _tty_usage
#define _Prefs _tty_Prefs
#define Prefs tty_Prefs
#define _prefs_parse _tty_prefs_parse
#define _tty __tty
#include "../src/tty.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _tty
#undef PROGNAME

/* uname.c */
#define PROGNAME "uname"
#define main _uname_main
#define _usage _uname_usage
#define _Prefs _uname_Prefs
#define Prefs uname_Prefs
#define _prefs_parse _uname_prefs_parse
#define _uname __uname
#include "../src/uname.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _uname
#undef PROGNAME

/* uniq.c */
#define PROGNAME "uniq"
#define main _uniq_main
#define _usage _uniq_usage
#define _Prefs _uniq_Prefs
#define Prefs uniq_Prefs
#define _prefs_parse _uniq_prefs_parse
#define _uniq __uniq
#include "../src/uniq.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _uniq
#undef PROGNAME

/* unlink.c */
#define PROGNAME "unlink"
#define main _unlink_main
#define _usage _unlink_usage
#define _Prefs _unlink_Prefs
#define Prefs unlink_Prefs
#define _prefs_parse _unlink_prefs_parse
#define _unlink __unlink
#include "../src/unlink.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _unlink
#undef PROGNAME

/* wc.c */
#define PROGNAME "wc"
#define main _wc_main
#define _usage _wc_usage
#define _Prefs _wc_Prefs
#define Prefs wc_Prefs
#define _prefs_parse _wc_prefs_parse
#define _wc __wc
#include "../src/wc.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _wc
#undef PROGNAME

/* who.c */
#define PROGNAME "who"
#define main _who_main
#define _usage _who_usage
#define _Prefs _who_Prefs
#define Prefs who_Prefs
#define _prefs_parse _who_prefs_parse
#define _who __who
#include "../src/who.c"
#undef main
#undef _usage
#undef _Prefs
#undef Prefs
#undef _prefs_parse
#undef _who
#undef PROGNAME


Call calls[] =
{

	{ "basename",	_basename_main	},
	{ "cat",	_cat_main	},
	{ "chgrp",	_chgrp_main	},
	{ "chmod",	_chmod_main	},
	{ "chown",	_chown_main	},
	{ "cksum",	_cksum_main	},
	{ "cmp",	_cmp_main	},
	{ "cp",	_cp_main	},
	{ "date",	_date_main	},
	{ "df",	_df_main	},
	{ "dirname",	_dirname_main	},
	{ "du",	_du_main	},
	{ "echo",	_echo_main	},
	{ "false",	_false_main	},
	{ "file",	_file_main	},
	{ "find",	_find_main	},
	{ "grep",	_grep_main	},
	{ "head",	_head_main	},
	{ "id",	_id_main	},
	{ "kill",	_kill_main	},
	{ "link",	_link_main	},
	{ "ln",	_ln_main	},
	{ "locale",	_locale_main	},
	{ "logname",	_logname_main	},
	{ "ls",	_ls_main	},
	{ "mkdir",	_mkdir_main	},
	{ "mkfifo",	_mkfifo_main	},
	{ "more",	_more_main	},
	{ "mv",	_mv_main	},
	{ "nice",	_nice_main	},
	{ "pr",	_pr_main	},
	{ "printf",	_printf_main	},
	{ "ps",	_ps_main	},
	{ "pwd",	_pwd_main	},
	{ "renice",	_renice_main	},
	{ "rm",	_rm_main	},
	{ "rmdir",	_rmdir_main	},
	{ "sleep",	_sleep_main	},
	{ "strings",	_strings_main	},
	{ "tail",	_tail_main	},
	{ "test",	_test_main	},
	{ "time",	_time_main	},
	{ "touch",	_touch_main	},
	{ "true",	_true_main	},
	{ "tty",	_tty_main	},
	{ "uname",	_uname_main	},
	{ "uniq",	_uniq_main	},
	{ "unlink",	_unlink_main	},
	{ "wc",	_wc_main	},
	{ "who",	_who_main	},
	{ NULL,		NULL		}
};
