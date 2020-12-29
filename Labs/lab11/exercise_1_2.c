#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    if(fork() == 0) {
        printf("Child PID: %d\n", getpid());
        kill(getppid(), SIGTERM);
    } else {
        printf("Parent PID: %d\n", getpid());
    }
}