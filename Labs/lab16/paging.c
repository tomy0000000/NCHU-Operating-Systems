#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

int free_frames[16];
int free_frame_i = 0;

bool mem_occupied(int n) {
    for(int i = 0; i < free_frame_i; i++) {
        if(free_frames[i] == n) {
            return true;
        }
    }
    return false;
}

int main() {

    srand(time(NULL));

    const char *a_mem[3];
    a_mem[0] = "ab";
    a_mem[1] = "ef";
    a_mem[2] = "cd";
    
    const char *b_mem[3];
    b_mem[0] = "rx";
    b_mem[1] = "yy";
    b_mem[2] = "zz";
    
    int a_page_table[3], b_page_table[3];
    
    
    char *phys_mem[16];
    for(int i = 0; i < 16; i++) {
        phys_mem[i] = "--";
    }
    
    int loc;
    for(int i = 0; i < 3; i++) {
        do {
            loc = rand() % 16;
        } while(mem_occupied(loc));
        free_frames[free_frame_i++] = loc;
        a_page_table[i] = loc;
        phys_mem[loc] = a_mem[i];
    }
    for(int i = 0; i < 3; i++) {
        do {
            loc = rand() % 16;
        } while(mem_occupied(loc));
        free_frames[free_frame_i++] = loc;
        b_page_table[i] = loc;
        phys_mem[loc] = b_mem[i];
    }
    
    printf("Process A's page table is:\n");
    printf("page\tframe\n");
    for(int i = 0; i < 3; i++) {
        printf("%d\t%d\n", i, a_page_table[i]);
    }
    
    printf("Process A's logical memory is:\n");
    printf("page\tdata\n");
    for(int i = 0; i < 3; i++) {
        printf("%d\t%s\n", i, a_mem[i]);
    }
    
    printf("Process B's page table is:\n");
    printf("page\tframe\n");
    for(int i = 0; i < 3; i++) {
        printf("%d\t%d\n", i, b_page_table[i]);
    }
    
    printf("Process B's logical memory is:\n");
    printf("page\tdata\n");
    for(int i = 0; i < 3; i++) {
        printf("%d\t%s\n", i, a_mem[i]);
    }
    
    printf("physicla memory is:\n");
    printf("frame\toffset\tdata\n");
    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d\t%d\t", i, j);
            printf("\t%c\n", phys_mem[i][j]);
        }
    }
    
    printf("free frame is:\n");
    for(int i = 0; i < 16; i++) {
        if(mem_occupied(i)) {
            continue;
        }
        printf("%d ", i);
    }
    printf("\n");
    
    return 0;
}
