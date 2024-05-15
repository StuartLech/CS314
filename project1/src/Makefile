#
# This is a makefile for the DLX OS projects.
#

CC = gcc-dlx
AS = dlxasm
CFLAGS = -mtraps -O3

#INCS = $(wildcard *.h)
#SRCS = $(wildcard *.c)
#OBJS = $(addsuffix .o, $(basename $(wildcard *.c))) \
#       $(addsuffix .o, $(basename $(wildcard *.s)))
INCS = dlxos.h traps.h filesys.h memory.h misc.h process.h queue.h \
       synch.h syscall.h
SRCS = filesys.c memory.c misc.c process.c queue.c synch.c traps.c sysproc.c
OBJS = $(addsuffix .o, $(basename $(SRCS)))

os.dlx.obj: os.dlx userprog
	$(AS) -i _osinit -l os.lst os.dlx
	mv os.dlx.obj ../execs

os.dlx: $(OBJS) dlxos.o trap_random.o osend.o
	$(CC) -mtraps -O3 dlxos.o trap_random.o $(OBJS) osend.o -o os.dlx

osend.o: osend.s
	$(CC) -c osend.s

trap_random.o: trap_random.s
	$(CC) -c trap_random.s

dlxos.o: dlxos.s
	$(CC) -c dlxos.s

usertraps.o: usertraps.s
	$(CC) -c usertraps.s

userprog : userprog.o usertraps.o
	$(CC) -mtraps -O3 userprog.o usertraps.o -o userprog.dlx
	$(AS) -l userprog.lst userprog.dlx
	mv userprog.dlx.obj ../execs

Makefile.depend: depend

depend: $(SRCS) $(INCS)
	$(CC) -MM $(SRCS) > Makefile.depend

clean:
	/bin/rm -f *.o *.dlx *.lst *.obj Makefile.depend vm

include Makefile.depend
