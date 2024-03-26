#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, i, j, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n],dup_bt[n];

    printf("Enter the process id, arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &pid[i], &at[i], &bt[i]);
        dup_bt[i]=bt[i];
    }

    // Sort processes based on arrival time using selection sort
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                swap(&pid[i], &pid[j]);
                swap(&at[i], &at[j]);
                swap(&bt[i], &bt[j]);
            }
        }
    }

    int complete = 0;
    int shortest = 0;
    int time = 0;

    while (complete != n) {
        shortest = -1;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && bt[i] > 0) {
                if (shortest == -1 || bt[i] < bt[shortest]) {
                    shortest = i;
                }
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        ct[shortest] = time + bt[shortest];
        tat[shortest] = ct[shortest] - at[shortest];
        wt[shortest] = tat[shortest] - bt[shortest];

        bt[shortest] = 0;
        time = ct[shortest];
        complete++;
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], dup_bt[pid[i]-1], ct[i], tat[i], wt[i]);
    }

    float avg_tat = 0, avg_wt = 0;
    for (i = 0; i < n; i++) {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= n;
    avg_wt /= n;
    printf("Average turn around time: %.2f\n", avg_tat);
    printf("Average waiting time: %.2f\n", avg_wt);

    return 0;
}
