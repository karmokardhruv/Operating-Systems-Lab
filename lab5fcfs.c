#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main() {
    int n, i, j, temp;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];
    printf("Enter the process id, arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &pid[i], &at[i], &bt[i]);
    }
   
    for (i = 0; i < n; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (at[j] > at[j + 1]) {
                temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (i == 0) {
            ct[i] = at[i] + bt[i];
        } else {
            if (at[i] > ct[i - 1]) {
                ct[i] = at[i] + bt[i];
            } else {
                ct[i] = ct[i - 1] + bt[i];
            }
        }
    }

    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
    }

    for (i = 0; i < n; i++) {
        wt[i] = tat[i] - bt[i];
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
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