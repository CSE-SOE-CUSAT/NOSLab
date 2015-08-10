#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
int main(int argc, char *argv[]){
    struct stat buffer;
    int s;
    if(argc==2){
        s=stat(argv[1],&buffer);
        if(s!=-1){
            printf("Owner id : %d \n",buffer.st_uid);
            printf("File mode : %o \n",buffer.st_mode);
            printf("Size of file :%llu bytes \n",(unsigned long long)buffer.st_size);
  
          printf("Last modification time: %s \n",ctime(&buffer.st_mtime));
	 printf("Last change time: %s \n",ctime(&buffer.st_ctime));	
	        }
    else
        printf("Number of command line options error");

    }    
    return 0;
}
