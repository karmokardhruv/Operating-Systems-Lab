#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    // Initialising
    int id, fd[2];
    pipe(fd);
    id = fork();
    
    // Error
    if (id == -1)
    {
        printf("Error!\n");
    }
    // Child
    else if (id == 0)
    {
        // Using the exec system call to run the helper.c executable file
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        execlp("./helper", "./helper", NULL);
    }
    // Parent
    else
    {
        // Wait for child to finish executing
        wait();
        
        // Initialising
        char ch;
        int count = 0;
        
        // Counting the number of prime numbers
        close(fd[1]);
        while (read(fd[0], &ch, 1) > 0)
        {
            putchar(ch);
            if (ch == '\n') count++;
        }
        close(fd[0]);
        
        // Printing the result
        printf("The count of prime numbers between 1 and 100 is: %d\n", count);
    }
    
    return 0;
}

HELPER FILE

#include <stdio.h>

// Function To Check Whether A Number Is Prime
int prime(int n)
{
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    // Finding The Prime Numbers And Printing
    for (int i = 1; i <= 100; i++)
    {
        if (prime(i))
        {
            printf("%d\n", i);
        }
    }
    
    return 0;
}
