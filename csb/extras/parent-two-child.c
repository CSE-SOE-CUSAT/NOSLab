#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
int main(){ 
   int pid1,pid2,i;
   if(pid1=fork()==0){
      for(i=30;i>=1;i=i-2)
         printf("Process B ------- %d\n",i);
      exit(1);
   }
   else{
      waitpid(pid1,NULL,0);
      for(i=2;i<=30;i=i+2)
         printf("Process A------- %d\n",i);
      if(pid2=fork()==0){
         for(i=1;i<=10;i++)
               printf("Process C------ %d * 4 = %d\n",i,i*4);
      exit(1);
   }
   waitpid(pid2,NULL,0);
   } 
   return 0; 
}
