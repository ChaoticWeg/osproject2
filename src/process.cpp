#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <iostream>

#include <process.h>

int Process::lastPid = 0;

Process* Process::generate() {
    int pid = ++lastPid;
    unsigned long cpu = gen_cpu();
    unsigned long mem = gen_mem();

    return new Process(pid, cpu, mem);
}

unsigned long Process::gen_ulong(unsigned long min, unsigned long max) {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<unsigned long> distribution(min, max);
    return distribution(engine);
}

std::string Process::to_string() {
    std::stringstream ss;
    ss << pid << "," << cpu_cycles << "," << memory_usage;
    return ss.str();
}
