#ifndef SERVERFUNCS_H
#define SERVERFUNCS_H

int getPort(int port);
int clientConnect(int listenFD);
ssize_t sending(int acceptFD, char msg[]);
char getInput(int acceptFD, char *msg);
size_t reading(FILE *fp, char buffer[]);
unsigned long hash(unsigned char *str);
char *JSON(char *name, char *type, size_t items_read, unsigned long digSig);
void crypto(char *buffer);
char messaging(int acceptFD);

#endif