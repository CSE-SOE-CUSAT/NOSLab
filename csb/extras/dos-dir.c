#include<stdio.h>
#include<dirent.h>
struct dirent *dptr;
int main(int argc, char *argv[]){
   DIR *dirp;
   dirp=opendir(argv[1]);
   if(dirp==NULL){
     printf("Error");
     exit(1);
   }
   while(dptr=readdir(dirp)){
     printf("%s\n",dptr->d_name);
   }
   closedir(dirp);
}
