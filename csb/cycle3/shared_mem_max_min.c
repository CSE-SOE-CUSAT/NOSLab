#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   long shmid;
   key_t key;
   int *shm;
   int *s,shm_size,n,i,large,small;
   printf("Inside process %d\n",getpid());
   printf("\nSize limit:  ");
   scanf("%d",&n);
   shm_size=n*sizeof(long);
   key = IPC_PRIVATE;
   if ((shmid = shmget(key, shm_size, IPC_CREAT | 0666)) < 0) {
     perror("shmget");
     exit(1);
   }
   if ((shm = shmat(shmid, NULL, 0)) == (int *) -1) {
     perror("shmat");
     exit(1);
   }
   s = shm;
   printf("Enter %d numbers\n",n);
   for(i=0;i<n;i++,s++)
     scanf("%d",s);
   if(fork()==0){
     printf("Inside process %d\n",getpid());
     s=shm;
     large=*s;
     small=*s;
     for(i=1;i<n;i++){
       if(*(s+i)>large)
         large=*(s+i);
       else if(*(s+i)<small) small=*(s+i);
     }
   }
   else{
     wait(NULL);
     return 0;
   }
 //  printf("Inside process %d\n",getpid());
   printf("\nLargest= %d \nSmallest= %d\n",large,small);
   return 0;
}

