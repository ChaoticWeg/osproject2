#ifndef OSPROJECT2_MEMORY_H
#define OSPROJECT2_MEMORY_H

#include <process.h>

class MemoryManager {

public:
    explicit MemoryManager(unsigned long maxBytes);

    bool malloc(Process* p);
    void free(Process* p);

private:
    unsigned long freeBytes;

};

#endif //OSPROJECT2_MEMORY_H
