#include<stdio.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
   char cmd[50];
   int ret;
   if(argc==3){
     sprintf(cmd,"cp %s %s",argv[1],argv[2]);
     ret=system(cmd);
     if(ret==0)
       printf("Success Source: %s Destination: %s\n",argv[1],argv[2]);
   }
   else
     printf("Invalid Command\n");
   return 0;
}

