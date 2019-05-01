#ifndef OSPROJECT2_MEMORY_H
#define OSPROJECT2_MEMORY_H

#include <process.h>


class MemoryManager {

public:
    explicit MemoryManager(unsigned long maxBytes);

    virtual bool malloc(Process* p) = 0;
    virtual void free(Process* p) = 0;

protected:
    unsigned long freeBytes;

};


class RealMemoryManager : public MemoryManager {

public:
    using MemoryManager::MemoryManager;

    bool malloc(Process* p) override;
    void free(Process* p) override;

};


class SimpleMemoryManager : public MemoryManager {

public:
    using MemoryManager::MemoryManager;

    bool malloc(Process* p) override;
    void free(Process* p) override;

};


class ComplexMemoryManager : public MemoryManager {

public:
    using MemoryManager::MemoryManager;

    bool malloc(Process* p) override;
    void free(Process* p) override;

};

#endif //OSPROJECT2_MEMORY_H
