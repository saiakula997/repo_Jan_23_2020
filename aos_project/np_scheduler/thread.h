#ifndef THREAD_H
#define THREAD_H

#include "types.h"

typedef void (* thread_t) (struct thread_handler *handler);

typedef enum thread_status {
    READY,
    RUN,
    SUSPENDED,
    STOP,
} thread_status_t;

typedef struct thread_handler{
    uint32_t junk; //Bug Report: getting corrtpted ? 
    uint32_t id;
    char name[16];
    uint8_t priority;
    thread_t thread_fun;
    struct thread_handler * prev; 
    struct thread_handler * next;
    uint8_t state;
    
}thread_handler_t;


void print_tcb_list(void);
void thread_init(thread_handler_t *handler, uint32_t id, char *name, uint8_t priority, thread_t *thread_fun);
void thread_create(thread_handler_t *handler);
void thread_stop(thread_handler_t *handler);
void thread_np_scheduler(void);

#endif