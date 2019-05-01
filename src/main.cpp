#include <cstdio>
#include <vector>

#include <process.h>

const int PROC_COUNT = 50; // number of processes to generate

int main() {

    // generate processes
    std::vector<Process> procs;
    procs.reserve(PROC_COUNT);
    for (int i = 0; i < PROC_COUNT; i++) {
        procs.push_back(Process::generate());
    }

    // print the processes
    // TODO: actually do logic stuffbbb
    for (Process proc : procs) {
        printf("%s\n", proc.to_string().c_str());
    }

    return 0;
}
