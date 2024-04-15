#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

#define ARRAY_SIZE 30

// Function to generate and sort array of size 30
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

// Function to merge two given arrays and store them in another array
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
    int id1, id2, id3, id4, fd1[2], fd2[2], fd3[2], fd4[2];
    int arr_a[ARRAY_SIZE], arr_b[ARRAY_SIZE], arr_c[ARRAY_SIZE], arr_d[2 * ARRAY_SIZE], arr_e[3 * ARRAY_SIZE];
    
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pipe(fd4);
    
    id1 = fork();
    
    if (id1 == -1) {
        printf("Error\n");
    } else if (id1 == 0) {
        id2 = fork();
        
        if (id2 == -1) {
            printf("Error\n");
        } else if (id2 == 0) {
            id3 = fork();
            
            if (id3 == -1) {
                printf("Error\n");
            } else if (id3 == 0) {
                id4 = fork();
                
                if (id4 == -1) {
                    printf("Error\n");
                } else if (id4 == 0) {
                    // Function A
                    generate_and_sort_array(arr_a);
                    printf("A\n");
                    close(fd1[0]);
                    write(fd1[1], &arr_a, ARRAY_SIZE * sizeof(int));
                    close(fd1[1]);
                } else {
                    // Function B
                    wait();
                    generate_and_sort_array(arr_b);
                    printf("B\n");
                    close(fd2[0]);
                    write(fd2[1], &arr_b, ARRAY_SIZE * sizeof(int));
                    close(fd2[1]);
                }
            } else {
                // Function C
                wait();
                generate_and_sort_array(arr_c);
                printf("C\n");
                close(fd3[0]);
                write(fd3[1], &arr_c, ARRAY_SIZE * sizeof(int));
                close(fd3[1]);
            }
        } else {
            // Function D
            wait();
            printf("D\n");
            close(fd1[1]);
            read(fd1[0], arr_a, ARRAY_SIZE * sizeof(int));
            close(fd1[1]);
            close(fd2[1]);
            read(fd2[0], arr_b, ARRAY_SIZE * sizeof(int));
            close(fd2[1]);
            merge_arrays(arr_a, arr_b, arr_d, ARRAY_SIZE, ARRAY_SIZE);
            close(fd4[0]);
            write(fd4[1], &arr_d, 2 * ARRAY_SIZE * sizeof(int));
            close(fd4[1]);
        }
    } else {
        // Function E
        wait();
        printf("E\n");
        close(fd3[1]);
        read(fd3[0], arr_c, ARRAY_SIZE * sizeof(int));
        close(fd3[1]);
        close(fd4[1]);
        read(fd4[0], arr_d, 2 * ARRAY_SIZE * sizeof(int));
        close(fd4[1]);
        merge_arrays(arr_c, arr_d, arr_e, ARRAY_SIZE, 2 * ARRAY_SIZE);
        
        for (int i = 0; i < 3 * ARRAY_SIZE; i++) {
            printf("Final E at index %d: %d\n", i, arr_e[i]);
        }
    }
    
    return 0;
}
