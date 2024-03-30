#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include "mq.h"
int main(){


int id=fork();

if( id==0 ){
int mqid=msgget(1234,IPC_CREAT|0666);
MQ msg1;
int i,n,k;
printf("Enter number of students: ");
scanf("%d",&msg1.size);
printf("Enter their roll number:\n ");
for(i=0;i<msg1.size;i++){
scanf("%d",&k);
msg1.roll[i]=k;
}
msg1.mtype=5;
msgsnd(mqid,&msg1,DS,0);

msgrcv(mqid,&msg1,DS,8,0);

printf("\nsorted data: ");
for(i=0;i<msg1.size;i++){
  printf("%d  ",msg1.roll[i]);
}

}else{

int mqid=msgget(KEY,0666);
MQ msgp;
msgrcv(mqid,&msgp,DS,5,0);
int i,j,temp;
printf("Data recived by reciver: ");
for(i=0;i<msgp.size;i++){
  printf("%d  ",msgp.roll[i]);
}

for(i=0;i<msgp.size;i++){
	for(j=i+1;j<msgp.size;j++){
	  if( msgp.roll[i]>msgp.roll[j]){
	    temp=msgp.roll[j];
	    msgp.roll[j]=msgp.roll[i];
	    msgp.roll[i]=temp;
	  }
	}
}
msgp.mtype=8;
msgsnd(mqid,&msgp,DS,0);

}

return 0;
}
