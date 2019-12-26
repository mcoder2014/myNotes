#include <iostream>
#include <stdlib.h>
#include <apue.h>
#include <sys/wait.h>

using namespace std;

void pr_exit(int status)
{
    if(WIFEXITED(status))
        printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
    else if(WIFSIGNALED(status))
            printf("abnormal termination, signal number = %d%s\n",
                WTERMSIG(status),
#ifdef WCOREDUMP
            WCOREDUMP(status) ? " (core file generated)" : "");
#else
    "");
#endif
    else if(WIFSTOPPED(status))
        printf("child stopped, signal number = %d\n", WSTOPSIG(status));
    
}

int main()
{
    pid_t pid;
    int status;

// normal
    if((pid = fork()) < 0)
        cerr<<"Error! fork" << endl;
    else if (pid == 0)
        exit(7);

    if(wait(&status) != pid)
        cerr << "Error! wait!" << endl;
    pr_exit(status);

// generate SIGABRT
    if((pid = fork()) < 0)
        cerr <<"fork error" << endl;
    else if(pid == 0)     
        abort();

    if(wait(&status)!=pid)
        cerr << "wait error" << endl;
    pr_exit(status);


// generate SIGFPE
    int test = 0;
    if((pid = fork()) < 0)
        cerr <<"fork error" << endl;
    else if(pid == 0)     
        status /= test;
    
    if(wait(&status)!=pid)
        cerr << "wait error" << endl;
    pr_exit(status);

    return 0;
}