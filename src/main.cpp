#include <cstdio>
#include <queue>

#include <cpu.h>
#include <process.h>
#include <runqueue.h>

const int PROC_COUNT = 50; // number of processes to generate
const int PROC_ARRIVAL_INTERVAL = 50; // number of cycles after which to a process arrives

const char PROC_HEADER_FORMAT[] = "%6s  %3s  %10s  %10s  %10s\n";
const char PROC_ROW_FORMAT[] = "%6s  %3i  %10lu  %10lu  %10lu\n";

void print_proc_event(const std::string &event, Process* p, CPU* cpu);

int main() {
    CPU cpu;
    RunQueue runQueue;

    // generate processes
    std::queue<Process*> procs; // vector of process to be scheduled every 50 cycles
    for (int i = 0; i < PROC_COUNT; i++) {
        procs.push(Process::generate());
    }

    // print header
    printf(PROC_HEADER_FORMAT, "Event", "PID", "Cycle", "CPU", "Memory");

    // simulate cpu cycles
    while (runQueue.size() > 0 || !procs.empty()) { // stop the simulation when no processes remain

        // determine what the next cycle to advance to will be
        unsigned long nextCycle = (cpu.get_current_cycle() - (cpu.get_current_cycle() % PROC_ARRIVAL_INTERVAL)
                + PROC_ARRIVAL_INTERVAL) - cpu.get_current_cycle();
        if (cpu.get_process() != nullptr) { // process is running
            if (cpu.get_current_cycle() + cpu.get_remaining_cycles() <= nextCycle) { // arrival after process end
                nextCycle = cpu.get_remaining_cycles();
            }
        }

        // a process arrives if current cycle is a multiple of PROC_ARRIVAL_INTERVAL and there is a process to arrive
        if (cpu.get_current_cycle() % PROC_ARRIVAL_INTERVAL == 0 && !procs.empty()) {
            Process* p = procs.front();
            print_proc_event("ARRIVE", p, &cpu);
            runQueue.push(procs.front());
            procs.pop();
        }

        // run a process in the runqueue if the CPU is idle and there is something to run
        if (cpu.get_process() == nullptr && runQueue.size() > 0) {
            Process *p = runQueue.pop();
            print_proc_event("START", p, &cpu);
            cpu.run(p);
        }

        // advance the cpu to next cycle
        Process* currentProcess = cpu.get_process();
        cpu.advance(nextCycle);
        if (cpu.get_process() != currentProcess) {
            print_proc_event("END", currentProcess, &cpu);
        }
    }

    return 0;
}

void print_proc_event(const std::string &event, Process* p, CPU* cpu) {
    printf(PROC_ROW_FORMAT, event.c_str(), p->pid(), cpu->get_current_cycle(), p->cpu(), p->mem());
}
