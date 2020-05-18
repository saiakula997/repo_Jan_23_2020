#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
void node1_handler(int signum);
void node2_handler(int signum);
void node3_handler(int signum);
void node4_handler(int signum);
void node5_handler(int signum);
int search_next_node(int id);

struct meta_buffer
{
	int  Img[100];
	struct meta_buffer *next_ptr;
};

#define  TRACE(); printf("In %s() at %d \n",__func__,__LINE__);
