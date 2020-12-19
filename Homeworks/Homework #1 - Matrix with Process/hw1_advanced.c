//
//  main.c
//  Matrix with Process and Shared Memory
//
//  Created by Tomy Hsieh on 2020/11/12.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
const char *name = "mtx";

int main(int argc, const char *argv[]) {

  // Dimension
  int n;
  printf("Matrix Size: ");
  scanf("%d", &n);
  const int SIZE = n * n * sizeof(int);

  // Matrix C
  int *c = (int *)malloc(SIZE);
  printf("Input Matrix C:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &c[i]);
  }

  // Matrix D
  int *d = (int *)malloc(SIZE);
  printf("Input Matrix D:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &d[i]);
  }

  // Initialize shared memory
  int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  if (shm_fd < 0) {
    perror("Shared memory open error");
    exit(1);
  }
  ftruncate(shm_fd, SIZE);
  int *shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_base == MAP_FAILED) {
    perror("Shared memory mapping error");
    exit(1);
  }

  // Spawn children
  for (int row = 0; row < n; row++) {
    if (fork() == 0) {
      // Child process, calculate cell value and store to shared memory
      for (int col = 0; col < n; col++) {
        shm_base[row * n + col] = 0;
        for (int i = 0; i < n; i++) {
          shm_base[row * n + col] += c[row * n + i] * d[n * i + col];
        }
      }
      // Exit explicitly
      exit(0);
    }
  }

  // Wait for all children to exit
  while (wait(NULL) != -1)
    ;

  // Print results
  printf("Results:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", shm_base[i * n + j]);
    }
    printf("\n");
  }

  // Clean Up
  if (munmap(shm_base, SIZE) == -1) {
    perror("Shared memory unmapping error");
    exit(1);
  }
  if (close(shm_fd) == -1) {
    perror("Shared memory close error");
    exit(1);
  }
  shm_unlink(name);
  free(d);
  free(c);
}
