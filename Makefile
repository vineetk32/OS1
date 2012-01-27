CC = ~/bin/gcc
LINKER_FLAGS = -static
COMPILE_FLAGS = -Wall -Wextra -ggdb
BINDIR=bin
OBJS = mythread_create.o mythread_util.o mythread_exit.o mythread_queue.o futex.o mythread_key_create.o mythread_getspecific.c mythread_yield.c mythread_self.c mythread_setspecific.c mythread_join.c linklist_kv.c

%.o:	%.c
	${CC} -c -o $@ $< $(COMPILE_FLAGS)

all:	$(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/mythread.x $(LINKER_FLAGS)

clean:
	rm ${BINDIR}/*.x *.o
