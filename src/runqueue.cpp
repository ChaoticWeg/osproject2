#include <runqueue.h>

Process* RunQueue::pop_ready() {
    Process* p = this->readyProcs.front();
    this->readyProcs.pop();
    return p;
}

Process* RunQueue::pop_waiting() {
    Process* p = this->waitingProcs.front();
    this->waitingProcs.pop();
    return p;
}

Process *RunQueue::peek_waiting() {
    return this->waitingProcs.front();
}

void RunQueue::push(Process *p) {
    this->readyProcs.push(p);
}

void RunQueue::wait(Process *p) {
    this->waitingProcs.push(p);
}

unsigned long RunQueue::size() {
    return this->waitingProcs.size() + this->readyProcs.size();
}

unsigned long RunQueue::wait_count() {
    return this->waitingProcs.size();
}
