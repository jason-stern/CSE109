CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

fileManip: fileManip.o syscalls.o fileManipFuncs.o printMsgs.o
	gcc ${LFLAGS} -o fileManip fileManip.o syscalls.o fileManipFuncs.o printMsgs.o
fileManip.o: fileManip.c
	gcc ${CFLAGS} fileManip.c
syscalls.o: syscalls.c
	gcc ${CFLAGS} syscalls.c
fileManipFuncs.o: fileManipFuncs.c
	gcc ${CFLAGS} fileManipFuncs.c
printMsgs.o: printMsgs.h
	gcc ${CFLAGS} printMsgs.h
clean:
	rm -f fileManip.o fileManipFuncs.o syscalls.o
	rm -f fileManip