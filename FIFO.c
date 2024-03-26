//write the code for Page replacement Algorithm
// it should be using the FIFO algorithm
// FIRST , I will input the total number of pages
// then i will input the pages
// then i will input size of main memory (3 frames)
// For output , I will print the page fault and the page hit

//Example:
//Sample Input:
//12
//0 1 2 3 0 1 4 0 1 2 3 4
//3
//Sample Output:
//Iter1: 0 0 0  miss
//Iter2: 0 1 0  miss
//Iter3: 2 1 0  miss
//Iter4: 2 1 3  miss
//Iter5: 2 0 3  miss
//Iter6: 1 0 3  miss
//Iter7: 1 0 4  miss
//Iter8: 1 0 4  hit
//Iter9: 1 0 4  hit
//Iter10: 1 2 4  miss
//Iter11: 3 2 4  miss
//Iter12: 3 2 4  hit
//Miss: 9
//Hit: 3

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
    for(i = 0; i < m; i++)
    {
        main_memory[i] = -1;
    }
    for(i = 0; i < n; i++)
    {
        bool flag = false;
        for(j = 0; j < m; j++)
        {
            if(pages[i] == main_memory[j])
            {
                flag = true;
                page_hit++;
                break;
            }
        }
        if(flag == false)
        {
            page_fault++;
            for(j = 0; j < m; j++)
            {
                if(main_memory[j] == -1)
                {
                    main_memory[j] = pages[i];
                    break;
                }
            }
            if(j == m)
            {
                for(k = 0; k < m; k++)
                {
                    main_memory[k] = main_memory[k + 1];
                }
                main_memory[m - 1] = pages[i];
            }
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