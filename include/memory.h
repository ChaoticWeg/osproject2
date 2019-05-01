#ifndef OSPROJECT2_MEMORY_H
#define OSPROJECT2_MEMORY_H

#include <process.h>

class MemoryManager {

public:
    virtual bool malloc(Process* p) = 0;
    virtual void free(Process* p) = 0;

};

class SimpleMemoryManager : public MemoryManager {

public:
    explicit SimpleMemoryManager(unsigned long maxBytes);

    bool malloc(Process* p) override;
    void free(Process* p) override;

private:
    unsigned long freeBytes;

};

class ComplexMemoryManager : public MemoryManager {

public:
    explicit ComplexMemoryManager(unsigned long maxBytes);

    bool malloc(Process* p) override;
    void free(Process* p) override;

private:
    unsigned long freeBytes;

};

#endif //OSPROJECT2_MEMORY_H
