CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

client: client.o syscalls.o clientFuncs.o globalDefs.h
	gcc ${LFLAGS} -o client client.o syscalls.o clientFuncs.o
client.o: client.c globalDefs.h
	gcc ${CFLAGS} client.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
clientFuncs.o: clientFuncs.c globalDefs.h
	gcc ${CFLAGS} clientFuncs.c
clean:
	rm -f client.o syscalls.o
	rm -f client