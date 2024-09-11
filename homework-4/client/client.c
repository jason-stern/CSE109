#include "globalDefs.h"
#include "syscalls.h"
#include "clientFuncs.h"
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

int main(void) {

  struct sockaddr_in serverAddr;
  struct hostent* host = gethostbyname("localhost"); // resolve the server address (convert from symbolic name to IP number)
  int serverPort = 9087;
  char msg[1024];
  int socketFD = Socket(AF_INET, SOCK_STREAM, 0);
  connectToServer(socketFD, serverAddr, host, serverPort);
  runCmds(socketFD, msg);

  Close(socketFD); // close socketFD
  return 0;
}