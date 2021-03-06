
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
   long shmid,shm_size;
   key_t key;
   char *shm,*s;
   int n,i;
   printf("Inside process %d\n",getpid());    
   printf("\nNumber of names :- ");
   scanf("%d",&n);
   shm_size=n*30*sizeof(char);// size limit for names is 30
   key = IPC_PRIVATE;
   if ((shmid = shmget(key, shm_size, IPC_CREAT | 0666)) < 0) {
   perror("shmget");
   exit(1);
   }
   if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) {
   perror("shmat");
   exit(1);
   }
   s = shm;
   printf("Enter names\n");
   for(i=0;i<n;i++,s=s+20)
   scanf("%s",s);
   if(fork()==0){
     printf("Inside process %d\n",getpid());
     s=shm;
     int j,temp;
     char t[20];
     for(i=0;i<n-1;i++){
       temp=i;
         for(j=i+1;j<n;j++)
           if(strcmp(s+(20*temp),s+(20*j))>0)  temp=j;
       strcpy(t,s+(20*i));
       strcpy(s+(20*i),s+(20*temp));
       strcpy(s+(20*temp),t);
     }
   }
   else{
     wait(NULL);
     return 0;
   }
   s=shm;
   printf("Alphabetical Order\n");
   for(i=0;i<n;i++,s=s+20)
     printf("%s\n",s);
   return 0;
}

