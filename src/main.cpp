#include <cstdio>
#include <queue>
#include <iostream>
#include <exception>

#include <cpu.h>
#include <process.h>
#include <memory.h>
#include <runqueue.h>

const int PROC_COUNT = 50; // number of processes to generate
const int PROC_ARRIVAL_INTERVAL = 50; // number of cycles after which to a process arrives

const char PROC_HEADER_FORMAT[] = "%6s  %3s  %10s  %10s  %10s\n";
const char PROC_ROW_FORMAT[] = "%6s  %3i  %10lu  %10lu  %10lu\n";

unsigned long choice(const std::string& message, const std::vector<std::string>& choices);
void print_proc_event(const std::string &event, Process* p, CPU* cpu);

int main() {
    CPU cpu;
    RunQueue runQueue;

    // generate processes
    std::vector<Process *> procs; // all processes
    std::queue<Process *> unscheduledProcs; // vector of process to be scheduled every 50 cycles
    for (int i = 0; i < PROC_COUNT; i++) {
        Process *p = Process::generate();
        procs.push_back(p);
        unscheduledProcs.push(p);
    }

    // calculate the total amount of memory in bytes
    unsigned long totalMemory = 0;
    for (Process *p : procs) {
        totalMemory += p->get_memory_usage();
    }

    // prompt the user to specify the size of memory in bytes
    unsigned long maxMemory = 0;
    printf("Required memory:  %lu\n", totalMemory);
    while (maxMemory == 0) {
        printf("Available memory: ");
        char maxMemoryStr[256];
        std::cin >> maxMemoryStr;
        maxMemory = strtoul(maxMemoryStr, nullptr, 10);
    }
    printf("\n");

    // create a memory manager
    MemoryManager *memory;
    unsigned long memoryManagerChoice = choice("Select a memory manager:", {"Real", "Simple", "Complex"});
    switch (memoryManagerChoice) {
        case 0:
            memory = new RealMemoryManager();
            break;
        case 1:
            memory = new SimpleMemoryManager(maxMemory);
            break;
        default:
            memory = new ComplexMemoryManager(maxMemory);
    }

    // print header
    printf(PROC_HEADER_FORMAT, "Event", "PID", "Cycle", "CPU", "Memory");

    // simulate cpu cycles - stop when no processes remain
    while (runQueue.size() > 0 || !unscheduledProcs.empty() || cpu.get_remaining_cycles() > 0) {

        // a process arrives if current cycle is a multiple of PROC_ARRIVAL_INTERVAL and there is a process to arrive
        if (cpu.get_current_cycle() % PROC_ARRIVAL_INTERVAL == 0 && !unscheduledProcs.empty()) {
            Process* p = unscheduledProcs.front();
            print_proc_event("ARRIVE", p, &cpu);

            // allocate memory for the process
            void* alloc = memory->malloc(p->get_memory_usage());
            if (alloc != nullptr) {
                p->memory_ptr = alloc;
                print_proc_event("MALLOC", p, &cpu);
                runQueue.push(unscheduledProcs.front());
            } else {
                print_proc_event("FAILED", p, &cpu);
            }
            unscheduledProcs.pop();
        }

        // run a process in the runqueue if the CPU is idle and there is something to run
        if (cpu.get_process() == nullptr && runQueue.size() > 0) {
            Process *p = runQueue.pop();
            print_proc_event("START", p, &cpu);
            cpu.run(p);
        }

        // determine what the next cycle to advance to will be
        unsigned long nextCycle = (cpu.get_current_cycle() - (cpu.get_current_cycle() % PROC_ARRIVAL_INTERVAL)
                                   + PROC_ARRIVAL_INTERVAL) - cpu.get_current_cycle();
        if (cpu.get_process() != nullptr) { // process is running
            if (cpu.get_remaining_cycles() <= nextCycle) { // arrival after process end
                nextCycle = cpu.get_remaining_cycles();
            }
        }

        // advance the cpu to next cycle
        Process* currentProcess = cpu.get_process();
        cpu.advance(nextCycle);

        // if process ended, free memory
        if (currentProcess != nullptr && cpu.get_remaining_cycles() == 0) {
            print_proc_event("END", currentProcess, &cpu);

            // free memory allocated by memory manager
            print_proc_event("FREE", currentProcess, &cpu);
            memory->free(currentProcess->memory_ptr);
            currentProcess->memory_ptr = nullptr;
        }
    }

    return 0;
}

void print_proc_event(const std::string &event, Process* p, CPU* cpu) {
    printf(PROC_ROW_FORMAT, event.c_str(), p->get_pid(), cpu->get_current_cycle(), p->get_cpu_cycles(),
           p->get_memory_usage());
}

unsigned long choice(const std::string& message, const std::vector<std::string>& choices) {

    // print choices
    printf("%s\n", message.c_str());
    for (unsigned long i = 0; i < choices.size(); i++) {
        printf("%lu) %s\n", i + 1, choices[i].c_str());
    }

    // prompt for response
    unsigned long val = 0;
    while (val == 0) {
        printf("?) ");
        fflush(stdout);

        char response[256];
        std::cin >> response;
        val = strtoul(response, nullptr, 10);

        if (val > choices.size()) {
            val = 0;
        }
    }
    printf("\n");
    return val - 1;
}
