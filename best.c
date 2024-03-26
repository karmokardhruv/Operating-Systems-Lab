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
        int best_fit_index = -1;
        int best_fit_size = -1;
        for (j = 0; j < n; j++) {
            if (partitions[j] == 'F' && processes[i] <= partition_sizes[j]) {
                if (best_fit_index == -1 || partition_sizes[j] - processes[i] < best_fit_size) {
                    best_fit_size = partition_sizes[j] - processes[i];
                    best_fit_index = j;
                }
            }
        }
        if (best_fit_index != -1) {
            printf("Process %d of size %d is allocated to partition %d of size %d\n", i + 1, processes[i], best_fit_index + 1, partition_sizes[best_fit_index]);
            partitions[best_fit_index] = 'A';
            partition_sizes[best_fit_index] -= processes[i];
            flag = 1;
        }
        if (flag == 0) {
            printf("Process %d of size %d is not allocated\n", i + 1, processes[i]);
        }
    }
    return 0;
}
