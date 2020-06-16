#include <apue.h>
#include <stdio.h>
#include <pthread.h>


void *th_func(void * arg)
{
    
    pthread_t tid;
    tid = pthread_self();

    pid_t pid = getpid();

    for(int i =0; i < 10000; i++)
    {
        printf("th_func pid:%lld thread_id:%lld\n", (u_int64_t)pid, (unsigned long long)tid);
        usleep(1000000);
    }

    return (void *)0;
}

int main(int argc, char** argv)
{

    pthread_t tid;
    int err;
    char stss[] = "Dancing";
    if(err = pthread_create(&tid, NULL, th_func, (void *)stss) != 0)
        printf("pthread_create error: %d", err);


    // pause();
    
    pthread_t mtid = pthread_self();

    // test fork
    pid_t pid;
    if((pid = fork()) < 0)
    {
        // error
        printf("fork error");
    }
    else if(pid == 0)
    {
        // son
        pid = getpid();
        pthread_t son_tid = pthread_self();
        while(1)
        {
            printf("son Main pid:%lld thread_id:%lld\n", (u_int64_t)pid, (unsigned long long)son_tid);
            sleep(1);
        }
    }
    else 
    {
        // parent
        pid = getpid();
        pthread_t tid = pthread_self();
        while (1)
        {
            /* code */
            printf("Main pid:%lld thread_id:%lld\n", (u_int64_t)pid, (unsigned long long)tid);
            sleep(1);
        }

        return 0;       
    }

    

    return 0;
}