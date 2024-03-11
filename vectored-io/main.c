#include <stdio.h>
#include <unistd.h>
#include <sys/uio.h>
#include <string.h>

int main() {

    ssize_t res;

    struct iovec iov;

    char buffer[1024];
    char buffer2[1024];

    iov.iov_base = buffer;
    iov.iov_len = 5 + 1;

    struct iovec iov2;
    iov2.iov_base = buffer2;
    iov2.iov_len = 10 + 1;

    res = readv(STDIN_FILENO, &iov, 2);

    printf("%li\n", res);

    printf("%s\n", buffer);
    printf("%s\n", buffer2);

    return 0;
}
