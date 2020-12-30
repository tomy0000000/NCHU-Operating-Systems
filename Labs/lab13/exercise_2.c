#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int glob = 1;

pthread_mutex_t mtx;
pthread_cond_t conds[8];

static void *threadFunc(void *arg) {
    pthread_mutex_init(&mtx, NULL);
    while (1) {
        if (glob != *((int *)arg)) {
            pthread_cond_wait(&conds[*((int *)arg)], &mtx);
        }
        
        printf("%d\t", glob);
        glob = (*((int *)arg) + 2) % 6;
        
        pthread_cond_signal(&conds[glob]);
    }
}

int main(int argc, char *argv[]) {

    pthread_t ts[8];
    int ints[] = {0, 1, 2, 3, 4, 5, 6, 7};

    for (int i = 1; i <= 5; i += 2) {
        pthread_cond_init(&conds[i], NULL);
    }
    for (int i = 1; i <= 5; i += 2) {
        pthread_create(&ts[i], NULL, threadFunc, &ints[i]);
    }
    
    while (1) pause();
}
