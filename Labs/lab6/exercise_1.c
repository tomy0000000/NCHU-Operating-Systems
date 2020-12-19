#include <unistd.h>
#include <stdio.h>

int global = 10;

int main() {
    
    pid_t new_pid;
    int local = 10;
    
    printf("global: %d\n", global);
    printf("local: %d\n", local);
    
    new_pid = fork();
    switch(new_pid) {
        case -1:
            printf("Fork Error\n");
            break;
        case 0:
            printf("\n-----This is child process-----\n");
            global++;
            local++;
            printf("PID: %d\nParent PID: %d\n", getpid(), getppid());
            printf("global: %d\n", global);
            printf("local: %d\n", local);
            printf("-------------------------------\n");
            break;
        default:
            printf("\n-----This is parent process-----\n");
            printf("PID: %d\nChild PID: %d\n", getpid(), new_pid);
            printf("global: %d\n", global);
            printf("local: %d\n", local);
            printf("--------------------------------\n");
            break;
    }
    return 0;
}
