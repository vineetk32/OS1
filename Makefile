#CC = ~/bin/gcc
LINKER_FLAGS = -static -ggdb -L .
COMPILE_FLAGS = -Wall -Wextra -ggdb
BINDIR=bin
OBJS = mythread_create.o mythread_util.o mythread_exit.o mythread_queue.o futex.o mythread_key_create.o mythread_getspecific.o mythread_yield.o mythread_self.o mythread_setspecific.o mythread_join.o linklist_kv.o

%.o:	%.c
	${CC} -c -o $@ $< $(COMPILE_FLAGS)

all:	lib a5

lib:	${OBJS}
	ar rc libmythread.a ${OBJS}
a5: lib
	$(CC) p5.c -o a5.x $(COMPILE_FLAGS) -lmythread $(LINKER_FLAGS)

clean:
	rm  -f *.x *.o
