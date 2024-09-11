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

/**
 * connectToServer
 *
 * Create server address
 * Print the IP address of the server
 * Connect to server
 *
 * @param socketFD socket file-descriptor
 * @param serverAddr socket addresss struct
 * @param host local host
 * @param serverPort port that handles data transfer; group port: 9087
 */
void connectToServer(int socketFD, struct sockaddr_in serverAddr, struct hostent* host, int serverPort) {

  // create server address
  memset(&serverAddr, '\0', sizeof(struct sockaddr_in));
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(serverPort);


  memmove(&(serverAddr.sin_addr.s_addr), host->h_addr_list[0], 4); // write resolved IP address of a server to the address structure

  fprintf(stdout, "Server address = "); // print a resolved address of server (the first IP of the host)
  fprintf(stdout, "%d.", ((int)(host->h_addr_list[0][0] & 0xff)));
  fprintf(stdout, "%d.", ((int)(host->h_addr_list[0][1] & 0xff)));
  fprintf(stdout, "%d.", ((int)(host->h_addr_list[0][2] & 0xff)));
  fprintf(stdout, "%d,\n", ((int)(host->h_addr_list[0][3] & 0xff)));
  fprintf(stdout, "port = %d\n", (int)serverPort);

  Connect(socketFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); // Connect to a remote server
}

/**
 * runCmds
 * Receive and decrypt message
 * Encrypt and send message: "Thanks! Server-dude!"
 * Close socket
 *
 * @param socketFD socket file descriptor
 * @param msg message buffer for receiving message from server
 */
void runCmds(int socketFD, char msg[1024]) {
  while (1) {
    int bytes_xferd = Recv(socketFD, msg, 1023, 0); // receive message: file options (1,2,3)
    fprintf(stdout, "Message received (%d bytes)\n", bytes_xferd);
    //crypto(msg);
    fprintf(stdout, "%s\n", msg);

    // GET USER INPUT (1, 2, or 3)
    char userInput;// = NULL;
    int validInput = 0;
    while (!validInput) {
      fprintf(stdout, "Enter an option: ");
      scanf(" %c", &userInput);
      if (userInput == '1') {
        bytes_xferd = Send(socketFD, "1", 1, 0); // csjobs
        break;
      } else if (userInput == '2') {
        bytes_xferd = Send(socketFD, "2", 1, 0); // urandom
        break;
      } else if (userInput == '3') {
        bytes_xferd = Send(socketFD, "3", 1, 0); // wealth
        break;
      } else if (userInput == 'q') {
        userInput = 'q';
        bytes_xferd = Send(socketFD, "q", 1, 0); // quit
        memset(msg, '\0', 1024/**sizeof(msg)*/);
        break;
      }
      fprintf(stdout, "Invalid option | ");
      //userInput = NULL;
    }

    if (userInput == 'q') {
      break; // stop looping for requests
    }  

    // Receive file JSON information from server
    memset(msg, '\0', 1024/**sizeof(msg)*/);
    bytes_xferd = Recv(socketFD, msg, ITEMS_TO_COPY, 0);
    fprintf(stdout, "Message received (%d bytes)\n", bytes_xferd);
    crypto(msg);
    fprintf(stdout, "%s\n", msg);

    // Receive file info and write to localfile
    memset(msg, '\0', ITEMS_TO_COPY);
    int total_bytes = 0;
    while ((bytes_xferd = Recv(socketFD, msg, ITEMS_TO_COPY, 0) > 0)) {
      Fwrite(socketFD, msg, ITEMS_TO_COPY, 0);
      total_bytes += bytes_xferd;
    }

    memset(msg, '\0', 1024/**sizeof(msg)*/);
    char message[] = "Thanks! Server-dude!";
    crypto(message);
    bytes_xferd = Send(socketFD, message, 21, 0); // send message
    fprintf(stdout, "Message sent\n");

  }

}

void crypto(char buffer[]) {
  
  (void)buffer;
  for (size_t i = 0; i < msgLen; i++) {
    buffer[i] ^= key[i];
  }

}

unsigned long hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}