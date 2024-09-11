#include <stdio.h>       /* for fprintf */
#include <stdlib.h>      /* for exit */
#include <errno.h>       /* for errno */
#include <string.h>      /* for strerror */
#include <unistd.h>      /* for chdir */
#include <dirent.h>

FILE *Fopen(const char *path, const char *mode) {     /* same as in prog0 */
  FILE *fp = NULL;
  if ((fp = fopen(path, mode)) == NULL) {
    fprintf(stderr, "Unable to open %s with mode %s - %s", path, mode, strerror(errno));
    exit(errno);
  }
  return fp;
}

void Fclose(FILE *fp) {     /* same as in prog1 */
  if (fp && fclose(fp)) {
    fprintf(stderr, "Unable to close file descriptor %d - %s", fileno(fp), strerror(errno));
    exit(errno);
  }
}

int Fseek(FILE *fp, long offset, int whence) {
  int newOffset;
  if ((newOffset = fseek(fp, offset, whence)) != 0) {
    fprintf(stderr, "Unable to seek using offset %ld with whence %d - %s", offset, whence, strerror(errno));
    exit(errno);
  }
  return newOffset;
}

long Ftell(FILE *fp) {
  long offset;
  if ((offset = ftell(fp)) == -1) {
    fprintf(stderr, "Unable to obtain position using ftell - %s", strerror(errno));
    exit(errno);
  }
  return offset;
}

size_t Fread(void *ptr, size_t item_size, size_t num_items, FILE *fp) {
  size_t items_read = 0;
  /* The function fread() reads num_items of data, each item_size bytes long, from the stream pointed to by fp and storing them at ptr */
  if ((items_read = fread(ptr, item_size, num_items, fp)) == 0)        /* getting 0 may not be an error */
    if (!feof(fp) && ferror(fp)) {   /* this means we did not reach EOF but encountered an error */
      fprintf(stderr, "Encountered error while reading from file descriptor %d - %s", fileno(fp), strerror(errno));
      exit(errno);
    }
  return items_read;
}

size_t Fwrite(const void *ptr, size_t item_size, size_t num_items, FILE *fp) {
  size_t items_written = 0;
  /* The function fwrite() writes num_items of data, each item_size bytes long, from the stream pointed to by fp and storing them at ptr */
  if ((items_written = fwrite(ptr, item_size, num_items, fp)) == 0)    /* only if no items are written do we check for error */
    if (ferror(fp)) {
      fprintf(stderr, "Encountered error while writing to file descriptor %d - %s", fileno(fp), strerror(errno));
      exit(errno);
    }
  return items_written;
}

void *Malloc(size_t size) {
  void *ptr;
  if ((ptr = malloc(size)) == NULL) {
    fprintf(stderr, "Could not allocate space - %s", strerror(errno));
    exit(errno);
  }
  return ptr;
}

int Chdir(const char *path) {                                          /* error checking/handling wrapper around chdir system call */
  if (chdir(path)) {  /* error if -1, 0 upon success */
    fprintf(stderr, "chdir error (%s) - %s\n", path, strerror(errno));  /* use errno global variable to retrieve error message */
    exit(errno);                                                       /* exit with the errno global variable value */
  }
  return 0;                                                            /* if no error, return 0 (which is what chdir returned) */
}

DIR *Opendir(const char *name) {
  DIR *dirp = NULL;
  if (!(dirp = opendir(name))) {  /* error if NULL is returned */
    fprintf(stderr, "opendir error (%s) - %s\n", name, strerror(errno));
    exit(errno);
  }
  return dirp;
}

struct dirent *Readdir(DIR *dirp) {
  errno = 0;  /* clear so an error condition can be detected */
  struct dirent *filep = NULL;
  if (!(filep = readdir(dirp)) && errno) {  /* error if NULL is returned AND errno is nonzero */
    fprintf(stderr, "readdir error - %s\n", strerror(errno));
    exit(errno);
  }
  return filep;
}

int Closedir(DIR *dirp) {
  if (closedir(dirp)) {  /* error if -1, 0 upon success */
    fprintf(stderr, "closedir error - %s\n", strerror(errno));
    exit(errno);
  }
  return 0;
}