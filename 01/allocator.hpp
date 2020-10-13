#include <iostream>
#include <cstdio>

class Allocator {
    char *start = nullptr;
    size_t max_size = 0, offset_size = 0;
public:
    void makeAllocator(size_t maxSize) {
        if (start != nullptr) {
            delete [] start;   
        }
        start = new char[maxSize];
        max_size = maxSize;
    }
    char* alloc(size_t size) {
        if (offset_size + size > max_size) {
            return nullptr;
        }
        char *offset = start + offset_size;
        offset_size += size;
        return offset;
    }
    void reset() {
        offset_size = 0;
    }
    ~Allocator() {
        delete [] start;
    }
};
