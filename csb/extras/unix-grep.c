#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int printLine(int,int);
int cmpStr(int,int,char[]);
int main(int argc, char *argv[]){
   int fd,count=0,len,line=0;
   char buffer,flag='y';
   fd = open(argv[2],O_RDWR);
   if(fd!=-1){
     len=lseek(fd,0L,2);
     while(lseek(fd,count,0)<len){
       count++;
       read(fd,&buffer,sizeof(char));
       if(argv[1][0]==(char)buffer){
         if(cmpStr(fd,count,argv[1])){
           count=printLine(fd,line);
           line=count;
         }
       }
       else if((char)buffer=='\n')
         line=count;
     }

   }
   else
     printf("\nFile not found\n");
   close(fd);
   return 0;
}
int printLine(int fd,int start){
   char bfr;
   int len;
   len=lseek(fd,0L,2);
   while(lseek(fd,start,0)<len){
     start++;
     read(fd,&bfr,sizeof(char));
     printf("%c",(char)bfr);
     if((char)bfr=='\n')
       return start;
  }
  exit(1);
}
int cmpStr(int fd,int start,char str[]){
   char bfr;
   int len,i;
   len=lseek(fd,0L,2);
  for(i=1;i<strlen(str);i++){
     if(lseek(fd,start,0)<len){
       start++;
       read(fd,&bfr,sizeof(char));
       if((char)bfr!=str[i])
         return 0;
     }
     else
       exit(1); 
  }
   return 1;
}
