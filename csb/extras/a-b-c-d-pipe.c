#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main(){
   int pid1,pid2,pid3,pid4;
   int p1[2],p2[2];
   char bufr[30],rev[30];
   int countL=0,countU=0,i=-1,j=0,countV=0,len;
   pipe(p1);
   pipe(p2);
   if(pid1=fork()==0){

      if(pid2=fork()==0){ 
         read(p2[0],bufr,sizeof(bufr));
         len=strlen(bufr);
         for(i=len-1,j=0;j<len;i--,j++)
            rev[j]=bufr[i];
         rev[j]='\0';
         printf("Proccess D---- Reverse = %s \n",rev);
         exit(1);
      }
      else{
         read(p1[0],bufr,sizeof(bufr)); 
         write(p2[1],bufr,sizeof(bufr));
         if(pid3=fork()==0){
            printf("Poccess C--- ID of B = %d and ID of C = %d \n",getppid(),getpid());
         exit(1);
      }
      else{
         while(bufr[++i]!='\0')
            if(bufr[i]>='A' && bufr[i]<='Z')
               countU++;
         i=-1;
         while(bufr[++i]!='\0')
            if(bufr[i]>='a' && bufr[i]<='z')
               countL++;
         printf("Poccess B--- No of UpperCase letters = %d \n",countU);
         printf("Poccess B--- No of LowerCase letters = %d \n",countL);
         waitpid(pid2,NULL,0);
         waitpid(pid3,NULL,0);
      }
   }
   exit(1);
   }
   else{
      printf("Poccess A--- Enter a sentence ");
      gets(bufr);
      write(p1[1],bufr,sizeof(bufr));
      while(bufr[++i]!='\0')
         if(bufr[i]=='a' || bufr[i]=='e' || bufr[i]=='i' || bufr[i]=='o' || bufr[i]=='u' ||
            bufr[i]=='A' || bufr[i]=='E' || bufr[i]=='I' || bufr[i]=='O' || bufr[i]=='U' )
            countV++;
      printf("Poccess A--- No of Vowels = %d \n",countV);
      waitpid(pid1,NULL,0);
   }
   close(p1[0]);
   close(p1[1]);
   return 0;
}

