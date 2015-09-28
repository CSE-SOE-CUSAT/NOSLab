#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
   int pid,a,n,p[2],i,vv;
   char str1[100][100],str2[100][100];
   
   printf("Number of strings:- ");
   scanf("%d",&n);
   a = pipe(p); //Unidirectional pipe
   if(a == -1)
   {
       fprintf(stderr, "Pipe Failed.\n");
       return EXIT_FAILURE;
    }
    pid = fork();
   switch(pid){
       case -1:perror("main: fork"); //error encountered
          exit(1);
       case 0: read(p[0],str2,sizeof(str2)); //read from pipe
          printf("In child process (ID: %d)\n", getpid());
          for(i=0;i<n;i++)
             printf("String %d:- %s\n",i+1,str2[i]);
          exit(1);
          break;
       default: printf("In parent process (ID: %d)\n", getpid());
          for(i=0;i<n;i++){
             printf("Enter the string %d:- ",i+1);
             scanf("%s",str1[i]);
          }
          write(p[1],str1,sizeof(str1)); //write to pipe
          waitpid(pid,NULL,0); //suspend parent process till the state of child process is changed
          break;
    }
    close(p[0]);
    close(p[1]);
    return 0;
}

