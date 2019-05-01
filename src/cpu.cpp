#include <cpu.h>

void CPU::advance(unsigned int cycles) {
    this->cycle += cycles;
    if (this->remainingCycles < cycles) { // process completes before end of cycles
        this->remainingCycles = 0;
    } else { // process does not complete or completes exactly at end of cycles
        this->remainingCycles -= cycles;
    }

    if (this->remainingCycles == 0) { // if process completed, clear it out
        this->process = nullptr;
    }
}

unsigned long CPU::get_current_cycle() {
    return this->cycle;
}

unsigned long CPU::get_remaining_cycles() {
    return this->remainingCycles;
}

Process *CPU::get_process() {
    return this->process;
}

void CPU::run(Process* p) {
    this->process = p;
    this->remainingCycles = p->get_cpu_cycles();
}
