#include "psTreeFuncs.h"
#include "syscalls.h"
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

char *parseArgs(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Error: invalid number of arguments" << endl;
        exit(10);
    }

    return argv[1];    
}

void searchProcess(char *path, vector<Process>& processes) {
  DIR *dptr = Opendir(path);
  
  struct dirent *fileptr = NULL;
  while ((fileptr = Readdir(dptr))) { // Taken and modified from my P2
    if (strcmp(fileptr->d_name, ".") && strcmp(fileptr->d_name, "..")) {
      if (fileptr->d_type == DT_DIR) {
        char newpath[300];
        snprintf(newpath, sizeof(newpath), "%s/%s", path, fileptr->d_name); // I looked this up on geeksforgeeks.com
        searchProcess(newpath, processes);
      } else if (fileptr->d_type == DT_REG) {
        char newpath[300];
        snprintf(newpath, sizeof(newpath), "%s/%s", path, fileptr->d_name); // I looked this up on geeksforgeeks.com
        FILE *fp = Fopen(newpath, "r");
        Process newProcess = readFileContents(fp);
        processes.push_back(newProcess);
        Fclose(fp);
      }
    }
  }
  Closedir(dptr);
  //cout << processes[0].toString() << endl;
  //cout << "size: " << processes.size() << endl;

 // return processes;
}

Process readFileContents(FILE *fp) {
  Process returnProcess = Process();
  string name;
  string state;
  int pid = 0;
  int ppid = 0;

  size_t len = 0;
  int read;
  char *line = nullptr;

  int result = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    if ((sscanf(line, "Name: %255s", line)) == 1) {
        returnProcess.setName(line);
    }
    if ((sscanf(line, "State: %*[^()] (%[^)])", line)) == 1) { // I looked up this format specifier on stackoverflow
        returnProcess.setState(line);
    }
    if ((sscanf(line, "Pid: %d", &pid)) == 1) {
        returnProcess.setPID(pid);
    }
    if ((sscanf(line, "PPid: %d", &ppid)) == 1) {
        returnProcess.setPPID(ppid);
    }
  }
  
  return returnProcess;
}

//
void make_and_print_psTree(vector<Process>& processes) {
  bool hasPpid_0 = false;

  for (size_t i = 0; i < processes.size() + 1; i++ ) {
    if (processes[i].getPID() == 0) {
      hasPpid_0 = true;
    }

    for (size_t j = 0; j < processes.size() + 1; j++ ) {
      if (i == j) { continue; }

      // if (processes[i].getPID() == processes[j].getPPID()) {
      //   processes[i].addChild(processes[j]);
      // }
    }
  }


  if (!hasPpid_0) { // If there is not a singular origin parent process with a PPid of 0, you are to exit with an error message and a return code of 99.
     cerr << "Error: no process found with a PPID of 0" << endl;
     exit(99);
  }

  bool foundRootParent = false;
  for (size_t i = 0; i < processes.size() + 1; i++) { // finds root Process and calls print_psTree on it
    if (processes[i].getPID() == 1) {
      foundRootParent = true;
      print_psTree(processes, processes[i], "");
    }
  }
  if (!foundRootParent) { // If there is not a singular origin parent process, you are to exit with an error message and a return code of 98.
    cerr << "Error: no origin parent process found" << endl;
    exit(98);
  }

}

void print_psTree(vector<Process> procs, Process parentProcess, string formatter) {
  cout << formatter << parentProcess << endl;
    std::sort(procs.begin(), procs.end(), // Learned this on cppreference
         [](Process& a, Process& b) {
             return a.getPID() < b.getPID();
         });

  for (Process p : procs) {
    if (p.getPPID() == parentProcess.getPID()) {
            //cout << "hey: " << procs.size();
            print_psTree(procs, p, formatter + "----");
        }
  }
  
}