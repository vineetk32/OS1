CC = ~/bin/gcc
LINKER_FLAGS = -static -ggdb -lmythread -L .
COMPILE_FLAGS = -Wall -Wextra -ggdb
BINDIR=bin
OBJS = mythread_create.o mythread_util.o mythread_exit.o mythread_queue.o futex.o mythread_key_create.o mythread_getspecific.o mythread_yield.o mythread_self.o mythread_setspecific.o mythread_join.o linklist_kv.o mythread_tester.o

%.o:	%.c
	${CC} -c -o $@ $< $(COMPILE_FLAGS)

all:	$(OBJS)
	$(CC) $(OBJS) -o $(BINDIR)/mythread.x $(LINKER_FLAGS)
lib:	${OBJS}
	ar rc libmythread.a ${OBJS}

clean:
	rm ${BINDIR}/*.x *.o
