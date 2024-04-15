#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int pidA, pidB, pidC, pidD, pidE;

    pidA = fork();
    if (pidA == 0)
    {
        printf("Process A, my pid is %d, my parent pid is %d\n", getpid(), getppid());

        pidC = fork();
        if (pidC == 0)
        {
            printf("Process C, my pid is %d, my parent pid is %d\n", getpid(), getppid());
        }
        else
        {
            pidD = fork();
            if (pidD == 0)
            {
                printf("Process D, my pid is %d, my parent pid is %d\n", getpid(), getppid());
            }
        }
    }
    else
    {
        pidB = fork();
        if (pidB == 0)
        {
            printf("Process B, my pid is %d, my parent pid is %d\n", getpid(), getppid());

            pidE = fork();
            if (pidE == 0)
            {
                printf("Process E, my pid is %d, my parent pid is %d\n", getpid(), getppid());
            }
        }
    }

    return 0;
}
