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
#define PORT 8080

void rmPollfd(pollfd* pollfds, int index, int& fdCounts) 
{
    for(int i = index; i < fdCounts - 1; i++)
    {
        pollfds[i].events = pollfds[i+1].events;
        pollfds[i].fd = pollfds[i+1].fd;
        pollfds[i].revents = pollfds[i+1].revents;
    }

    pollfds[fdCounts-1].fd = 0;
    pollfds[fdCounts-1].events = 0;
    pollfds[fdCounts-1].revents = 0;

    fdCounts--;
}

int main(int argc, char **argv)
{
    char buffer[MAXBUF];
    char sendBuffer[MAXBUF] = "Message from poll server";
    struct sockaddr_in addr;
    struct sockaddr_in client;
    int addrlen, n, i, max = 0;
    int sockfd, commfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(sockfd, 32);

    pollfd pollfds[MAXBUF];
    memset(pollfds, 0, MAXBUF * sizeof(pollfd));

    // 配置 socket
    pollfds[0].fd = sockfd;
    pollfds[0].events = POLLIN ;
    int fdCounts = 1;

    while (true)
    {
        puts("round again");
        poll(pollfds, fdCounts, 50000);
        if(pollfds[0].revents & POLLIN) 
        {
            // 建立 socket 链接
            if(-1 == (pollfds[fdCounts].fd = accept(pollfds[0].fd, NULL, NULL)))
            {
                perror("accept error!\n");
                exit(1);
            }
            else
            {
                printf("Accept link %d\n", fdCounts);
                pollfds[fdCounts].events = POLLIN | POLLOUT ;
                fdCounts++;
            }
        }

        for (i = 1; i < fdCounts; i++)
        {
            if (pollfds[i].revents & POLLIN)
            {
                memset(buffer, 0, MAXBUF);
                if(recv(pollfds[i].fd, buffer, MAXBUF, 0) < 0)
                {
                    perror("recv error\n");
                }
                else
                {
                    printf("index = %d Content = %s\n", i, buffer);
                }
            }
            
            if(pollfds[i].revents & POLLOUT)
            {
                send(pollfds[i].fd, sendBuffer, strlen(sendBuffer),0);
                printf("Send message to Client = %d\n", i);
                
                close(pollfds[i].events);
                rmPollfd(pollfds, i, fdCounts);
                i--;
            }
            pollfds[i].revents = 0;
        }
    }

    return 0;
}