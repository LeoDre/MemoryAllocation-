PROGRAMS=memgrind
SRCS = mymalloc.c memgrind.c 
OBJS = $(SRCS: .c=.o)
CC = gcc
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
RM = rm -f
memgrind: $(OBJS) 
	$(CC) $(LFLAGS) $(OBJS) -o memgrind
mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) mymalloc.c
memgrind.o: memgrind.c
	$(CC) $(CFLAGS) memgrind.c
.PHONY: clean
clean:
	$(RM) *.o $(PROGRAMS)