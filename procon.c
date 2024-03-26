#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int fill = 0;
int use = 0;
int count = 0;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % BUFFER_SIZE;
    count++;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % BUFFER_SIZE;
    count--;
    return tmp;
}

pthread_mutex_t mutex;
int semaphore = 1;

void sem_wait() {
    pthread_mutex_lock(&mutex);
    while (semaphore <= 0) {
        pthread_mutex_unlock(&mutex);
        pthread_mutex_lock(&mutex);
    }
    semaphore--;
    pthread_mutex_unlock(&mutex);
}

void sem_signal() {
    pthread_mutex_lock(&mutex);
    semaphore++;
    pthread_mutex_unlock(&mutex);
}

void* producer(void* arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait();
        put(i);
        sem_signal();
        printf("Produced: %d\n", i);
    }
    return NULL;
}

void* consumer(void* arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sem_wait();
        int value = get();
        sem_signal();
        printf("Consumed: %d\n", value);
    }
    return NULL;
}

int main() {
    pthread_t producer_thread, consumer_thread;
    
    pthread_mutex_init(&mutex, NULL);
    
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
