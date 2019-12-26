#include <stdio.h>
#include <iostream>
#include <apue.h>
#include <sys/wait.h>

using namespace std;

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
        cerr << "fork error" << endl;
    else if(pid == 0)
    {
        if((pid = fork()) < 0)
            cerr << "fork error" << endl;
        else if(pid > 0)
            return 0;   // parent of second fork;

        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        return 0;
    }

    if(waitpid(pid, NULL, 0) != pid)
    {
        cerr << "waitpid error";
    }

    return 0;
}