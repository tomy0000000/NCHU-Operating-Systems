#include <stdio.h>
extern int selection_sort(int list[], int n);

int main() {

    int numbers[] = {15, 22, 41, 8, 35};

    selection_sort(numbers, 5);
    
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
}