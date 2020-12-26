#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>
#include <pthread.h>
#define receiver_name "/q2uque"
#define sender_name "/q2uque2"
#define MSG_STOP "/0"
#define MAX_SIZE 1000

int terminate = 0;

void *receiver(void *arg) {
    mqd_t mq1;
    char buffer[MAX_SIZE + 1];
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    mq1 = mq_open(receiver_name, O_RDONLY|O_CREAT, 0644, &attr);
    if (mq1 == -1) {
        perror("mq error:\n");
        exit(1);
    }
    do {
        ssize_t bytes_read;
        bytes_read = mq_receive(mq1, buffer, 8192, NULL);
        if (bytes_read<0) {
            perror("bytes_read error\n");
            exit(1);
        }
        buffer[bytes_read] = '\0';
        if (!strncmp(buffer, MSG_STOP, strlen(MSG_STOP))) {
            terminate = 1;
        } else {
            printf("Received: %s", buffer);
        }
        if (strncmp(buffer, "exit", 4) == 0) {
            terminate = 1;
        }
    } while (!terminate);
    int s_close = mq_close(mq1);
    if (s_close == -1) {
        perror("s_close error:\n");
        exit(1);
    }
    if (mq_unlink(receiver_name) == -1) {
        exit(0);
    }
    pthread_exit(NULL);
}

void *sender(void *arg) {
    mqd_t mq1;
    char buffer[MAX_SIZE];
    mq1 = mq_open(sender_name, O_WRONLY|O_CREAT, 0644, NULL);
    if (mq1 == -1) {
        perror("mq1 error:\n");
        exit(1);
    }
    do {
        for (int i=0; i<sizeof(buffer); i++) {
            buffer[i] = '\0';
        }
        fgets(buffer, MAX_SIZE, stdin);
        int send = mq_send(mq1, buffer, strlen(buffer)+1, 0);
        if (send < 0) {
            perror("message:\n");
            exit(1);
        }
        if (strncmp(buffer, "exit", 4) == 0) {
            terminate = 1;
        }
    } while (!terminate);
    int s_close = mq_close(mq1);
    if (s_close == -1) {
        perror("s_close error:\n");
        exit(1);
    }
    if (mq_unlink(receiver_name) == -1) {
        exit(0);
    }
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    int tmp = 0;
    void *ret;
    
    pthread_t listen_thread, send_thread;
    if (pthread_create(&listen_thread, NULL, receiver, &tmp)) {
        printf("CREATE ERROR\n");
        exit(-1);
    }
    if (pthread_create(&send_thread, NULL, sender, &tmp)) {
        printf("CREATE ERROR\n");
        exit(-1);
    }
    if (pthread_join(listen_thread, &ret)) {
        printf("JOIN ERROR\n");
        exit(-1);
    }
    if (pthread_join(send_thread, &ret)) {
        printf("JOIN ERROR\n");
        exit(-1);
    }

    return 0;
}

