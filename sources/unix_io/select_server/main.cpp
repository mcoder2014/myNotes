/***
 * https://zh.wikipedia.org/wiki/Select_(Unix)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <sys/select.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define PORT "8080"

/* function prototypes */
void die(const char*);

int main(int argc, char **argv)
{
    int sockfd,     // socket 的文件描述符
        neww, 
        maxfd, 
        on = 1, 
        nready, 
        i;
    struct addrinfo *res0, *res, hints;
    char buffer[BUFSIZ];        // 8196
    char sendBuffer[100] = "This is a select io server";

    fd_set master, readfds, writefds;
    ssize_t nbytes;

    // 用0 填充
    memset(&hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    if(-1 == (getaddrinfo(NULL, PORT, &hints, &res0)))
        die("getaddrinfo()");

    for(res = res0; res; res = res->ai_next)
    {
        if(-1 == (sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol)))
        {
            perror("socket()");
            continue;
        }

        if(-1 == (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(int))))
        {
            perror("setsockopt()");
            continue;
        }

        if(-1 == (bind(sockfd, res->ai_addr, res->ai_addrlen)))
        {
            perror("bind");
            continue;
        }

        break;
    }

    if(-1 == sockfd)
        exit(EXIT_FAILURE);
    freeaddrinfo(res0);

    if(-1 == (listen(sockfd, 32)))
        die("listen()");

    //设置new_fd无阻塞属性
    int flags;
    if ((flags = fcntl(sockfd, F_GETFL, 0)) < 0)
    {
        perror("fcntl F_GETFL");
    }
    flags |= O_NONBLOCK;
    if (fcntl(sockfd, F_SETFL, flags) < 0)
    {
        die("fcntl()");
    }

    FD_ZERO(&master);
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_SET(sockfd, &master);

    maxfd = sockfd;     // 此时只有一个文件描述符

    while(1)
    {
        memcpy(&readfds, &master, sizeof(master));
        memcpy(&writefds, &master, sizeof(master));
        printf("running select()\n");

        if(-1 == (nready = select(maxfd+1, &readfds, &writefds, NULL, NULL)))
            die("select()");
        printf("Number of ready descriptor: %d\n", nready);

        for(i=0; i<=maxfd && nready>0; i++)
        {
            if(FD_ISSET(i, &readfds))
            {
                // 检查文件描述符
                nready--;
                if(i == sockfd)
                {
                    // 如果 socket 的文件描述符有变化，可能是有连接建立
                    printf("Trying to accept() new connection(s)\n");
                    if(-1 == (neww = accept(sockfd, NULL, NULL)))
                    {
                        // 失败，报错
                        if(EWOULDBLOCK != errno)
                            die("accept()");
                        break;
                    }
                    else
                    {
                        // 将新的描述符加入到集合中
                        FD_SET(neww, &master);

                        if(maxfd < neww)
                            maxfd = neww;
                    }
                }
                else
                {
                    // 其他描述符发生改变，说明有描述符进入了可以状态，接受消息
                    nbytes = recv(i, buffer, sizeof(buffer), 0);
                    if(nbytes <= 0)
                    {
                        if(EWOULDBLOCK != errno)
                            die("recv()");
                        break;
                    }

                    buffer[nbytes] = '\0';
                    printf("%zi bytes received. fd: \n", nbytes, i);
                    printf("%s\n\n", buffer);
                }
            }

            if (FD_ISSET(i, &writefds))
            {
                nready--;
                printf("Send Message to Client %d\n", i);
                if (send(i, sendBuffer, strlen(sendBuffer), 0) == -1)
                {
                    die("send");
                }
                close(i);
            }
        }

    }

    return 0;
}

void die(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}