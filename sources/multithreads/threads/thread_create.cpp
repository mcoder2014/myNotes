#include <stdio.h>
#include <iostream>
#include "apue.h"
#include <pthread.h>

using namespace std;

pthread_t ntid;

void
printids(const char *s)
{
	pid_t		pid;
	pthread_t	tid;

	pid = getpid();
	tid = pthread_self();
	printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
	  (unsigned long)tid, (unsigned long)tid);
}

void *
thr_fn(void *arg)
{
    pthread_t	tid = pthread_self();
    printf("this thread is index:%d tid %lu\n", *(int*)arg, (unsigned long)tid);
	// printids("new thread: ");
    delete (int*)arg;
	return((void *)0);
}

int
main(int argc, char** argv)
{
	int err;

    int counts = 10;

    for(int i=0; i <argc; i++)
        printf("argv[%d]: %s\n", i, argv[i]);

    if(argc >= 2)
        counts = std::stoi(argv[1]);
    printf("Create new threads counts %d\n", counts);


    // 可以看出多线程执行次序每次是不确定的
    for(int i = 0; i < counts; i++)
    {
        int* arg = new int(i);
        err = pthread_create(&ntid, NULL, thr_fn, arg);
	    if (err != 0)
		    printf("can't create thread, %d\n", err);
    }

    printids("main thread:");
	sleep(1);
	exit(0);
}