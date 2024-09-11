#include "psTreeFuncs.h"
#include "syscalls.h"
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv) { // psTree /home/merle/109/inClassPrograms/proc3
    char *path = parseArgs(argc, argv);
    vector<Process> processes;
    searchProcess(path, processes);
    make_and_print_psTree(processes);
    return 0;
}