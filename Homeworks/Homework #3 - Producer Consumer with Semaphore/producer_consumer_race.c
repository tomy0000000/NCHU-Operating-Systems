//
//  producer_consumer_race.c
//  Producer Consumer
//
//  Created by Tomy Hsieh on 2021/1/2.
//  Copyright © 2021 Tomy Hsieh. All rights reserved.
//

#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

int buffer_size;
int buffer[5];

void *producer() {
  for (int i=0; i<5; i++) {
    bool produced = false;
    while (!produced) {
      if (buffer_size < 5) {
        buffer[buffer_size++] = 0;
        printf("run producer count=%d\n", buffer_size);
        produced = true;
      }
    }
  }
  pthread_exit(NULL);
}

void *consumer() {
  for (int i=0; i<5; i++) {
    bool consumed = false;
    while (!consumed) {
      if (buffer_size > 0) {
        printf("run consumer count=%d\n", --buffer_size);
        consumed = true;
      }
    }
  }
  pthread_exit(NULL);
}

int main(int argc, const char * argv[]) {
  
  // Initialize
  buffer_size = 0;
  
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
  
}
