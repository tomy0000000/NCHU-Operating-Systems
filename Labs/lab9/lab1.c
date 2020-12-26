#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;

void *thread_func(void *arg) {
    printf("Thread ID: %lu\n", pthread_self());
    printf("Iteration: %d\n", *(int*)arg + 1);
    int re = 50;
    for (int i = 0; i < 250000; ++i) {
        count++;
    }
    pthread_exit((void*)re);
}

int main(int argc, char const *argv[]) {

    pthread_t threads[4];
    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&threads[i], NULL, thread_func, &i)) {
            printf("CREATE ERROR\n");
            exit(-1);
        }
    }

    for (int i = 0; i < 4; ++i) {
        void *ret;
        if (pthread_join(threads[i], &ret)) {
            printf("JOIN ERROR\n");
            exit(-1);
        }
    }    

    printf("count: %d\n", count);

    return 0;
}
