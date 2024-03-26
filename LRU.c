#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main()
{
    int n, i, j, k, m, page_fault = 0, page_hit = 0;
    printf("Enter the total number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter the pages: ");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }
    printf("Enter the size of main memory: ");
    scanf("%d", &m);
    int main_memory[m];
    int timestamp[m];

    for(i = 0; i < m; i++)
    {
        main_memory[i] = -1;
        timestamp[i] = 0;
    }

    int curr_time = 1;

    for(i = 0; i < n; i++)
    {
        bool flag = false;
        for(j = 0; j < m; j++)
        {
            if(pages[i] == main_memory[j])
            {
                flag = true;
                page_hit++;
                timestamp[j] = curr_time; 
                curr_time++;
                break;
            }
        }
        if(flag == false)
        {
            page_fault++;
            int min_timestamp = timestamp[0];
            int min_timestamp_index = 0;

            for(j = 1; j < m; j++)
            {
                if(timestamp[j] < min_timestamp)
                {
                    min_timestamp = timestamp[j];
                    min_timestamp_index = j;
                }
            }

            main_memory[min_timestamp_index] = pages[i]; 
            timestamp[min_timestamp_index] = curr_time;
            curr_time++;
        }

        printf("Iter%d: ", i + 1);
        for(j = 0; j < m; j++)
        {
            printf("%d ", main_memory[j]);
        }
        if(flag == false)
        {
            printf("miss\n");
        }
        else
        {
            printf("hit\n");
        }
    }
    printf("Miss: %d\n", page_fault);
    printf("Hit: %d\n", page_hit);
    return 0;
}
