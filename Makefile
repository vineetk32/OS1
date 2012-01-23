all:
	gcc mythread_create.c util.c -o mythread -Wall -Wextra -pedantic -ggdb -static
