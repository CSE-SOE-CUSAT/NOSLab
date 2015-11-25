#include<stdio.h>
#include<stdlib.h>
int main(int n,char *args[])
{
   char command[100]; 
   int ret; 
   if(n==3){
     sprintf(command,"cp %s %s",args[1],args[2]);
     ret=system(command);
     if(ret==0)
       printf("Successfully Copied from %s to %s\n",args[1],args[2]);
   }
   else
     printf("Invalid Command\n");
   return 0;
}
