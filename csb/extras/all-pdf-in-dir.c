#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <dirent.h>
#include <string.h>
struct dirent *dptr;
int main(int argc, char *argv[]){ 
   int pid,a,p[2],i=0,j,n,f; 
   char buffr1[100][100],buffr2[100][100],t[20];
   DIR *dirp;
   a = pipe(p);
   if(a == -1) 
   { 
     printf("Pipe Failed.\n"); 
     return 0; 
   } 
   pid = fork(); 
   switch(pid){ 
     case -1:perror("main: fork"); 
     exit(1); 
     case 0: read(p[0],buffr2,sizeof(buffr2));
     n=(int) buffr2[0][0];
     for(i=0;i<n;i++){
       j=0;
       while(buffr2[i][j]!='\0'){
       f=0;
       while(buffr2[i][j+f]==argv[1][f] && argv[1][f]!='\0')
         f++;
       if(f==strlen(argv[1])){
         printf("%s\n",buffr2[i]);
         break;
       }
       j++;
     }
     }
      exit(1);
     break;
     default: 
     dirp=opendir(".");
     if(dirp==NULL){
       printf("Error");
       exit(1);
     }
     while(dptr=readdir(dirp))
       strcpy(buffr1[++i],dptr->d_name);
     closedir(dirp);
     //Sorting
     n=i;
     for(i=1;i<n;i++){
       for(j=0;j<n-i;j++){
         if(strcmp(buffr1[j],buffr1[j+1])>0){
           strcpy(t,buffr1[j]);
           strcpy(buffr1[j],buffr1[j+1]);
           strcpy(buffr1[j+1],t);
         }
       }
     } 
     buffr1[0][0]=i;
     write(p[1],buffr1,sizeof(buffr1));
     waitpid(pid,NULL,0);
     break;
   } 
   close(p[0]);
   close(p[1]);
   return 0; 
}
