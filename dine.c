#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define LEFT (i + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT (i + 1) % NUM_PHILOSOPHERS

int forks[NUM_PHILOSOPHERS];
pthread_mutex_t waiter;
int running = 1;  

void semaphore_wait(int* semaphore) {
    pthread_mutex_lock(&waiter);
    while (*semaphore <= 0) {
        pthread_mutex_unlock(&waiter);
        pthread_mutex_lock(&waiter);
    }
    (*semaphore)--;
    pthread_mutex_unlock(&waiter);
}

void semaphore_signal(int* semaphore) {
    pthread_mutex_lock(&waiter);
    (*semaphore)++;
    pthread_mutex_unlock(&waiter);
}

void* philosopher(void* arg) {
    int i = *(int*)arg;
    
    while (running) {
        printf("Philosopher %d is thinking\n", i);
        sleep(1);
        
        semaphore_wait(&waiter);
        
        semaphore_wait(&forks[LEFT]);
        semaphore_wait(&forks[RIGHT]);
        
        printf("Philosopher %d is eating\n", i);
        sleep(1);
        
        semaphore_signal(&forks[LEFT]);
        semaphore_signal(&forks[RIGHT]);
        
        semaphore_signal(&waiter);
    }
    
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        forks[i] = 1;
    }
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }
    
    sleep(5);
    
    running = 0;
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }
    
    return 0;
}
