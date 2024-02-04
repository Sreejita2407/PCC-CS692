#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include "msgq.h"

int main(){
	int mqid=msgget(1234,IPC_CREAT|0666);
	MQ msg1;
	msgrcv(mqid,&msg1,dataSize,1,0);
	printf("Data received from Message queue :%s\n",msg1.mdata);
}
