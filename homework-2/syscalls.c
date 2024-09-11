#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>      /* for chdir */
#include <dirent.h>

int Chdir(const char *path) {                                         /* error checking/handling wrapper around chdir system call */
  if (chdir(path)) {                                                  /* if chdir system calls returns nonzero value, we have an error */
     fprintf(stderr, "chdir error - %d\n", strerror(errno));  /* use errno global variable to retrieve error message */
     exit(errno);                                                     /* exit with the errno global variable value */
  }
  return 0;                                                           /* if no error, return 0 (which is what chdir returned) */
}

DIR *Opendir(const char *path) {
  DIR *dir = opendir(path);
  if (!dir) {
    fprintf(stderr, "opendir error - %d\n", strerror(errno));
    exit(errno);
  }
  return dir;
}

struct dirent *Readdir(DIR *dirp) {
  struct dirent *dir = readdir(dirp);
  if (!dir && (dir != NULL)) {
    fprintf(stderr, "readdir error - %d\n", strerror(errno));
    exit(errno);
  }
  return dir;
}

int *Closedir(DIR *dirp) {
  int num = closedir(dirp);
  if (num) {
    fprintf(stderr, "closedir error - %d\n", strerror(errno)); 
    exit(errno);
  }
  return 0;

}