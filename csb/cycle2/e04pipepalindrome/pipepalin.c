#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
  int pid,a,n,p[2],p2[2],i,len,j,k,flag,n2=0;
  char str1[100][100],str2[100][100];
  printf("Number of elements:- ");
  scanf("%d",&n);
  a = pipe(p);
  if(a == -1)
  {
     fprintf(stderr, "Pipe Failed.\n");
     exit(1);
  }
  a = pipe(p2);
   if(a == -1)
   {
     fprintf(stderr, "Pipe Failed.\n");
     exit(1);
  }
   pid = fork();
   switch(pid){
     case -1:perror("main: fork");
       exit(1);
     case 0: read(p[0],str2,sizeof(str2));
       printf("In child process (ID: %d)\n", getpid());
       for(i=0;i<n;i++){
         len=strlen(str2[i]);
         flag=0;
	printf("checking %s >\t",str2[i]);
        for(j=0,k=len-1;j<len;j++,k--){
           if(str2[i][j]!=str2[i][k]){
             flag=1;
		break;
           }
         }
	if(flag==1){
	printf("%s is not a palindrome\n",str2[i]);
	}
	else{
	printf("%s is a palindrom\n",str2[i]);		
	}
		
	} break;
	default: printf("In parent process (ID: %d)\n", getpid());
		  printf("Enter elements\n");
		  for(i=0;i<n;i++){
		  scanf("%s",str1[i]);
		  }
		  write(p[1],str1,sizeof(str1));
		  waitpid(pid,NULL,0);
		  break;

	}
	close(p[0]);
}
