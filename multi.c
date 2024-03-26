#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int n, i, j;

void *sort_integers(void *arg) {
    int *arr = (int *)arg;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            int temp;
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void *sort_alphabets(void *arg) {
    char *arr = (char *)arg;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            char temp;
            if (strcmp(&arr[j], &arr[j + 1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    printf("Enter the number of integers: ");
    scanf("%d", &n);

    int arr1[n];

    printf("Enter the integers:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter the number of alphabets: ");
    scanf("%d", &n);

    char arr2[n];

    printf("Enter the alphabets:\n");
    for (i = 0; i < n; i++) {
        scanf(" %c", &arr2[i]);
    }

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, sort_integers, arr1);
    pthread_create(&thread2, NULL, sort_alphabets, arr2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Sorted array of integers:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\nSorted array of alphabets:\n");
    for (i = 0; i < n; i++) {
        printf("%c ", arr2[i]);
    }
    printf("\n");

    return 0;
}



