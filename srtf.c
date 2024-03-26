#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main() {
    int n, i, j, temp, time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rem_bt[n];
    printf("Enter the process id, arrival time and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        scanf("%d%d%d", &pid[i], &at[i], &bt[i]);
        rem_bt[i] = bt[i]; 
    }

    int completed = 0; 
    while (completed < n) { 
        int shortest = -1; 
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rem_bt[i] > 0 && (shortest == -1 || rem_bt[i] < rem_bt[shortest])) {
                shortest = i;
            }
        }

        rem_bt[shortest]--; 
        time++;

        if (rem_bt[shortest] == 0) { 
            completed++;
            ct[shortest] = time;
            tat[shortest] = ct[shortest] - at[shortest];
            wt[shortest] = tat[shortest] - bt[shortest];
        }
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