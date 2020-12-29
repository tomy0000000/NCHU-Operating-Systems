#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
sem_t *mutex;

int count = 0;
void inc(void);
void dec(void);

int main(void) {
    
    int i=0;
    mutex = sem_open("/the_lock", O_CREAT, 0644, 1);
    if (mutex == SEM_FAILED) {
        sem_close(mutex);
        perror("Failed to open semphore");
        exit(-1);
    }

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
    sem_close(mutex);
    sem_unlink("/the_lock");
}

void inc(void) {
    sem_wait(mutex);

    for (int i=0; i<25000000; i++) {
        count++;
    }

    sem_post(mutex);
    pthread_exit(NULL);
}

void dec(void) {
    sem_wait(mutex);

    for (int i=0; i<25000000; i++) {
        count--;
    }

    sem_post(mutex);
    pthread_exit(NULL);
}
