#ifndef OSPROJECT2_PROCESS_H
#define OSPROJECT2_PROCESS_H

#include <tuple>
#include <string>
#include <vector>

// cpu burst time in cycles
#define PROC_MIN_CPU 10
#define PROC_MAX_CPU 100

// mem usage in bytes
#define PROC_MIN_MEM 250
#define PROC_MAX_MEM 200000

class Process {

public:
    static Process* generate();

    inline int get_pid() const { return pid; }
    inline unsigned long get_cpu_cycles() const { return cpu_cycles; }
    inline unsigned long get_memory_usage() const { return memory_usage; }

    std::string  to_string();

private:
    static int lastPid;

    static unsigned long gen_ulong(unsigned long, unsigned long);
    inline static unsigned long gen_cpu() { return gen_ulong(PROC_MIN_CPU, PROC_MAX_CPU); }
    inline static unsigned long gen_mem() { return gen_ulong(PROC_MIN_MEM, PROC_MAX_MEM); }

    int pid;
    unsigned long cpu_cycles, memory_usage;
    void* memory_ptr = nullptr;

    Process(int p, unsigned long c, unsigned long m) : pid(p), cpu_cycles(c), memory_usage(m) {};

friend class SimpleMemoryManager;
friend class ComplexMemoryManager;

};

#endif //OSPROJECT2_PROCESS_H
