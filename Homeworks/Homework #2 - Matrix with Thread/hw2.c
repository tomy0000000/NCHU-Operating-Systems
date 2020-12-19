//
//  main.c
//  Matrix with Thread
//
//  Created by Tomy Hsieh on 2020/11/13.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int n, *c, *d;

// Thread function
void *row_calculation(void *args) {
  int row = *(int *)args;
  int *results = (int *)malloc(n * sizeof(int));
  // Calculate each cell value of the row
  for (int col = 0; col < n; col++) {
    results[col] = 0;
    for (int i = 0; i < n; i++) {
      results[col] += c[row * n + i] * d[n * i + col];
    }
  }
  // reuslts is a malloc array and should be free manually from main thread
  pthread_exit(results);
}

int main(int argc, const char *argv[]) {

  // Dimension
  printf("Matrix Size: ");
  scanf("%d", &n);

  // Matrix C
  c = (int *)malloc(n * n * sizeof(int));
  printf("Input Matrix C:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &c[i]);
  }

  // Matrix D
  d = (int *)malloc(n * n * sizeof(int));
  printf("Input Matrix D:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &d[i]);
  }

  // Create plain int array
  int *plain_ints = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    plain_ints[i] = i;
  }

  // Spawn children
  pthread_t *threads = malloc(n * sizeof(pthread_t));
  for (int row = 0; row < n; row++) {
    pthread_create(&threads[row], NULL, row_calculation, &plain_ints[row]);
  }

  // Print results
  printf("Results:\n");
  for (int row = 0; row < n; row++) {
    int *results;
    // Wait for thread to exit, and collect its result
    pthread_join(threads[row], (void *)&results);
    for (int col = 0; col < n; col++) {
      printf("%d ", results[col]);
    }
    printf("\n");
    // Manually free malloc results
    free(results);
  }

  // Clean Up
  free(threads);
  free(plain_ints);
  free(d);
  free(c);
}
