TARGETS	= $(OBJDIR)utilbox
OBJDIR	=
PREFIX	= /usr/local
DESTDIR	=
BINDIR	= $(PREFIX)/bin
SBINDIR	= $(PREFIX)/sbin
CC	= cc
CPPFLAGSF=
CPPFLAGS=
CFLAGSF	= -W
CFLAGS	= -Wall -g -O2 -pedantic
RM	= rm -f
LN	= ln -f
MKDIR	= mkdir -m 0755 -p
INSTALL	= install


all: $(TARGETS)

utilbox_OBJS = $(OBJDIR)utilbox.o $(OBJDIR)utils.o
utilbox_CFLAGS = $(CPPFLAGSF) $(CPPFLAGS) $(CFLAGSF) $(CFLAGS)
utilbox_LDFLAGS = $(LDFLAGSF) $(LDFLAGS)

$(OBJDIR)utilbox: $(utilbox_OBJS)
	$(CC) -o $(OBJDIR)utilbox $(utilbox_OBJS) $(utilbox_LDFLAGS)

$(OBJDIR)utilbox.o: utilbox.c utilbox.h
	$(CC) $(utilbox_CFLAGS) -o $(OBJDIR)utilbox.o -c utilbox.c

$(OBJDIR)utils.o: utils.c utilbox.h
	$(CC) $(utilbox_CFLAGS) -o $(OBJDIR)utils.o -c utils.c

clean:
	$(RM) -- $(utilbox_OBJS)

distclean: clean
	$(RM) -- $(TARGETS)

install: $(TARGETS)

uninstall:

.PHONY: all clean distclean install uninstall
