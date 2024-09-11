#include <stdlib.h>
#include <string>
#include <iostream>
#include "syscalls.h"
#include "process.h"
using namespace std;

// psTree /home/merle/109/inClassPrograms/proc3
char *parseArgs(int argc, char **argv);

// Searches directory and fills a vector of processes
void searchProcess(char *path, vector<Process>& processes);

// Reads a status file, and uses its information to construct and return a Process.
Process readFileContents(FILE *fp);

// Takes a vector of processes and tries to make a psTree. If successful, the function print_psTree is called
void make_and_print_psTree(vector<Process>& processes);

// Recursive print function to print a formatted output of psTree
void print_psTree(vector<Process> procs, Process parentProcess, string formatter);
