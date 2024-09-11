#include "globalDefs.h"
#include "syscalls.h"
#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>      /* for chdir */
#include <dirent.h>
#include <time.h>        /* for nanosleep */
#include <sys/types.h>   /* for getpid, getppid */
#include <unistd.h>      /* for getpid, getppid, read, write, close*/
#include <sys/socket.h>
#include <netinet/in.h> // struct soccaddr_in
#include <netdb.h>

void connectToServer(int socketFD, struct sockaddr_in serverAddr, struct hostent* host, int serverPort);
void runCmds(int socketFD, char msg[1024]);
void crypto(char buffer[]);
unsigned long hash(unsigned char *str);