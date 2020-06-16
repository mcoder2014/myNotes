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

    cout << "This is Client!" << endl;
    if(args < 3)
    {
        cout << "plus_one_client <ip> <port>" << endl;
        return 0;
    }

    //string strport(argv[1]);
    int port = std::atoi(argv[2]);
    cout << "Client set server port: " << port << endl;

    int socketfd;   // socket port and connect port
    socklen_t len;

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    char buff[1024] = "A message from client to server!";
    char recbuf[1024]="";
    time_t ticks;

    // socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    len = sizeof(servaddr);
    
    // connect
    int rtn = connect(socketfd, (struct sockaddr*) &servaddr, len);
    if(rtn == -1)
    {
        cout << "Connecting failed!" << endl;
        return 0;
    }

    cout << "Server config, fd: " << socketfd << "\n"
         << "IP: " << inet_ntop(AF_INET, &servaddr.sin_addr, recbuf, sizeof(recbuf))
         << ":" << ntohs(servaddr.sin_port) << endl;
    
    bzero(recbuf, sizeof(recbuf));

    // 客户端先接收
    recv(socketfd,recbuf,1024,0);
    cout << recbuf << endl;

    // 再发送
    send(socketfd, buff, strlen(buff), 0);

    close(socketfd);

    return 0;
}