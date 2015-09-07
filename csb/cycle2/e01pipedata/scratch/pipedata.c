#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

        main()
        {
                int     fd[2];
                pid_t   childpid;

                pipe(fd);
        
                if((childpid = fork()) == -1)
                {
                        perror("fork");
                        exit(1);
                }

                if(childpid == 0)
                {
                        /* Child process closes up input side of pipe */
                        close(fd[0]);
                }
                else
                {
                        /* Parent process closes up output side of pipe */
                        close(fd[1]);
                }
                .
                .
        }
