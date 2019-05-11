/*
 * jpipe.h
 *
 *  Created on: May 10, 2019
 *      Author: jeken
 */

#ifndef _JPIPE_H
#define _JPIPE_H

struct Jpipe_t{
	int   fd[2];
	int   (*recv)(int,void*,int);
	int   (*sent)(int,const void*,int);
};


int  revc_pipe(int fd, void *buf, int size);
int  sent_pipe(int fd, const void *buf, int size);

struct Jpipe_t* New_Jpipe();
void Delete_Jpipe(struct Jpipe_t *jp);



#endif /* PROC_IPC_JPIPE_H_ */
