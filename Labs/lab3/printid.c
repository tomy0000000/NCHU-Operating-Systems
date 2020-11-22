#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    printf("Read Uid=%d\n""effectuve Uid=%d\n", getuid(), geteuid());
    return 0;
}
