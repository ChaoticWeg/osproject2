#ifndef OSPROJECT2_RUNQUEUE_H
#define OSPROJECT2_RUNQUEUE_H

#include <queue>

#include <process.h>

class RunQueue {

public:
    Process*      pop_ready();
    Process*      pop_waiting();
    Process*      peek_waiting();
    void          push(Process *p);
    void          wait(Process *p);
    unsigned long wait_count();
    unsigned long size();

private:
    std::queue<Process*> readyProcs;   // processes that are ready to start executing
    std::queue<Process*> waitingProcs; // processes that are waiting on memory to become available
};

#endif //OSPROJECT2_RUNQUEUE_H
