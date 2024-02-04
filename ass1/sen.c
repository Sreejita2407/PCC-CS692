#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include "msgq.h"

void toBinary(int m, char* ch){
	int r,i=0;
	while(m!=0){
		r=m%2;
		ch[i++]=r+'0';
		m/=2;
	}
	ch[i]='\0';
	int s=0,e=i-1;
	while(s<e){
		char t=ch[s];
		ch[s]=ch[e];
		ch[e]=t;
		s++;
		e--;
		}
	}
		
int main(){
	int mqid;
	int n;
	mqid=msgget(1234,IPC_CREAT|0666);
	MQ msg1, msg2,msg3;
	msg1.mtype=1;
	msg2.mtype=2;
	msg3.mtype=3;
	printf("Enter a number: ");
	scanf("%d",&n);
	char ch[32], ch1[32],ch2[32];
	
	toBinary(n,ch);
	sprintf(ch1,"%o",n);
	sprintf(ch2,"%x",n);
	strcpy(msg1.mdata,ch);
	strcpy(msg2.mdata,ch1);
	strcpy(msg3.mdata,ch2);
	
	msgsnd(mqid,&msg1,dataSize,0);
	msgsnd(mqid,&msg2,dataSize,0);
	msgsnd(mqid,&msg3,dataSize,0);
	printf("Data Sent to Massage Queue....\n");
	}
