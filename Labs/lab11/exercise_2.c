#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void catch_int_1(int sig_num) {
    printf("How are you?\n");
}

void catch_int_2(int sig_num) {
    printf("I am fine!\n");
}

int main() {
    time_t start = time(NULL);
    while(1) {
        if(time(NULL) - start < 3) {
            signal(SIGINT, catch_int_1);
        } else if(time(NULL) - start < 6) {
            signal(SIGINT, catch_int_2);
        } else {
            signal(SIGINT, SIG_DFL);
            break;
        }
    }
    signal(SIGALRM, SIG_IGN);
    alarm(3);
    while(1);
}