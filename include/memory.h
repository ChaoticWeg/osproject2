#ifndef OSPROJECT2_MEMORY_H
#define OSPROJECT2_MEMORY_H

#import <map>

#include <process.h>

struct Partition {
    unsigned long len;    // length of the partition in bytes
    unsigned long offset; // offset of the partition
};


class MemoryManager {

public:

    /**
     * Allocates memory for the specified Process.
     *
     * @param len Length of memory that should be allocated
     * @return Address of the allocated memory, or nullptr on failure.
     */
    virtual void* malloc(unsigned long len) = 0;

    /**
     * Releases memory for the specified Process.
     *
     * @param ptr Pointer to the memory location
     */
    virtual void  free(void* ptr) = 0;
};


class RealMemoryManager : public MemoryManager {

public:
    using MemoryManager::MemoryManager;

    void* malloc(unsigned long len) override;
    void  free(void* ptr) override;
};


class SimpleMemoryManager : public MemoryManager {

public:
    explicit SimpleMemoryManager(unsigned long maxBytes);

    void* malloc(unsigned long len) override;
    void  free(void* ptr) override;

protected:
    unsigned long maxBytes; // maximum number of bytes in memory
    void* memory;           // pointer to memory allocated to the memory manager
    std::vector<Partition*> table; // partition table

    /**
     * Finds the first hole that is at least the specified minimum size, constructing a new
     * Partition to insert into that hole.
     *
     * @param minLen Minimum size of the hole
     * @return A new Partition to insert into the hole, or nullptr if no such hole exists
     */
    Partition* find_hole(unsigned long minLen);

};


class ComplexMemoryManager : public SimpleMemoryManager {

public:
    using SimpleMemoryManager::SimpleMemoryManager;

    void* malloc(unsigned long len) override;
    void  free(void* ptr) override;

};

#endif //OSPROJECT2_MEMORY_H
