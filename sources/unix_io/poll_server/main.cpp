#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <poll.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

#define MAXBUF 8196

int main(int argc, char *argv[])
{
    char buffer[MAXBUF];
    char sendBuffer[MAXBUF] = "Message from poll server";
    struct sockaddr_in addr;
    struct sockaddr_in client;
    int addrlen, n, i, max = 0;
    int sockfd, commfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("createSocket");
        return -1;
    }

    memset(&addr, 0, sizeof(struct sockaddr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定套接口
    bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr));
    //创建监听套接口
    listen(sockfd, 10);

    // poll 文件描述符集合
    pollfd pollfds[MAXBUF];
    int sendCount[MAXBUF];
    memset(pollfds, 0, MAXBUF * sizeof(pollfd));
    memset(pollfds, 0, MAXBUF * sizeof(int));

    // 配置 socket
    pollfds[0].fd = sockfd;
    pollfds[0].events = POLLIN;
    int fdCounts = 1;

    while (true)
    {
        printf("round again\n");
        if (poll(pollfds, fdCounts, 5000) == 0)
            continue;
        if (pollfds[0].revents & POLLIN)
        {
            // 建立 socket 链接
            int sin_size = sizeof(struct sockaddr_in);
            if (-1 == (pollfds[fdCounts].fd = accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&sin_size)))
            {
                perror("accept error!\n");
                continue;
            }
            else
            {
                printf("Accept link %d\n", fdCounts);
                pollfds[fdCounts].events = POLLIN | POLLOUT;
                fdCounts++;
            }
        }

        for (i = 1; i < fdCounts; i++)
        {
            if(pollfds[i].revents != 0)
                printf("Index %d  event : 0x%04x\n", i, pollfds[i].revents);
            if (pollfds[i].revents & POLLIN)
            {
                printf("index %d POLLIN event!\n", i);
                memset(buffer, 0, MAXBUF);
                if (recv(pollfds[i].fd, buffer, MAXBUF, 0) < 0)
                    perror("recv() error!\n");
                else
                    printf("index = %d Content = %s\n", i, buffer);
            }

            if (pollfds[i].revents & POLLOUT)
            {
                printf("index %d POLLOUT event!\n", i);
                if(!sendCount[i])
                {
                    sendCount[i]++;
                    printf("Send message to Client = %d\n", i);
                    if (send(pollfds[i].fd, sendBuffer, strlen(sendBuffer), 0) < 0)
                        perror("send() error!\n"); 
                }
            }

            if(pollfds[i].revents & POLLHUP)
            {
                close(pollfds[i].fd);
                pollfds[i].fd = -1;
            }
            pollfds[i].revents = 0;
        }
    }

    return 0;
}