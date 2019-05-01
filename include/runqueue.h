#ifndef OSPROJECT2_RUNQUEUE_H
#define OSPROJECT2_RUNQUEUE_H

#include <queue>

#include <process.h>

class RunQueue {

public:
    Process*      pop();
    void          push(Process *p);
    unsigned long size();

private:
    std::queue<Process*> readyProcs;   // processes that are ready to start executing
    std::queue<Process*> waitingProcs; // processes that are waiting on memory to become available
};

#endif //OSPROJECT2_RUNQUEUE_H
