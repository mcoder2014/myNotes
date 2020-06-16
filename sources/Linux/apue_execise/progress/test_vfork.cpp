
#include <iostream>
#include <stdio.h>
#include <apue.h>

using namespace std;

int gl_var = 6;
int main()
{
    int var;
    pid_t pid;

    var = 88;
    printf("before vfork;\n");

    if((pid = vfork()) < 0)
    {
        cerr<<"Error;" << endl;
    }
    else if (pid == 0)
    {
        // sub
        gl_var++;
        var++;
        _exit(0);
    }
    else 
    {
        // parent
        printf("pid= %ld, glob= %d, var= %d\n", (long)getpid(), gl_var, var);
    }

    return 0;
}