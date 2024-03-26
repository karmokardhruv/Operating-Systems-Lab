#include <stdio.h>
#include <stdbool.h>
int main() {
    int n, m, i, j, k;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    int totalAvailable[m];
    int maximum[n][m];
    int allocated[n][m];
    int need[n][m];
    bool finished[n];
    char pid[n][21];
    printf("Enter the total number of available instances for each resource: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &totalAvailable[i]);
    }
    printf("Enter the Process IDs: ");
    for (i = 0; i < n; i++) {
        scanf("%s", pid[i]);
    }
    printf("Enter the maximum number of instances for:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }
    printf("Enter the number of allocated instances for:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocated[i][j]);
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
        finished[i] = false;
    }
    int available[m];
    for (j = 0; j < m; j++) {
        available[j] = totalAvailable[j];
        for (i = 0; i < n; i++) {
            available[j] -= allocated[i][j];
        }
    }
    int work[m];
    bool canAllocate;
    int safetySequence[n];
    int sequenceIndex = 0;
    for (i = 0; i < m; i++) {
        work[i] = available[i];
    }
    int count = 0;
    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finished[i]) {
                canAllocate = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (j = 0; j < m; j++) {
                        work[j] += allocated[i][j];
                    }
                    safetySequence[sequenceIndex++] = i;
                    finished[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }
    if (count == n) {
        printf("The SAFE Sequence is as follows: ");
        for (i = 0; i < n - 1; i++) {
            printf("%s -> ", pid[safetySequence[i]]);
        }
        printf("%s\n", pid[safetySequence[n - 1]]);
    } else {
        printf("The system is in an unsafe state. Deadlock detected.\n");
    }
    return 0;
}
