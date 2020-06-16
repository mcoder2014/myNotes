#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <apue.h>

using namespace std;

int gl_var = 0; // 用来测试是否父进程子进程都能看到更改

int main(int argc, char** argv)
{

    int var;
    pid_t pid;

    var = 88;
    printf("before fork\n");

    if((pid = fork()) < 0)
    {
        cerr << "Create sub progress failed!" << endl;
    } else if(pid == 0)
    {
        // sub progress
        gl_var++;
        var++;
    } else
    {
        // parent progress
        sleep(2);
    }
    
    printf("pid= %ld, glob= %d, var= %d\n", (long)getpid(), gl_var, var);
    return 0;
}