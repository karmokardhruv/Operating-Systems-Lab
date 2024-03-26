#include <stdio.h>

int main() 
{
    int count = 0;
    int k;
    printf("Enter the total number of pages: ");
    scanf("%d", &k);
    int ref_str[k];
    printf("Enter the pages: ");
    for (int i = 0; i < k; i++) 
    {
        scanf("%d", &ref_str[i]);
    }
    int refStrLen = sizeof(ref_str) / sizeof(ref_str[0]);
    int max_frames;
    printf("Enter the size of main memory: ");
    scanf("%d", &max_frames);
    int frame_items[max_frames];
    int frame_occupied = 0;
    int hits = 0;

    for (int i = 0; i < refStrLen; i++) 
    {
        int key = ref_str[i];
        int result = -1, farthest = i;
        
        int page_found = 0;
        for (int j = 0; j < frame_occupied; j++) 
        {
            if (frame_items[j] == key) 
            {
                hits++;
                page_found = 1;
                break;
            }
        }
        
        if (page_found) 
        {
            count++;
            printf("Iter%d: ", count);
            for (int j = 0; j < max_frames; j++) 
            {
                if (j < frame_occupied)
                    printf("%d ", frame_items[j]);
                else
                    printf("-1 ");
            }
            printf("hit\n");
            continue;
        }
        
        if (frame_occupied < max_frames) 
        {
            frame_items[frame_occupied] = key;
            frame_occupied++;
        } 
        
        else 
        {
            for (int j = 0; j < frame_occupied; j++) 
            {
                int k;
                for (k = i; k < refStrLen; k++) 
                {
                    if (frame_items[j] == ref_str[k]) 
                    {
                        if (k > farthest) 
                        {
                            farthest = k;
                            result = j;
                        }
                        break;
                    }
                }
                
                if (k == refStrLen) 
                {
                    result = j;
                    break;
                }
            }
            frame_items[result] = key;
        }

        count++;
        printf("Iter%d: ", count);
        for (int j = 0; j < max_frames; j++) 
        {
            if (j < frame_occupied)
                printf("%d ", frame_items[j]);
            else
                printf("-1 ");
        }
        printf("miss\n");
    }
    
    printf("Miss: %d\n", refStrLen - hits);
    printf("Hit: %d\n", hits);
    
    return 0;
}