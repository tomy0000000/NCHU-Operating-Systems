//
//  main.c
//  Matrix with Process
//
//  Created by Tomy Hsieh on 2020/11/12.
//  Copyright © 2020 Tomy Hsieh. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {

  // Dimension
  int n;
  printf("Matrix Size: ");
  scanf("%d", &n);

  // Matrix C
  int *c = (int *)malloc(n * n * sizeof(int));
  printf("Input Matrix C:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &c[i]);
  }

  // Matrix D
  int *d = (int *)malloc(n * n * sizeof(int));
  printf("Input Matrix D:\n");
  for (int i = 0; i < n * n; i++) {
    scanf("%d", &d[i]);
  }

  // Spawn children
  pid_t *pids = malloc(n * n * sizeof(pid_t));
  for (int i = 0; i < n * n; i++) {
    if ((pids[i] = fork()) == 0) {
      // Child process, calculate cell value
      int row = i / n, col = i % n, cell = 0;
      for (int j = 0; j < n; j++) {
        cell += c[row * n + j] * d[n * j + col];
      }
      exit(cell);
    }
  }

  // Collect answers
  int *answer = (int *)malloc(n * n * sizeof(int));
  for (int i = 0; i < n * n; i++) {
    int result;
    // Wait on each processes
    if (waitpid(pids[i], &result, WUNTRACED | WCONTINUED) == -1) {
      perror("Wait PID error");
    }
    if (WIFEXITED(result)) {
      // Child exit successfully, extract value from exit code
      answer[i] = WEXITSTATUS(result);
    } else if (WIFSIGNALED(result)) {
      printf("%d Killed by signal %d\n", pids[i], WTERMSIG(result));
    } else if (WIFSTOPPED(result)) {
      printf("%d Stopped by signal %d\n", pids[i], WSTOPSIG(result));
    } else if (WIFCONTINUED(result)) {
      printf("%d Continued\n", pids[i]);
    }
  }

  // Print results
  printf("Results:\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", answer[i * n + j]);
    }
    printf("\n");
  }

  // Clean Up
  free(answer);
  free(d);
  free(c);
  free(pids);
}
