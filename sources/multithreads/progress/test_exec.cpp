#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <apue.h>

using namespace std;

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main()
{

    char *username = getlogin();
    printf("Login user: %s\n", username);

    pid_t pid;

    if((pid = fork()) <0)
    {
        cerr << "fork Error" << endl;
    } 
    else if (pid == 0)
    {
        //            argv[0]   argv[1]
        if(execle("/usr/bin/env", "env", (char*)0, env_init) < 0)
            cerr << "execle error" << endl;
        
        /// 子进程内容被替换，不会输出下方的分割线

        cout << "================================================" << endl;
    }

    if(waitpid(pid, NULL, 0) < 0)
        cerr << "wait error" << endl;
    
    if((pid = fork()) <0)
    {
        cerr << "fork Error" << endl;
    } 
    else if (pid == 0)
    {
        if(execlp("env", "echoall", (char*)0) < 0)
            cerr << "execle error" << endl;
    }

    if(waitpid(pid, NULL, 0) < 0)
        cerr << "wait error" << endl;

    return 0;
}