#include <stdio.h>
#include <string.h> /* memset */
#include <sys/socket.h>
#include <netinet/in.h>
#include "syscalls.h"
#include "globalDefs.h"
#include "serverFuncs.h"

int main(int argc, char *argv[]) {
  int listenFD, acceptFD;
  (void) argc;
  int port;
  sscanf(argv[1], "%d", &port);
  int listenPort = getPort(port);

  listenFD = Socket(AF_INET, SOCK_STREAM, 0);

  memset(&serverAddr, '\0', sizeof(serverAddr));  
  serverAddr.sin_family = AF_INET;               
  serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);// set address to any (all 0s)
  serverAddr.sin_port = htons(listenPort);

  /*acceptFD = clientConnect(listenFD);*/

  socklen_t clientAddr_len;
  Bind(listenFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  Listen(listenFD, 1);
  acceptFD = Accept(listenFD, (struct sockaddr*)&clientAddr, &clientAddr_len);
  Close(listenFD);
  
  int exit = 1;
  while(exit) {
    char c = messaging(acceptFD);
    if (c == 'q') {
       fprintf(stdout, "Exiting program\n");
       break;
    }
  }

  return 0;
}