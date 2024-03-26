#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
int main()
{
    int n, i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int AT[n], BT[n], ST[n][20], WT[n], FT[n], TAT[n], priority[n];
    char pid[n][21];
    printf("Enter the Process ID, Arrival Time, Burst Time, and Priority:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%s%d%d%d", pid[i], &AT[i], &BT[i], &priority[i]);
    }
    int c = n, s[n][20];
    float time = 0, mini = INT_MAX, b[n], a[n];
    int index = -1;
    for (i = 0; i < n; i++)
    {
        b[i] = BT[i];
        a[i] = AT[i];
        for (j = 0; j < 20; j++)
        {
            s[i][j] = -1;
        }
    }
    int tot_wt, tot_tat;
    tot_wt = 0;
    tot_tat = 0;
    bool flag = false;
    while (c != 0)
    {
        mini = INT_MAX;
        flag = false;
        for (i = 0; i < n; i++)
        {
            float p = time + 0.1;
            if (a[i] <= p && priority[i] < mini && b[i] > 0)
            {
                index = i;
                mini = priority[i];
                flag = true;
            }
        }
        if (!flag)
        {
            time++;
            continue;
        }
        j = 0;
        while (s[index][j] != -1)
        {
            j++;
        }
        if (s[index][j] == -1)
        {
            s[index][j] = time;
            ST[index][j] = time;
        }
        if (b[index] <= 1)
        {
            time += b[index];
            b[index] = 0;
        }
        else
        {
            time += 1;
            b[index] -= 1;
        }
        if (b[index] > 0)
        {
            a[index] = time + 0.1;
        }
        if (b[index] == 0)
        {
            c--;
            FT[index] = time;
            WT[index] = FT[index] - AT[index] - BT[index];
            tot_wt += WT[index];
            TAT[index] = BT[index] + WT[index];
            tot_tat += TAT[index];
        }
    }

    printf("PID\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
    for (i = 0; i < n; i++)
    {
        printf("%s\t", pid[i]);
        printf("%d\t", AT[i]);
        printf("%d\t", BT[i]);
        printf("%d\t", FT[i]);
        printf("%d\t", TAT[i]);
        printf("%d\t", WT[i]);
        printf("%d\n", priority[i]);
    }
    double avg_wt, avg_tat;
    avg_wt = tot_wt / (float)n;
    avg_tat = tot_tat / (float)n;
    printf("The Average Turnaround Time is: %.2lf\n", avg_tat);
    printf("The average Wait Time is: %.2lf\n", avg_wt);
    return 0;
}