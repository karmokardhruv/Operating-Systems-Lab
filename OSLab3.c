#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>

#define ARRAY_SIZE 30
void generate_and_sort_array(int array[ARRAY_SIZE]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100 + 1;
    }
    for (int i = 0; i < ARRAY_SIZE - 1; i++) {
        for (int j = 0; j < ARRAY_SIZE - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void merge_arrays(int arr1[], int arr2[], int result[], int size1, int size2) {
    int i = 0, j = 0, k = 0;
    while (i < size1 && j < size2) {
        if (arr1[i] <= arr2[j]) {
            result[k++] = arr1[i++];
        } else {
            result[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        result[k++] = arr1[i++];
    }
    while (j < size2) {
        result[k++] = arr2[j++];
    }
}

int main() {
    int fd1[2], fd2[2], fd3[2], fd4[2];
    int arr_a[ARRAY_SIZE], arr_b[ARRAY_SIZE], arr_c[ARRAY_SIZE], arr_d[2*ARRAY_SIZE], arr_e[3*ARRAY_SIZE];
    pid_t pid;
    
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pipe(fd4);
    
    pid = fork(); // Process A
    if (pid == 0) {
        generate_and_sort_array(arr_a);
        printf("A\n");
        close(fd1[0]);
        write(fd1[1], arr_a, ARRAY_SIZE*sizeof(int));
        close(fd1[1]);
        exit(0);
    } else {
        wait(NULL);
    }

    pid = fork(); // Process B
    if (pid == 0) {
        generate_and_sort_array(arr_b);
        printf("B\n");
        close(fd2[0]);
        write(fd2[1], arr_b, ARRAY_SIZE*sizeof(int));
        close(fd2[1]);
        exit(0);
    } else {
        wait(NULL);
    }

    pid = fork(); // Process C
    if (pid == 0) {
        generate_and_sort_array(arr_c);
        printf("C\n");
        close(fd3[0]);
        write(fd3[1], arr_c, ARRAY_SIZE*sizeof(int));
        close(fd3[1]);
        exit(0);
    } else {
        wait(NULL);
    }

    pid = fork(); // Process D
       if (pid == 0) {
        printf("D\n");
        close(fd1[1]);
        read(fd1[0], arr_a, ARRAY_SIZE*sizeof(int));
        close(fd1[0]);
        close(fd2[1]);
        read(fd2[0], arr_b, ARRAY_SIZE*sizeof(int));
        close(fd2[0]);
        merge_arrays(arr_a, arr_b, arr_d, ARRAY_SIZE, ARRAY_SIZE);
        close(fd4[0]);
        write(fd4[1], arr_d, 2*ARRAY_SIZE*sizeof(int));
        close(fd4[1]);
        exit(0);
    } else {
        wait(NULL);
    }

    pid = fork(); // Process E
    if (pid == 0) {
        printf("E\n");
        close(fd3[1]);
        read(fd3[0], arr_c, ARRAY_SIZE*sizeof(int));
        close(fd3[0]);
        close(fd4[1]);
        read(fd4[0], arr_d, 2*ARRAY_SIZE*sizeof(int));
        close(fd4[0]);
        merge_arrays(arr_c, arr_d, arr_e, ARRAY_SIZE, 2*ARRAY_SIZE);
        for (int i = 0; i < 3*ARRAY_SIZE; i++) {
            printf("Sorted Order: %d\n", i, arr_e[i]);
        }
        exit(0);
    } else {
        wait(NULL);
    }
    pid = fork();
    if (pid == 0) {
        exit(0);
    } else {
        wait(NULL);
    }
    return 0;
}
