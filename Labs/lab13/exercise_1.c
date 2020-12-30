#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int glob = 0;

pthread_mutex_t mtx;

static void *threadFunc(void *arg) {
    int loops = *((int*)arg);
    int loc, s;

    s = pthread_mutex_init(&mtx, NULL);

    for(int j=0; j < loops; ++j) {
        s = pthread_mutex_lock(&mtx);
        
        if(s != 0) {
            printf("pthread_mutex_lock ERROR");
        }

        loc = glob;
        loc += 2;
        glob = loc;
        
        s = pthread_mutex_unlock(&mtx);

        if(s != 0) {
            printf("pthread_mutex_unlock ERROR");
        }
    }
    return NULL;
}

static void *threadFunc2(void *arg) {
    int loops = *((int*)arg);
    int loc, s;

    s = pthread_mutex_init(&mtx, NULL);

    for(int j=0; j < loops; ++j) {
        s = pthread_mutex_lock(&mtx);
        
        if(s != 0) {
            printf("pthread_mutex_lock ERROR");
        }

        loc = glob;
        loc -= 2;
        glob = loc;
        
        s = pthread_mutex_unlock(&mtx);

        if(s != 0) {
            printf("pthread_mutex_unlock ERROR");
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2, t3;
    int loops, s;

    loops = atoi(argv[1]);

    s = pthread_create(&t1, NULL, threadFunc, &loops);
    if (s != 0) {
        printf("pthread_create ERROR");
    }
    s = pthread_create(&t2, NULL, threadFunc, &loops);
    if (s != 0) {
        printf("pthread_create ERROR");
    }
    s = pthread_create(&t3, NULL, threadFunc2, &loops);
    if (s != 0) {
        printf("pthread_create ERROR");
    }

    s = pthread_join(t1, NULL);
    if (s != 0) {
        printf("pthread_join ERROR");
    }
    s = pthread_join(t2, NULL);
    if (s != 0) {
        printf("pthread_join ERROR");
    }
    s = pthread_join(t3, NULL);
    if (s != 0) {
        printf("pthread_join ERROR");
    }

    printf("glob = %d\n", glob);
    s = pthread_mutex_destroy(&mtx);
    return 0;
}
