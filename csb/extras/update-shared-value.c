#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>
#define MUTEX 0
void up(int sem_id,int sem_num,struct sembuf *semaphore){
   semaphore->sem_num=sem_num;
   semaphore->sem_op=1;
   semaphore->sem_flg=0;
   semop(sem_id,semaphore,1);
}
void down(int sem_id,int sem_num,struct sembuf *semaphore){
   semaphore->sem_num=sem_num;
   semaphore->sem_op=-1;
   semaphore->sem_flg=0;
   semop(sem_id,semaphore,1);
}
void initsem(int sem_id,int sem_num,int val){
   union semnum{
     int val;
     struct semid_ds *buf;
     unsigned short *array;
   }argument;
   argument.val=val;
   semctl(sem_id,sem_num,SETVAL,argument);
}
int main(){
   key_t shm_key=32233,sem_key=45565;
   int shm_id,sem_id,pid;
   int *shm;
   struct sembuf semaphore;
   shm_id=shmget(shm_key,2,IPC_CREAT|0666);
   sem_id=semget(sem_key,1,IPC_CREAT|0666);
   shm=shmat(shm_id,NULL,0);
   printf("\nEnter the initial number ");
   scanf("%d",&shm[0]);
   shm[1]=0;
   initsem(sem_id,MUTEX,1);
   pid=fork();
   if(pid==0){
     while(shm[1]<10){
     int item,i;
     sleep(2);
     down(sem_id,MUTEX,&semaphore);
     if(shm[1]<10){
       shm[0]+=2;
       shm[1]++;
       printf("Incremented by 2\n");
     }
     up(sem_id,MUTEX,&semaphore);
   }
   exit(0);
  }
   else{
      while(shm[1]<10){
     sleep(1);
     down(sem_id,MUTEX,&semaphore);
     if(shm[1]<10){
       shm[0]-=4;
       shm[1]++;
       printf("Decremented by 4\n");
     }
     up(sem_id,MUTEX,&semaphore);
   }
   waitpid(pid,NULL,0);
   printf("\nResult:- %d\n",shm[0]);
   exit(0);

   }
}
