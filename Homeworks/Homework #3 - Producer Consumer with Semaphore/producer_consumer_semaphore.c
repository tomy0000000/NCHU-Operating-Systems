//
//  producer_consumer_semaphore.c
//  Producer Consumer with Semaphore
//
//  Created by Tomy Hsieh on 2021/1/2.
//  Copyright © 2021 Tomy Hsieh. All rights reserved.
//

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

sem_t lock;
int buffer_size;
int buffer[5];

void *producer() {
  for (int i=0; i<5; i++) {
    bool produced = false;
    while (!produced) {
      if (sem_wait(&lock) == -1) {
        perror("Producer sem_wait error");
        exit(1);
      }
      if (buffer_size < 5) {
        buffer[buffer_size++] = 0;
        printf("run producer count=%d\n", buffer_size);
        produced = true;
      }
      if (sem_post(&lock) == -1) {
        perror("Producer sem_post error");
        exit(1);
      }
    }
  }
  pthread_exit(NULL);
}

void *consumer() {
  for (int i=0; i<5; i++) {
    bool consumed = false;
    while (!consumed) {
      if (sem_wait(&lock) == -1) {
        perror("Consumer sem_wait error");
        exit(1);
      }
      if (buffer_size > 0) {
        printf("run consumer count=%d\n", --buffer_size);
        consumed = true;
      }
      if (sem_post(&lock) == -1) {
        perror("Consumer sem_post error");
        exit(1);
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, const char * argv[]) {
  
  // Initialize
  buffer_size = 0;
  if (sem_init(&lock, 1, 1) == -1) {
    perror("Semaphore init error");
    exit(1);
  }
  
  // Create 2 producers + 2 consumers
  pthread_t p1, p2, c1, c2;
  pthread_create(&p1, NULL, &producer, NULL);
  pthread_create(&p2, NULL, &producer, NULL);
  pthread_create(&c1, NULL, &consumer, NULL);
  pthread_create(&c2, NULL, &consumer, NULL);
  
  // Join on all threads
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  pthread_join(c1, NULL);
  pthread_join(c2, NULL);
  
  // Destroy semaphore
  if (sem_destroy(&lock) == -1) {
    perror("Semaphore destroy error");
    exit(1);
  }
  
}
