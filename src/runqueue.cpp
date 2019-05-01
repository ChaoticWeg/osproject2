#include <runqueue.h>

Process* RunQueue::pop() {
    Process* p = this->readyProcs.front();
    this->readyProcs.pop();
    return p;
}

void RunQueue::push(Process *p) {
    this->readyProcs.push(p);
}

unsigned long RunQueue::size() {
    return this->readyProcs.size();
}
