// In your C++ code, you are to create a single class named "Process" to store information about each process you encounter.
// As you encounter a valid process, you will need to create an instance of this class that contains private members to hold
// that process' PID, PPID, Name, and State. You will also need to keep some form of list (vector, array, or list container)
// to hold all its children. Thus, you will need to have setter (mutator) and getter (accessor) functions to set or get these variable values.
// You may also need/have additional member functions.

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Process {
    public:
        int getPID();
        void setPID(int newPID);

        int getPPID();
        void setPPID(int newPPID);

        string getName();
        void setName( string newName );

        string getState();
        void setState( string newState );

        void addChild(Process child);
        vector<Process> getChildren();


        Process();
        Process(int pid, int ppid, string name, string state);
        //~Process();
        friend std::ostream& operator<<(std::ostream& os, const Process& process) {
            os << process.name << " (" + to_string(process.PID) + "," + process.state + ")";
            return os;
        }
        // string toString();
    private:
        int PID;
        int PPID;
        string name;
        string state;
        vector<Process> children;
};