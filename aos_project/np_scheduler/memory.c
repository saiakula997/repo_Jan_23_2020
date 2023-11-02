#include "memory.h"

/* Heap Size is Coupled with Linker Script */
#define HEAP_SIZE   0x10000
#define BLOCK_SIZE  64
#define BLOCK_COUNT (HEAP_SIZE/BLOCK_SIZE)


typedef struct heap_memory_handler{
    uint8_t *heap_start;
    uint8_t block[BLOCK_COUNT];       
    uint32_t total_blocks;
    uint32_t available_blocks;
    uint32_t total_size;
    uint32_t available_size;
} heap_memory_handler_t;

static heap_memory_handler_t _heap_memory_handler = { NULL, };


void inti_memory(uint8_t *heap){
    memset((void*)&_heap_memory_handler, 0, sizeof(heap_memory_handler_t));
    _heap_memory_handler.heap_start = heap;
    _heap_memory_handler.available_blocks=BLOCK_COUNT;
    _heap_memory_handler.total_blocks=BLOCK_COUNT;
    _heap_memory_handler.available_size=HEAP_SIZE;
    _heap_memory_handler.total_size=HEAP_SIZE;
    memset((void*)_heap_memory_handler.heap_start, 0, HEAP_SIZE);    
}


void* malloc(size_t size){
    static uint8_t  block_id = 1;
    uint8_t *ptr = NULL, served=0;
    uint32_t blocks_req = (size/BLOCK_SIZE) + ((size%BLOCK_SIZE)!=0);
    if(blocks_req<= _heap_memory_handler.available_blocks){
        for(uint32_t i=0; (i<BLOCK_COUNT)&&(!served); i++){
            if(_heap_memory_handler.block[i]==0){
                for(uint32_t j=0; j<blocks_req; j++){
                    _heap_memory_handler.block[i+j] = block_id;
                    served=1;
                    print(" BLOCK [%u]  Block ID [%u] \n", (i+j+1), block_id);
                }
                if(served){
                    ptr = (uint8_t*)(_heap_memory_handler.heap_start + (i*BLOCK_SIZE));
                    block_id++;
                    _heap_memory_handler.available_blocks -= blocks_req;
                    _heap_memory_handler.available_size -= (blocks_req*BLOCK_SIZE);
                }
            }
        }
    }
    print(" Heap Start [%u] Heap ptr Allocated [%u] \n", _heap_memory_handler.heap_start, ptr);
    return (void *)ptr;
}


void free(void* ptr){
    
}

void print_heap_block_list(void){
    print("--------------- BLOCKS -----------------\n");
    for(uint32_t i=0; i<(_heap_memory_handler.total_blocks - _heap_memory_handler.available_blocks)+1; i++){
        print("Block [%u] Block ID[%u] \n", i, _heap_memory_handler.block[i]);
    }
    print("----------------------------------------\n");
}