#include<sys/types.h>
#include<sys/stat.h>
#include<pwd.h>
#include<time.h>
#include<stdio.h>
int main(){
   int s;
   char source[30],flag='y';
    struct stat filestat;
    struct passwd *pwd;
    printf("\nEnter the file name:- ");
    gets(source);
    s=stat(source,&filestat);
    if(s!=-1){
       printf("\nOwner id:- %d",filestat.st_uid);
       if((pwd = getpwuid(filestat.st_uid)) != NULL)
          printf("\tname:- %s", pwd->pw_name);
       printf("\nFile Size :- %d bytes",filestat.st_size);
       printf("\nPermission :- %o",filestat.st_mode);
       printf("\nDate of creation :- %s",ctime(&filestat.st_ctime));
       printf("\nLast Modified Date :- %s",ctime(&filestat.st_mtime));
    }
   else
       printf("\nError!!!!");
    return 0;
}

