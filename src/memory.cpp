#include <memory.h>

MemoryManager::MemoryManager(unsigned long maxBytes){
    this->freeBytes = maxBytes;
}

bool RealMemoryManager::malloc(Process *p) {
    if (p->memory_usage > this->freeBytes) { // memory usage exceeds free bytes
        return false;
    }

    // try to actually allocate memory
    void* memory = ::malloc(p->memory_usage);
    if (memory != nullptr) { // allocation succeeded
        p->memory_ptr = memory;
        return true;
    } else { // allocation failed
        return false;
    }
}

void RealMemoryManager::free(Process *p) {
    if (p->memory_ptr != nullptr) {
        p->memory_ptr = nullptr;
        this->freeBytes += p->memory_usage;
    }
}

bool SimpleMemoryManager::malloc(Process *p) {
    // TODO: TBI
    return false;
}

void SimpleMemoryManager::free(Process *p) {
    // TODO: TBI
}

bool ComplexMemoryManager::malloc(Process *p) {
    // TODO: TBI
    return false;
}

void ComplexMemoryManager::free(Process *p) {
    // TODO: TBI
}
