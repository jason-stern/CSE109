CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

server: server.o syscalls.o serverFuncs.o globalDefs.h
	gcc ${LFLAGS} -o server server.o syscalls.o serverFuncs.o
server.o: server.c globalDefs.h
	gcc ${CFLAGS} server.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
serverFuncs.o: serverFuncs.c globalDefs.h
	gcc ${CFLAGS} serverFuncs.c
clean:
	rm -f server.o syscalls.o
	rm -f server