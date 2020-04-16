#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAX_EVENTS 8196

using namespace std;

void setNoBlocking(int fd);

int main()
{

    struct epoll_event ev, events[MAX_EVENTS];
    int listen_sock, conn_sock, nfds, epollfd;
    struct sockaddr_in addr, cliaddr;
    char buff[8196];
    char sendBuff[8196] = "From Epoll Server\n";

    //初始化socket结构
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8080);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //创建socket
    if((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("createSocket");
        return -1;
    }
    //绑定套接口
    if(bind(listen_sock,(struct sockaddr *)&addr,sizeof(struct sockaddr))==-1)
    {
        perror("bind");
        return -1;
    }
    //创建监听套接口
    if(listen(listen_sock,10)==-1)
    {
        perror("listen");
        return -1;
    }

    // 创建 epoll 的描述符
    epollfd = epoll_create1(0);
    if (epollfd == -1)
    {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // 对 socket 的描述符监听 连接事件
    ev.events = EPOLLIN;
    ev.data.fd = listen_sock;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1)
    {
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);
        if (nfds == -1)
        {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < nfds; ++i)
        {
            if (events[i].data.fd == listen_sock)
            {
                int addrlen = sizeof(struct sockaddr_in);
                conn_sock = accept(
                    listen_sock, 
                    (struct sockaddr *)&addr, 
                    (socklen_t *)&addrlen);

                if (conn_sock == -1)
                {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }

                setNoBlocking(conn_sock);
                ev.events = EPOLLIN | EPOLLET | EPOLLOUT;
                ev.data.fd = conn_sock;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1)
                {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                // 处理 IO 事件
                if(events[i].events & EPOLLIN)
                {
                    int recvLength = recv(events[i].data.fd, buff, sizeof(buff), 0);
                    if(recvLength == 0)
                    {
                        close(events[i].data.fd);
                        epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                    } 
                    else if(recvLength < 0)
                    {
                        perror("recv failed");
                    }
                    else
                    {
                        printf("Receive %d bytes from client\n%s\n", recvLength, buff);
                    }
                }
                
                if(events[i].events & EPOLLOUT)
                {
                    send(events[i].data.fd, sendBuff, strlen(sendBuff), 0);
                    printf("Send Message to client\n");
                }

                if(events[i].events & EPOLLHUP || events[i].events & EPOLLET)
                {
                    epoll_ctl(epollfd, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                }
            }
        }
    }
    return 0;
}

void setNoBlocking(int fd)
{
    fcntl(fd, F_SETFL, O_NONBLOCK);
}