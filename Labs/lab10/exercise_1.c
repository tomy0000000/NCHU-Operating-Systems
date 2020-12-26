#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

static __thread int glob = 0;

void *incr_2(void *arg) {

    int loc;
    for (int i = 0; i < *(int*)arg; ++i) {
        loc = glob;
        loc++;
        glob = loc;
    }
    printf("thread_ID = %lu , glob = %d\n", pthread_self(), glob);
    pthread_exit(NULL);
}

int main() {
    pthread_t id[2];
    int a = 50, b = 100;
    pthread_create(&id[0], NULL, incr_2, &a);
    pthread_create(&id[1], NULL, incr_2, &b);
    
    pthread_join(id[0], NULL);
    pthread_join(id[1], NULL);

    return 0;
}