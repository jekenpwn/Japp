/*
 * hello_ipc.c
 *
 *  Created on: May 10, 2019
 *      Author: jeken
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "jpipe.h"

static volatile char flag =  1;
static int  count;

static pthread_t  thread_client,thread_server;


static char buf_s[124];
static char buf_c[124];
static int buf_size = 124;

void *
runnable_clinet(void *arg)
{
	while(1){
        if(flag == 1){
        	struct Jpipe_t *jp = (struct Jpipe_t *)arg;

        	sprintf(buf_c,"hello,count is %d \n",count);
        	if(jp->sent(jp->fd[1],buf_c,strlen(buf_c))>0){
        		printf("Client have sent: %s\n",buf_c);
        	}
        	count++;
        	flag = 0;
        }

	}
   return arg;
}
void *
runnable_server(void *arg)
{
	while(1){
		if(flag == 0){
			struct Jpipe_t *jp = (struct Jpipe_t *)arg;

			if(jp->recv(jp->fd[0],buf_s,buf_size)>0);
				printf("Server recv:%s\n",buf_s);
			flag=1;
		}
	}
	return arg;
}


static int
thread_create(pthread_t *pthd, void * (*runnable)(void*),void * arg)
{
	return pthread_create(pthd,NULL,runnable, arg);
}

static int
thread_join(pthread_t pthd)
{
	if(pthd != 0){
	   return pthread_join(pthd,NULL);
	}
	return -1;
}


int main()
{
	 struct Jpipe_t *jp = NULL;
	 jp = New_Jpipe();
     if(jp == NULL){
    	 printf("JP null \n");
     }
	 if (thread_create(&thread_client, runnable_clinet,(void*)jp) != 0){
		 printf("Client thread create failed!\n");
		 return -1;
	 }
	 if (thread_create(&thread_server,runnable_server,(void*)jp) != 0){
		 printf("Server thread create failed!\n");
		 return -1;
	 }

	 thread_join(thread_client);
	 thread_join(thread_server);

	 Delete_Jpipe(jp);

	 return 0;
}

