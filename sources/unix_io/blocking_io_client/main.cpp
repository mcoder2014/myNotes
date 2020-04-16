#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <thread>
#include <vector>

#include <atomic>

using namespace std;


char sendBuff[8196] = "hello world From blocking io";
char recvBuff[8196];
struct hostent *he;
struct sockaddr_in their_addr;
int threads_count = 4;
atomic_int thread_count;

void link_with_server()
{
    thread_count.fetch_add(1);
    int thread_id = thread_count.load();

    int sockfd, numbytes;
    //建立一个TCP套接口
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("socket");
        exit(1);
    }
    //和服务器建立连接
    if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr))==-1)
    {
        perror("connect");
        exit(1);
    }

    //向服务器发送字符串
    printf("Thread: %d Send Message to Server\n", thread_id);
    if(send(sockfd,sendBuff,strlen(sendBuff),0)==-1)
    {
        perror("send");
        exit(1);
    }
    memset(sendBuff,0,sizeof(sendBuff));

    //接受从服务器返回的信息
    if((numbytes = recv(sockfd,recvBuff,sizeof(recvBuff),0))==-1)
    {
        perror("recv");
        exit(1);
    }
    printf("Thread: %d Receive message from server: %d \n %s\n",
        thread_id, numbytes,recvBuff);

    close(sockfd);
}

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("%s: input IP & port\n",argv[0]);
        return 1;
    }

    //将基本名字和地址转换
    he = gethostbyname(argv[1]);

    //初始化结构体
    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(atoi(argv[2]));
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero),8);

    thread_count.store(0);

    std::vector<thread> th_clients;
    for(int i =0; i <threads_count; i++)
    {
        th_clients.emplace_back(thread(link_with_server));
    }

    for(thread & th:th_clients)
    {
        th.join();
    }

    return 0;
}
