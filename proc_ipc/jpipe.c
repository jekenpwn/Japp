/*
 * jpipe.c
 *
 *  Created on: May 10, 2019
 *      Author: jeken
 */

#include "jpipe.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int
revc_pipe(int fd, void *buf, int size)
{

	return read(fd,buf,size);
}

int
sent_pipe(int fd, const void *buf, int size)
{

	return write(fd, buf,size);
}

struct Jpipe_t*
New_Jpipe()
{
	struct Jpipe_t *jp;
	int fd[2] = {0};

	jp = malloc(sizeof(struct Jpipe_t));
	if (NULL == jp){
		printf("Jpipe: malloc memory failed!\n");
		return NULL;
	}

	if(pipe(fd) == -1){
		printf("Jpipe: pipe create failed!\n");
		return NULL;
	}

	memset(jp,0,sizeof(struct Jpipe_t));
	jp->fd[0] = fd[0];
	jp->fd[1] = fd[1];
	jp->recv = revc_pipe;
	jp->sent = sent_pipe;

	return jp;
}

void
Delete_Jpipe(struct Jpipe_t *jp)
{
	if(NULL != jp){
		if(jp->fd[0] != 0){
			close(jp->fd[0]);
		}
		if(jp->fd[1] != 0){
			close(jp->fd[1]);
		}
		free(jp);
	}
}



