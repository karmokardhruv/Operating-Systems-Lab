#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

int main() {
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int AT[n], BT[n], ST[n][20], WT[n], FT[n], TAT[n], quant;
    char pid[n][21];

    printf("Enter the time quantum: ");
    scanf("%d", &quant);

    printf("Enter the process id, arrival time, and burst time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", i + 1);
        scanf("%d%d", &AT[i], &BT[i]);
    }

    int c = n;
    int s[n][20];
    float time = 0;
    float mini = INT_MAX;
    float b[n];
    float a[n];
    int index = -1;

    for (i = 0; i < n; i++) {
        b[i] = BT[i];
        a[i] = AT[i];
        for (j = 0; j < 20; j++) {
            s[i][j] = -1;
        }
    }

    int tot_wt = 0;
    int tot_tat = 0;
    bool flag = false;

    while (c != 0) {
        mini = INT_MAX;
        flag = false;

        for (i = 0; i < n; i++) {
            float p = time + 0.1;
            if (a[i] <= p && mini > a[i] && b[i] > 0) {
                index = i;
                mini = a[i];
                flag = true;
            }
        }

        if (!flag) {
            time++;
            continue;
        }

        j = 0;
        while (s[index][j] != -1) {
            j++;
        }

        if (s[index][j] == -1) {
            s[index][j] = time;
            ST[index][j] = time;
        }

        if (b[index] <= quant) {
            time += b[index];
            b[index] = 0;
        } else {
            time += quant;
            b[index] -= quant;
        }

        if (b[index] > 0) {
            a[index] = time + 0.1;
        }

        if (b[index] == 0) {
            c--;
            FT[index] = time;
            WT[index] = FT[index] - AT[index] - BT[index];
            tot_wt += WT[index];
            TAT[index] = BT[index] + WT[index];
            tot_tat += TAT[index];
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i + 1, AT[i], BT[i], FT[i], TAT[i], WT[i]);
    }

    double avg_wt = (double)tot_wt / n;
    double avg_tat = (double)tot_tat / n;
    printf("Average turn around time: %.2lf\n", avg_tat);
    printf("Average waiting time: %.2lf\n", avg_wt);

    return 0;
}
