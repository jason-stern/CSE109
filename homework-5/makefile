CFLAGS=-g -c -Wall -Wextra -Wwrite-strings
LFLAGS=-g

psTree: psTree.o syscalls.o psTreeFuncs.o process.o 
	g++ ${LFLAGS} -o psTree psTree.o syscalls.o psTreeFuncs.o process.o
psTree.o: psTree.cpp
	g++ ${CFLAGS} psTree.cpp
syscalls.o: syscalls.c
	g++ ${CFLAGS} syscalls.c
psTreeFuncs.o: psTreeFuncs.cpp
	g++ ${CFLAGS} psTreeFuncs.cpp
process.o: process.cpp
	g++ ${CFLAGS} process.cpp