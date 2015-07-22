   #include <unistd.h>
   #include <fcntl.h>
   #include <sys/stat.h>
   #include <stdio.h>
   #include <string.h>
   int main(int argc, char* argv[]){
      int fd,fd2,count=-1;
      char buffer,flag='y';
      fd = open(argv[1],O_RDWR);
      if(fd!=-1){
          fd2 = open(argv[2],O_RDWR);
          if(fd2!=-1){
             printf("\n file present, 'y' to override: ");
             flag=getchar();
         }
         if(flag=='y'){
            fd2 = creat(argv[2],O_RDWR|0666);
            while(lseek(fd,count,SEEK_END)!=-1){
                count--;
                read(fd,&buffer,sizeof(char));
                write(fd2,&buffer,sizeof(char));
            }
         }
      }
      else
          printf("\nSource file not found error");
      close(fd);
 return 0;
   }

