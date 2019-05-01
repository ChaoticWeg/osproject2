#ifndef OSPROJECT2_CPU_H
#define OSPROJECT2_CPU_H

#include <process.h>

const unsigned int CPU_FREQ = 4000000000; // number of cycles per second

class CPU {

public:

    /**
     * Advances the CPU by the specified number of cycles.
     */
    void advance(unsigned int cycles);

    /**
     * @return Total number of cycles that have occurred since the CPU was initialized.
     */
    unsigned long get_current_cycle();

    /**
     * @return Number of cycles remaining until the Process completes.
     */
    unsigned long get_remaining_cycles();

    /**
     * @return Process currently running on the CPU.
     */
    Process* get_process();

    /**
     * Runs a Process on the CPU.
     *
     * @param p Process to run
     */
    void run(Process* p);

private:
    unsigned long cycle = 0;

    Process* process = nullptr; // process that is currently running
    unsigned long remainingCycles = 0; // number of cycles remaining for the process

};

#endif //OSPROJECT2_CPU_H
