#include  "handlers.h"


extern int *shmdata;
extern struct meta_buffer *shm_meta_buffer;


int search_next_node(int id)
{
	for(int i=0;i<5-1;i++)
	{
		if(*(shmdata+i)==id)
			return *(shmdata+i+1);
	}
	return 0;
}

void node1_handler(int signum)
{

	static int n_times=0;
	static int next_node_pid=0;
	int i;

	if(0==next_node_pid)
	{
		next_node_pid=search_next_node(getpid());
		printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
		n_times++;
		return ;
	}
	printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);

	//for(int i=0;i<100;i++)
	//	(shm_meta_buffer+n_times-1)->Img[i]=5+n_times;
	//(shm_meta_buffer+n_times-1)->next_ptr=(shm_meta_buffer+n_times);

	for(i=0;i<100;i++)
	{

		(shm_meta_buffer+n_times-1)->Img[i]=100+n_times;
	}
	shm_meta_buffer->next_ptr=shm_meta_buffer+n_times;
	printf("sending signal to %d \n",next_node_pid);
	if(next_node_pid)kill(next_node_pid,SIGRTMIN+3);
	n_times++;
}

void node2_handler(int signum)
{

	static int n_times=0;
	static int next_node_pid=0;

	if(0==next_node_pid)
	{
		next_node_pid=search_next_node(getpid());
		printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
		n_times++;
		return ;
	}

	printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);

	printf("Image=%d \n",(shm_meta_buffer+n_times-1)->Img[0]);

	//if(next_node_pid)kill(next_node_pid,SIGRTMIN+3);
	n_times++;
}


void node3_handler(int signum)
{

	static int n_times=0;
	static int next_node_pid=0;

	if(0==next_node_pid)
	{
		next_node_pid=search_next_node(getpid());
		printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
		n_times++;
		return ;
	}

	printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
	if(next_node_pid)kill(next_node_pid,SIGRTMIN+3);
	n_times++;
}

void node4_handler(int signum)
{

	static int n_times=0;
	static int next_node_pid=0;

	if(0==next_node_pid)
	{
		next_node_pid=search_next_node(getpid());
		printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
		n_times++;
		return ;
	}

	printf("my pid %d next node pid  %d times %d\n",getpid(),next_node_pid,n_times);
	if(next_node_pid)kill(next_node_pid,SIGRTMIN+3);
	n_times++;
}

void node5_handler(int signum)
{

	static int n_times=0;
	static int next_node_pid=0;

	if(0==next_node_pid)
	{
		next_node_pid=search_next_node(getpid());
		printf("my pid %d next node pid %d last node times %d\n",getpid(),next_node_pid,n_times);
		n_times++;
		return ;
	}

	printf("my pid %d next node pid %d last node times %d\n",getpid(),next_node_pid,n_times);
	if(next_node_pid)kill(next_node_pid,SIGRTMIN+3);
	n_times++;
}
