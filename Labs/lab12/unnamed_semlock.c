#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
sem_t mutex;

int count = 0;
void inc(void);
void dec(void);

int main(void) {
    
    int i=0;
    sem_init(&mutex, 0, 1);

    pthread_t id[4];
    pthread_create(&id[0], NULL,(void*)dec, NULL);
    pthread_create(&id[1], NULL,(void*)inc, NULL);
    pthread_create(&id[2], NULL,(void*)dec, NULL);
    pthread_create(&id[3], NULL,(void*)inc, NULL);
    
    for(i=0; i<4; i++) {
        pthread_join(id[i], NULL);
    }
    printf("Output is %d\n", count);
    pthread_exit(NULL);
    sem_destroy(&mutex);
}

void inc(void) {
    sem_wait(&mutex);

    for (int i=0; i<25000000; i++) {
        count++;
    }

    sem_post(&mutex);
    pthread_exit(NULL);
}

void dec(void) {
    sem_wait(&mutex);

    for (int i=0; i<25000000; i++) {
        count--;
    }

    sem_post(&mutex);
    pthread_exit(NULL);
}
