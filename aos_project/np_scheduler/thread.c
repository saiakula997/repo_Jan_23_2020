#include "utils.h"
#include "thread.h"

static thread_handler_t * _tcb_list_head = NULL;
static uint32_t _total_thread_count=0;

void print_tcb_list(void){
    thread_handler_t *node = _tcb_list_head;
    print("\n----------------- TCB -----------------\n");
    while(node){
        print("ID: %u  NAME: %s  PRIORITY : %u \n", node->id, node->name, node->priority);
        node = node->next;
    }
    print("---------------------------------------\n");
}


void thread_init(thread_handler_t *handler, uint32_t id, char *name, uint8_t priority, thread_t *thread_fun){
    strncpy(handler->name, name, strlen(name));
    handler->id = id;
    handler->priority = priority;
    handler->thread_fun = thread_fun;
    handler->state = READY;
    print("New: -> ID: %u  NAME: %s  PRIORITY : %u \n", handler->id, handler->name, handler->priority);
}


void thread_create(thread_handler_t *handler){
    thread_handler_t *tmp = NULL;
    if(handler){
        _total_thread_count++;
        if (_tcb_list_head == NULL){
            _tcb_list_head = handler;
            return;
        }
        thread_handler_t *node = _tcb_list_head; 
        while(node) {
            if (handler->priority > node->priority){
                if(node->prev==NULL){
                    _tcb_list_head = handler;
                } else {
                    node->prev->next = handler;
                }
                handler->prev = node->prev;
                handler->next = node;
                node->prev = handler;
                return; 
            }
            tmp = node;
            node = node->next;
        }
        tmp->next = handler;
        handler->prev = tmp;
        return;
    }
}

void thread_stop(thread_handler_t *handler){
    handler->state = STOP;
}
void thread_np_scheduler(void){
    print("---------------- START OF SCHEDULER ------------ \n");
    thread_handler_t *node = _tcb_list_head;
    while (node){
        if(node->state == READY){
            node->state = RUN;
            node->thread_fun(node);
            node->state=STOP;
            node = _tcb_list_head;
            continue;
        } 
        node = node->next;
    }
    print("---------------- END OF SCHEDULER ------------ \n");
    // panic();
}