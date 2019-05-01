#ifndef OSPROJECT2_PROCESS_H
#define OSPROJECT2_PROCESS_H

#include <tuple>
#include <string>
#include <vector>

// cpu burst time in cycles
#define PROC_MIN_CPU 10
#define PROC_MAX_CPU 50000000

// mem usage in bytes
#define PROC_MIN_MEM 250
#define PROC_MAX_MEM 200000

class Process {

public:
    static Process* generate();

    inline int pid() const { return _pid; }
    inline unsigned long cpu() const { return _cpu; }
    inline unsigned long mem() const { return _mem; }

    std::string  to_string();

private:
    static int lastPid;

    static unsigned long gen_ulong(unsigned long, unsigned long);

    inline static unsigned long gen_cpu() { return gen_ulong(PROC_MIN_CPU, PROC_MAX_CPU); }
    inline static unsigned long gen_mem() { return gen_ulong(PROC_MIN_MEM, PROC_MAX_MEM); }

    int _pid;
    unsigned long _cpu, _mem;

    Process(int p, unsigned long c, unsigned long m) : _pid(p), _cpu(c), _mem(m) {};

};

#endif //OSPROJECT2_PROCESS_H
