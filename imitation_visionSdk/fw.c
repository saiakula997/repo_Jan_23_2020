#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<error.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include<string.h>
#include <sys/types.h>

#include "handlers.h"


struct meta_buffer *shm_meta_buffer;
int *shmdata;

void *handlers[10]={node1_handler,node2_handler,node4_handler,node4_handler,node5_handler};



void init_all_process(void);

void init_all_process(void)
{
	printf("In %s() at %d \n",__func__,__LINE__);
	for(int i =0;i<5 ;i++)
		kill(shmdata[i],SIGRTMIN+3);
}

void interrupt_handler(int signum)
{
	printf("In %s() at %d \n",__func__,__LINE__);
	// detaching the shared memory of meta_buffer
	if(-1==shmdt(shm_meta_buffer))perror("shmdt");

	kill(getpid(),SIGKILL);
}

int main()
{

	int i,n=0;
	int nodes[10]={0};

	//creating shared memory for buffer nodes and pid's
	key_t key = ftok("./for_ftok.txt",65);
	if(-1 == key)
	{
		perror("ftok");
		TRACE();
		exit(0);
	}
	int shmid1 = shmget(key,(1024),0666|IPC_CREAT);
	if(-1 == shmid1)
	{
		perror("shmget");
		TRACE();
		exit(0);
	}

	shmdata = (int *)shmat(shmid1,(void*)0,0);
	if((void*)-1==shmdata)
	{
		perror("shmget");
		TRACE();
		exit(0);
	}

	// Creating shared memory for meta buffer
	key = ftok("./for_ftok.txt",66);
	if(-1==key)
	{
		perror("ftok");
		TRACE();
		exit(0);
	}
	int shmid2 = shmget(key,(1024*1024*100),0666|IPC_CREAT);
	if(shmid2==-1)
	{
		perror("shmget");
		TRACE();
		exit(0);
	}
	shm_meta_buffer = (struct meta_buffer *)shmat(shmid2,(void*)0,0);
	if((void *)-1 == shm_meta_buffer)
	{
		perror("shmat");
		TRACE();
		exit(0);
	}

	// creating new process
	for(i=0;i<5;i++)
	{
		signal(SIGRTMIN+3,handlers[i]);
		n=fork();
		if(n==0)while(1)pause();///child in pause state
		printf("Created node  %d  with pid %d\n",i,n);
		*(shmdata+i)=n;
		nodes[i]=n;

	}

	//initializing the processes (giving next_node_pid)
	init_all_process();

	// detaching the shared memory
	if(-1==shmdt(shmdata))perror("shmdt");
	if(-1==shmctl(shmid1,IPC_RMID,NULL))perror("shmctl");




	sleep(1);
	printf("sending signal to %d \n",nodes[0]);
	kill(nodes[0],SIGRTMIN+3);
	sleep(5);
	kill(nodes[0],SIGRTMIN+3);
	signal(SIGINT,interrupt_handler);
	// waiting state
	while(1)pause();



}
