#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    if(fork() == 0) {
        if(fork() == 0) {
            printf("I'm child process C.\nPID: %d\tParent PID: %d\n", getpid(), getppid());
        } else {
            wait(NULL);
            printf("I'm child process B.\nPID: %d\tParent PID: %d\n", getpid(), getppid());
        }
        return 0;
    } else {
        wait(NULL);
    }
    
    if(fork() == 0) {
        printf("I'm child process D.\nPID: %d\tParent PID: %d\n", getpid(), getppid());
        return 0;
    } else {
        wait(NULL);
    }
    
    if(fork() == 0) {
        printf("I'm child process E.\nPID: %d\tParent PID: %d\n", getpid(), getppid());
        return 0;
    } else {
        wait(NULL);
    }
    
    printf("I'm child process A.\nPID: %d\tParent PID: %d\n", getpid(), getppid());
    
}
