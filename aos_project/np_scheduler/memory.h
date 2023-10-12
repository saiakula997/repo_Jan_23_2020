#ifndef MEMORY_H
#define MEMORY_H

#include "utils.h"

void print_heap_block_list(void); 
void inti_memory(uint8_t *heap);
void* malloc(size_t size);
void free(void * ptr);



#endif
