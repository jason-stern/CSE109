#include <stdio.h>
#include <stdlib.h>     /* for exit */
#include <string.h>     /* for strcmp */
#include <sys/socket.h>
#include <netinet/in.h>
#include "globalDefs.h" /* for NUM_BYTES_TO_COPY_AT_A_TIME */
#include "syscalls.h"



int getPort(int port) {
  if((port < 9001 || port > 9099)) {
    fprintf(stderr, "invalid port number entered\n");
    exit(99);
  }
  return port;
}

int clientConnect(int listenFD) {
  socklen_t clientAddr_len;
  Bind(listenFD, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
  Listen(listenFD, 1);
  int acceptFD = Accept(listenFD, (struct sockaddr*)&clientAddr, &clientAddr_len);
  Close(listenFD);
  return acceptFD;
}

ssize_t sending(int acceptFD, char msg[]) {
  int bytes_left, bytes_xferd;
  char *msg_ptr = &msg[0];
  bytes_left = strlen(msg) + 1;
  while(bytes_left > 0) {
    bytes_xferd = Send(acceptFD, msg_ptr, ITEMS_TO_COPY, 0);
    bytes_left -= bytes_xferd;
    msg_ptr += bytes_xferd;
  }
  fprintf(stdout, "Message sent\n");
  return (ssize_t)bytes_xferd;
}

char getInput(int acceptFD, char msg[]) {
    sending(acceptFD, msg);
    memset(msg, '\0', 1024*sizeof(char));
    ssize_t bytes_xferd = Recv(acceptFD, msg, 1023, 0);
    msg[bytes_xferd] = '\0';
    char c = msg[0];
    /*if(c == 1 || c == 2 || c == 3) {
      fprintf(stdout, "%d\n", c);
      return c;
    }
    else {
      msg = (char*)"Invalid choice. Please enter 1, 2 or 3.";
    }*/
    fprintf(stdout, "Client requested option: %c\n", c);
    return c;
}

size_t reading(FILE *fp, char buffer[]) {
  size_t bytes_xferd = 0;
  size_t bytes_read = 0;
  while((bytes_read = Fread(buffer, sizeof(char), ITEMS_TO_COPY, fp)) > 0) {
    bytes_xferd += bytes_read;
  }
  bytes_xferd += bytes_read;
  return bytes_xferd;
}

unsigned long hash(unsigned char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++)) {
    hash = ((hash << 5) + hash) + c;   /* hash(i) = hash(i-1) * 33 + c */
  }
  return hash;
}

char *JSON(char *name, char *type, size_t items_read, unsigned long digSig) {
  char *json_str = (char*)Malloc(256);
  sprintf(json_str, "{\n \"file_name\": \"%s\",\n \"file_size\": %zu,\n \"file_type\": \"%s\",\n \"file_signature\": %lu\n}", name, items_read, type, digSig);
  return json_str;
}

void crypto(char *buffer) {
  for (int i = 0; i < msgLen; i++) {
  buffer[i] ^= key[i];
  }
}

char messaging(int acceptFD) {
  char msg[1024] = "Which file would you like to be sent: csjobs (1), urandom (2), wealth (3)";
  char c = getInput(acceptFD, msg);
  const char *path;
  char *name, *type;
  switch(c) {
    case '1':
      path = (char*)"/home/merle/109/inClassPrograms/csjobs";
      name = (char*)"csjobs";
      type = (char*)"text";
      break;
    case '2':
      path = (const char*)"/home/merle/109/inClassPrograms/urandom";
      name = "urandom";
      type = "binary";
      break;
    case '3':
      path = (char*)"/home/merle/109/inClassPrograms/wealth";
      name = (char*)"wealth";
      type = (char*)"text";
      break;
    case '0':
      memset(msg, '\0', 1024*sizeof(char));
      break;
  }
  if (c == '0') {
    return 'q';
  }
  FILE *fp = Fopen(path, "r");
  char buffer[ITEMS_TO_COPY];
  size_t items_read = reading(fp, buffer);
  unsigned long digSig = hash((unsigned char*)buffer);
  char *json = JSON(name, type, items_read, digSig);
  crypto(json);
  sending(acceptFD, json); // Send json (file info) to client

  memset(msg, '\0', 1024*sizeof(char));
  int total_bytes = 0;
  int b = 0;
  while ((b = Fread(msg, sizeof(char), ITEMS_TO_COPY, fp) > 0)) {
    Send(acceptFD, msg, ITEMS_TO_COPY, 0);
    total_bytes += b;
  }

  memset(msg, '\0', 1024*sizeof(char));
  ssize_t bytes_xferd = Recv(acceptFD, msg, 1023, 0);
  fprintf(stdout, "Message received (%d bytes)\n", bytes_xferd); // "Thanks! Server-dude!"
  crypto(msg);
  fprintf(stdout, "%s\n", msg);
  
  /*
  memset(msg, '\0', 1024*sizeof(char));
  char message2[] = "Request another file? (enter 1, 2, or 3; 0 to quit): ";
  crypto(msg);
  bytes_xferd = Send(acceptFD, message2, 53, 0); */
  /* recv ready signal */

  //crypto(buffer);
  //sending(acceptFD, buffer);
  
  /* add recv check for if file is all good */

  /* check for exit conidition (set acceptFD to null or something) */
  /*exit = 0;
  Close(acceptFD);*/
  return c;
}