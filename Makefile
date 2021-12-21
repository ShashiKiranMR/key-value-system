CC		= gcc
CFLAGS	= -g
RM		= rm -f

default: all

all: kv

kv: kv.c
	$(CC) $(CFLAGS) -o kv kv.c

clean:
	$(RM) kv
