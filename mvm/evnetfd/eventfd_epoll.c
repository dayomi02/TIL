#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>             /* Definition of uint64_t */

#define handle_error(msg) \
   do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define EPOLL_SIZE 1

int main(int argc, char *argv[])
{
    int efd, j, ret;
    uint64_t u;
    ssize_t s;

    int epoll_fd;
    struct epoll_event events;

    /* epoll create*/
    epoll_fd =  epoll_create(EPOLL_SIZE);
    if( epoll_fd == -1){
        handle_error("epoll_create");
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <num>...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    /*eventfd create*/
    efd = eventfd(0, 0);
    if (efd == -1)
        handle_error("eventfd");

    events.events = EPOLLIN;
    events.data.fd = efd;

    ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, efd, &events);
    if(ret < 0){
        handle_error("epoll_ctl");
    }

    switch (fork()) {
    case 0:
        for (j = 1; j < argc; j++) {
            printf("Child writing %s to efd\n", argv[j]);
            u = strtoull(argv[j], NULL, 0);
                    /* strtoull() allows various bases */
            s = write(efd, &u, sizeof(uint64_t));
            if (s != sizeof(uint64_t))
                handle_error("write");
        }
        printf("Child completed write loop\n");

        exit(EXIT_SUCCESS);

    default:
        while(1){
            ret = epoll_wait(epoll_fd, &events, EPOLL_SIZE, -1);
            if(ret > 0){
                printf("Parent about to read\n");
                s = read(efd, &u, sizeof(uint64_t));
                if (s != sizeof(uint64_t))
                    handle_error("read");
                printf("Parent read %llu (0x%llx) from efd\n",
                    (unsigned long long) u, (unsigned long long) u);
                exit(EXIT_SUCCESS);
            }
        }

    case -1:
        handle_error("fork");
    }
} 