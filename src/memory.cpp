#include <memory.h>

/*
 * RealMemoryManager
 */

void* RealMemoryManager::malloc(unsigned long len) {
    void* memory = ::malloc(len);
    if (memory != nullptr) { // allocation succeeded
        return memory;
    } else { // allocation failed
        return nullptr;
    }
}

void RealMemoryManager::free(void* ptr) {
    ::free(ptr);
}


/*
 * SimpleMemoryManager
 */

SimpleMemoryManager::SimpleMemoryManager(unsigned long maxBytes) {
    this->maxBytes = maxBytes;
    this->memory = ::malloc(maxBytes); // allocate memory for the memory manager
}

void* SimpleMemoryManager::malloc(unsigned long len) {

    // find a hole that fits the process' memory requirements
    Partition* partition = this->find_hole(len);
    if (partition == nullptr) { // no such hole exists, failure
        return nullptr;
    }

    // insert the partition into the partition table so we can keep track of allocations
    if (!this->table.empty()) { // table has partitions, insert into it
        for (unsigned long i = 0; i < this->table.size(); i++) {
            if (this->table[i]->offset + this->table[i]->len == partition->offset || i + 1 == this->table.size()) {
                this->table.insert(this->table.begin() + i + 1, partition);
                break;
            }
        }
    } else { // table has no partitions yet, just add it in
        this->table.push_back(partition);
    }

    // return starting address of the allocated memory
    return (char*)this->memory + partition->offset;
}

void SimpleMemoryManager::free(void* ptr) {
    unsigned long offset = (char*)ptr - (char*)this->memory; // offset of the partition

    // find the partition with this offset
    unsigned long index = -1;
    for (unsigned long i = 0; i < this->table.size(); i++) {
        if (this->table[i]->offset == offset) {
            index = i;
            break;
        }
    }

    // remove the partition from the table
    if (index >= 0) {
        this->table.erase(this->table.begin() + index);
    }
}

Partition* SimpleMemoryManager::find_hole(unsigned long minLen) {
    unsigned long len;       // length of the current hole

    // try to find a hole
    Partition* partition = nullptr;
    if (!this->table.empty()) { // table has partitions, find holes between them
        for (unsigned long i = 0; i < this->table.size(); i++) {
            Partition* compPartition = this->table[i];

            // calculate length of hole
            len = (i + 1 < this->table.size() ? this->table[i + 1]->offset : this->maxBytes)
                    - (compPartition->offset + compPartition->len);
            if (len >= minLen) { // hole meets the min length, build new partition
                partition = new Partition();
                partition->offset = compPartition->offset + compPartition->len;
                partition->len = minLen;
                break;
            }
        }
    } else if (this->maxBytes > minLen) { // table has no partitions, all memory is available
        partition = new Partition();
        partition->offset = 0;
        partition->len = minLen;
    }

    return partition;
}


/*
 * ComplexMemoryManager
 */

void* ComplexMemoryManager::malloc(unsigned long len) {
    // TODO: TBI
    return nullptr;
}

void ComplexMemoryManager::free(void* ptr) {
    // TODO: TBI
}
