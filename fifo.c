#include <stdio.h>

int main() {
    int pages[50], frames[10], n, f;
    int i, j, k = 0, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for(i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for(i = 0; i < f; i++)
        frames[i] = -1; // initialize empty frames

    printf("\nPage\tFrames\n-----------------\n");

    for(i = 0; i < n; i++) {
        int found = 0;
        for(j = 0; j < f; j++) {
            if(frames[j] == pages[i]) { // page hit
                found = 1;
                break;
            }
        }

        if(!found) { // page fault
            frames[k] = pages[i];
            k = (k + 1) % f; // FIFO pointer
            faults++;
        }

        printf("%d\t", pages[i]);
        for(j = 0; j < f; j++)
            if(frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        printf("\n");
    }

    printf("-----------------\nTotal Page Faults = %d\n", faults);
    return 0;
}
