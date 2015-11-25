#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
int main(){
   int shmid,shm_size=30,*shmInt,pid1,i=-1,count1=0,count2=0;
   int pid2,pid3,len,j;
   char *shm,*temp,rev[30];
   key_t key=4546,key2=6788;
   shmid=shmget(key,shm_size,IPC_CREAT | 0666);
   shm=shmat(shmid,NULL,0);
   shmid=shmget(key2,1,IPC_CREAT | 0666);
   shmInt=shmat(shmid,NULL,0);
   *shmInt=0;
   if(pid1=fork()==0){
     while(*shmInt==0);
     temp=shm;
     if(pid2=fork()==0){ 
       len=strlen(temp);
       for(i=len-1,j=0;j<len;i--,j++)
         rev[j]=*(temp+i);
       rev[j]='\0';
       printf("Proccess D---- Reverse = %s \n",rev);
       exit(1);
     }
     else{
       if(pid3=fork()==0){
         printf("Poccess C--- ID of B = %d and ID of C = %d \n",getppid(),getpid());
         exit(1);
     }
     else{
       while(*(temp+(++i))!='\0')
         if(*(temp+i)>='A' && *(temp+i)<='Z')
           count1++;
       i=-1;
       while(*(temp+(++i))!='\0')
         if(*(temp+i)>='a' && *(temp+i)<='z')
           count2++;
       printf("Poccess B--- No of UpperCase letters = %d \n",count1);
       printf("Poccess B--- No of LowerCase letters = %d \n",count2);
       waitpid(pid2,NULL,0);
       waitpid(pid3,NULL,0);
     }
   }
   exit(1);
   }
   else{
   printf("Enter a sentence ");
   gets(shm);
   *shmInt=1;
   temp=shm;
   while(*(temp+(++i))!='\0')
     if(*(temp+i)=='a' || *(temp+i)=='e' || *(temp+i)=='i' || *(temp+i)=='o' || *(temp+i)=='u' ||
       *(temp+i)=='A' || *(temp+i)=='E' || *(temp+i)=='I' || *(temp+i)=='O' || *(temp+i)=='U' )
         count1++; 
     printf("Poccess A--- No of Vowels = %d \n",count1);
     waitpid(pid1,NULL,0);
   }

   return 0;
}
