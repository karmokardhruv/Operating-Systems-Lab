//Write a C program for the following:
//Using fixed partition memory allocation technique, simulate the following memory management techniques:
//a) First fit
//Input: No. of memory partitions, size of each partition, no. of processes, size of each process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main() {
    int n, m, i, j, k, temp, flag = 0;
    printf("Enter the number of memory partitions: ");
    scanf("%d", &n);
    char partitions[n];
    int partition_sizes[n];
    printf("Enter the status of each partition (F for free, A for allocated):\n");
    for (i = 0; i < n; i++) {
        scanf(" %c", &partitions[i]);
    }
    printf("Enter the size of each partition:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &partition_sizes[i]);
    }
    printf("Enter the number of processes: ");
    scanf("%d", &m);
    int processes[m];
    printf("Enter the size of each process:\n");
    for (i = 0; i < m; i++) {
        scanf("%d", &processes[i]);
    }
    for (i = 0; i < m; i++) {
        flag = 0;
        for (j = 0; j < n; j++) {
            if (partitions[j] == 'F' && processes[i] <= partition_sizes[j]) {
                printf("Process %d of size %d is allocated to partition %d of size %d\n", i + 1, processes[i], j + 1, partition_sizes[j]);
                partitions[j] = 'A';
                partition_sizes[j] -= processes[i];
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            printf("Process %d of size %d is not allocated\n", i + 1, processes[i]);
        }
    }
    return 0;
}