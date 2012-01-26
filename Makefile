CC = ~/bin/gcc
LINKER_FLAGS = -lrt -static
COMPILE_FLAGS = -Wall -Wextra -ggdb
OBJDIR=objs
BINDIR=bin
OBJS = mythread_create.o mythread_util.o mythread_exit.o mythread_queue.o futex.o

%.o:	%.c
	${CC} -c -o $@ $< $(COMPILE_FLAGS)

all:	$(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/mythread.x $(LINKER_FLAGS)

clean:
	rm ${BINDIR}/*.x ${OBJDIR}/*.o
