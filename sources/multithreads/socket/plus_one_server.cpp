#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int main(int args, char**argv)
{
    cout << "This is Server " << endl;

    if(args < 2)
    {
        cout << "plus_one_server <port>" << endl;
        return 0;
    }

    //string strport(argv[1]);
    int port = std::atoi(argv[1]);
    cout << "set server port: " << port << endl;

    int listenfd, connfd;   // socket port and connect port
    socklen_t len;

    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    char ip[] = "127.0.0.1";
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &servaddr.sin_addr);

    char buff[1024] = "A message from server to clent !";
    char recbuf[1024]="";
    time_t ticks;

    // socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 512);

    cout << "Server config:\n"
         << "IP: " << inet_ntop(AF_INET, &servaddr.sin_addr, recbuf, sizeof(recbuf))
         << ":" << ntohs(servaddr.sin_port) << endl;

    for(;;)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr*) &cliaddr, &len);

        if(connfd >0)
        {
            cout << "Client info fd"<< connfd << ":\n"
                << "ip: " << inet_ntop(AF_INET, &cliaddr.sin_addr, recbuf, sizeof(recbuf))
                << ":" << htons(cliaddr.sin_port) << endl;

            bzero(recbuf, sizeof(recbuf)); // clear

            // 服务器先发送
            send(connfd, buff, strlen(buff), 0);

            // 再接收
            recv(connfd,recbuf,1024,0);
            cout << recbuf << endl;

            close(connfd);
        }
        else
        {
            cout << "connect failed!"<<endl;
        }
        

        
    }

    return 0;
}