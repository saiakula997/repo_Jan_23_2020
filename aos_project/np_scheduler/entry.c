
#include "utils.h"
#include "thread.h"

void thread_fun(struct thread_handler *handler){
    print("Running: %s Priority: %d \n", handler->name, handler->priority);
    delay(TICKS_S(1)); 
}

int entry(void){   
        print("Hello, world!\n");
        delay( TICKS_S(1) );
        
        thread_handler_t thread1;
        memset(&thread1, 0, sizeof(thread_handler_t));
        thread_init(&thread1, 1, "THREAD_1", 8, thread_fun);
        thread_create(&thread1);

        thread_handler_t thread2;
        memset(&thread2, 0, sizeof(thread_handler_t));
        thread_init(&thread2, 2, "THREAD_2", 5, thread_fun);
        thread_create(&thread2);
        

        thread_handler_t thread3;
        memset(&thread3, 0, sizeof(thread_handler_t));
        thread_init(&thread3, 3, "THREAD_3", 6, thread_fun);
        thread_create(&thread3);   
        

        thread_handler_t thread4;
        memset(&thread4, 0, sizeof(thread_handler_t));
        thread_init(&thread4, 4, "THREAD_4", 8, thread_fun);
        thread_create(&thread4);  

        print_tcb_list();

        thread_np_scheduler();

    return 0;
}