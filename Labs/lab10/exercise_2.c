#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int *result;

void *child(void *arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    int *input = (int*) arg;
    result = malloc(sizeof(int) * 1);
    *result = input[0] + input[1];
    for (int i = 0; i < 3; ++i) {
        sleep(1);
        printf("sleep: %d\n", i+1);
    }
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    for (int i = 0; i < 3; ++i) {
        sleep(1);
        printf("sleep: %d\n", i+1);
    }
    pthread_exit((void*)result);
}

int main() {
    pthread_t t;
    void *ret;
    int input[2] = {1, 2};

    pthread_create(&t, NULL, child, (void*)input);

    if (pthread_cancel(t) == 0) {
        printf("pthread success\n");
    } else {
        printf("pthread error\n");
    }

    pthread_join(t, NULL);

    printf("main thread:\n");
    printf("result: %d + %d = %d\n", input[0], input[1], *result);

    free(result);

    return 0;
}