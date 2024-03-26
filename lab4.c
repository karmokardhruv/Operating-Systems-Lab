#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    int fd[2];
    char *args[] = {"./prime", NULL};

    pipe(fd);

    if (fork() == 0) 
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execvp(args[0], args);
    } 
    
    else 
    {
        char ch;
        int count = 0;
        close(fd[1]);
        wait();

        while (read(fd[0], &ch, 1) > 0) 
        {
            putchar(ch);
            //printf(" CH: %c\n",ch);
            if (ch == '\n') count++;
        }

        printf("The count of prime numbers between 1 and 100 is: %d\n", count);
        close(fd[0]);
    }

    return 0;
} 