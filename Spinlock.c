#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

int count = 5;
bool lock = false;

bool TestAndSet(bool *target) {
    bool rv = *target;
    *target = true;
    return rv;
}

void* inc(void* n)
{
    while (TestAndSet(&lock));

    for (int i = 1; i <= 2000; i++)
    {
        count++;
    }

    lock = false;
    pthread_exit(n);
}

void* dec(void* n)
{
    while (TestAndSet(&lock));

    for (int i = 1; i <= 2000; i++)
    {
        count--;
    }

    lock = false;
    pthread_exit(n);
}

int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, inc, NULL);
    pthread_create(&t2, NULL, dec, NULL);

    sleep(2);

    printf("Count: %d\n", count);

    return 0;
}
