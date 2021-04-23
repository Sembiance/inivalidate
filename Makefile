CFLAGS	= -std=c99 -Wall -Wextra -O3
LDFLAGS	=
LIBS	= -lconfini

inivalidate: inivalidate.c
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)
