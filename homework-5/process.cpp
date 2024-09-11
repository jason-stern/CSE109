#include "process.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Process::getPID() { return PID; }
void Process::setPID(int newPID) { PID = newPID; }

int Process::getPPID() { return PPID; }
void Process::setPPID(int newPPID) { PPID = newPPID; }

string Process::getName() { return name; }
void Process::setName( string newName ) { name = newName; }

string Process::getState() { return state; }
void Process::setState(string newState ) { state = newState; }

void Process::addChild(Process child) {
    this->children.push_back(child);
}

vector<Process> Process::getChildren() {
    return children;
}

Process::Process() {
    this->PID = -1;
    this->PPID = -1;
    this->name = "";
    this->state = "";
}

Process::Process(int pid, int ppid, string name, string state) {
     this->PID = pid;
     this->PPID = ppid;
     this->name = name;
     this->state = state;
}

// string Process::toString() {
//     string returnString = getName() + " (" + to_string(getPID()) + ", " + getState() + ") children:";
//     for (Process child : children) {
//          returnString += child.getName() + ",";
//     }
//     returnString += " parent:" + to_string(getPPID());
//     return returnString;
// }