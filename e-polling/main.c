#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
    const int fd = epoll_create1(0);

    if (fd == 1){
        perror("epoll_create");
    }

    struct epoll_event events [2];

    events[0].events = EPOLL_CTL_ADD;
    events[0].data.fd = STDIN_FILENO;

    events[1].events = EPOLLOUT;
    events[1].data.fd = STDOUT_FILENO;

    epoll_ctl(fd, EPOLL_CTL_ADD, STDIN_FILENO, &events[0]);
    epoll_ctl(fd, EPOLL_CTL_ADD, STDOUT_FILENO, &events[1]);

    int res;

    res = epoll_wait(fd, events, 2, 100000 );


    char buffer[1024];
    // read(event.data.fd, buffer, 1024);

    printf("Hello, World! %i\n", res);
    // printf("Hello, World! %s\n", buffer);

    return 0;
}
