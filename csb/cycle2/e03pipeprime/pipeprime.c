#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int prime(int);
int main(){
    int pid,a,n,p[2],i,buffr1[100],buffr2[100];
    a = pipe(p);
    if(a == -1)
    {
       fprintf(stderr, "Pipe Failed.\n");
       return EXIT_FAILURE;
    }
    pid = fork();
    switch(pid){
       case -1:perror("main: fork");
          exit(1);
       case 0: n=read(p[0],buffr2,sizeof(buffr2));
          printf("In child process (ID: %d)\n",getpid());
          n=n/sizeof(int);
          for(i=0;i<n;i++){
             if(prime(buffr2[i]))
	     	printf("%d is prime\n",buffr2[i]);
		}
          exit(1);
          break;
       default: printf("In parent process (ID: %d)\n", getpid());
          printf("Number of elements:- ");
          scanf("%d",&n); 
	  printf("Enter the elements\n");
          for(i=0;i<n;i++){
             scanf("%d",&buffr1[i]);
          }
          write(p[1],buffr1,n*sizeof(int));
          waitpid(pid,NULL,0);
          break;
   }
   close(p[0]);
}
int prime(int n){
	int i;
	if(n==1)
		return 0;
	for(i=2;i<n; i++){
		if(n%i==0)
			return 0;
	}
	return 1;
	}
