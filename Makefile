CFLAGS	= -std=c99 -Wall -Wextra -O3
LDFLAGS	=
LIBS	= -lconfini -ljansson

inivalidate: inivalidate.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)
