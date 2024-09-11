#include <stdio.h>
#include <unistd.h>     /* for chdir */
#include <dirent.h>     /* for opendir, readdir, and closedir */
#include <string.h>     /* for strcmp */
#include <stdlib.h>     /* for exit */
#include "syscalls.h"

/* prototypes and dirent structure; references to help in code development 
  int chdir(const char *path);
  DIR *opendir(const char *name);
  struct dirent *readdir(DIR *dirp);
  int closedir(DIR *dirp);
  int strcmp(const char *s1, const char *s2);
  struct dirent {
    ino_t          d_ino;       // Inode number 
    off_t          d_off;       /    const char *input = "/usr/include";

*/

int parseArgs(int, char *[]);
int searchdir(int[], char *directory);
int printResults(char option, int counters[]);

int main(int argc, char *argv[]) {
  /* counters array: each index is a counter for each file type
   * 0: DT_BLK
   * 1: DT_CHR
   * 2: DT_DIR
   * 3: DT_FIFO
   * 4: DT_LNK
   * 5: DT_REG
   * 6: DT_SOCK
   * 7: DT_UNKNOWN
   */
  int counters[8] = {0, 0, 0, 0, 0, 0, 0, 0};

  parseArgs(argc, argv);
  char *directory = argv[2];
  searchdir(counters, directory);
  printResults(argv[1][1], counters);
  return 0;

}

// parseArgs validates the user input
int parseArgs(int argc, char *argv[]) {

  // Checks if the user entered more/less than three arguments
  if (argc != 3) {
    fprintf(stderr, "Error: Invalid number of args (must be 3)\n");
    exit(70);
  }
  // Checks if the user didn't start with '-' for the first argument
  if (argv[1][0] != '-') {
    fprintf(stderr, "Error: Invalid specifier (must start with '-')\n");
    exit(71);
  }
  // Checks if the user didn't enter a valid option
  switch (argv[1][1]) {
    case 'a': break;
    case 'b': break;
    case 'c': break;
    case 'd': break;
    case 'f': break;
    case 'p': break;
    case 'l': break;
    case 'r': break;
    case 's': break;
    case 'u': break;
    default:
      fprintf(stderr, "Error: Invalid specifier\n");
      exit(60);
  }
  if (strlen(argv[1]) == 4){
    if(strcmp(argv[1], "-all") != 0){
      fprintf(stderr, "Error: Invalid specifier\n");
      exit(61);
    }
  }else if (strlen(argv[1]) != 2){
    fprintf(stderr, "Error: Invalid specifier\n");
    exit(62);
  }  
   
  
// Checks the directory that the user enters
  char *directory = argv[2];
  if (directory[0] != '/') {
    fprintf(stderr, "Error: Invalid Directory (Must start with '/')\n");
    exit(80);
  }
  for (unsigned int i = 0; i < strlen(directory); i++) {
    if (argv[2][i] == ' ') {
      fprintf(stderr, "Error: Invalid Directory (Must not contain ' ')\n");
      exit(81);
    }
  }
  return 0;
}

// recursive function to search through directory
int searchdir(int counters[], char *directory) {
  // Chdir, Opendir, Readdir
  Chdir(directory);
  DIR *dptr = Opendir(".");
  struct dirent *fileptr = NULL;

  // Fills up the counters array to its corresponding indexes
  while ((fileptr = Readdir(dptr))) {
    if (strcmp(fileptr->d_name, ".") && strcmp(fileptr->d_name, "..")) {
      if (fileptr->d_type == DT_BLK) {
        counters[0] += 1;
      } else if (fileptr->d_type == DT_CHR) {
        counters[1]+= 1;
      } else if (fileptr->d_type == DT_DIR) {
        counters[2] += 1;
        char newpath[300];
        snprintf(newpath, sizeof(newpath), "%s/%s", directory, fileptr->d_name); // I looked this up on geeksforgeeks.com
        searchdir(counters, newpath);
      } else if (fileptr->d_type == DT_FIFO) {
        counters[3]+= 1;
      } else if (fileptr->d_type == DT_LNK) {
        counters[4]+= 1;
      } else if (fileptr->d_type == DT_REG) {
        counters[5]+= 1;
      } else if (fileptr->d_type == DT_SOCK) {
        counters[6]+= 1;
      } else if (fileptr->d_type == DT_UNKNOWN) {
        counters[7]+= 1;
      }
    }
  }

  Closedir(dptr);
  
  return 0;
}

// print results
int printResults(char option, int counters[]) {
  char options[] = {'b', 'c', 'd', 'f', 'l', 'r', 's', 'u'};
  if (option == 'b') {
    fprintf(stdout, "-%c: %d files\n", option, counters[0]);
  } else if (option == 'c') {
    fprintf(stdout, "-%c: %d files\n", option, counters[1]);
  } else if (option == 'd') {
    fprintf(stdout, "-%c: %d files\n", option, counters[2]);
  } else if (option == 'f' || option == 'p') {
    fprintf(stdout, "-%c: %d files\n", option, counters[3]);
  } else if (option == 'l') {
    fprintf(stdout, "-%c: %d files\n", option, counters[4]);
  } else if (option == 'r') {
    fprintf(stdout, "-%c: %d files\n", option, counters[5]);
  } else if (option == 's') {
    fprintf(stdout, "-%c: %d files\n", option, counters[6]);
  } else if (option == 'u') {
    fprintf(stdout, "-%c: %d files\n", option, counters[7]);
  } else if (option == 'a') {
    for (int i = 0; i < 8; i++) {
      fprintf(stdout, "-%c: %d files\n", options[i], counters[i]);
    } 
   } 
  
  return 0;
}

