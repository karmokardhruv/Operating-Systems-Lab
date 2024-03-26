#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int count = 5;
int flag[2] = {0,0};
int turn = 0;

void *inc_count(void *arg)
{
    flag[0] = 0;
    turn = 1;
    while(flag[1] == 1 && turn == 1);
    for (int i = 0; i < 5; i++)
    {
        count++;
    } 
}

void *dec_count(void *arg)
{
    flag[1] = 0;
    turn = 0;
    while(flag[0] == 1 && turn == 0);
    for (int i = 0; i < 5; i++)
    {
        count--;
    } 
}

int main()
{
    pthread_t tid1, tid2;
    pthread_create(&tid1, NULL, inc_count, NULL);
    pthread_create(&tid2, NULL, dec_count, NULL);
    sleep(2);
    printf("Count = %d\n", count);
    return 0;
}
