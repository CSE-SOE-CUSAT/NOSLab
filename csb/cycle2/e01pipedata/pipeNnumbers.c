#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    int childpid,a,n,pd[2],i,buffer1[50],buffer2[50];
    a = pipe(pd);
    if(a == -1)
    {
       fprintf(stderr, "Pipe creation Failed.\n");
       exit(1);
    }
childpid = fork();
//printf("PID %d\n:",getpid());
    switch(childpid){
       case -1:perror("Error creating child");
          exit(1);
       case 0: n=read(pd[0],buffer2,sizeof(buffer2));
          printf("Inside child, pid: %d\n", getpid());
          n=n/sizeof(int);
	  printf("Numbers recieved are :- \n");
          for(i=0;i<n;i++)
             printf("%d\n",buffer2[i]);
          exit(0);
          break;
       default: printf("Inside parent, pid: %d\n", getpid());
          printf("No of input? :\t");
          scanf("%d",&n);
	  printf("Enter elements 1 by 1 \n");
          for(i=0;i<n;i++){
             scanf("%d",&buffer1[i]);
          }
          write(pd[1],buffer1,n*sizeof(int));
//          printf("pid1 %d \n",getpid());
	  waitpid(childpid,NULL,0);
          break;
   }
   close(pd[0]);
    close(pd[1]);
    return 0;
}

