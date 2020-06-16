#include <stdio.h>
#include <iostream>
#include <apue.h>
#include <sys/wait.h>

using namespace std;

void charatatime(char *);

int main()
{
    pid_t pid;

    TELL_WAIT();

    if((pid = fork()) < 0)
        cerr << "fork error" << endl;
    else if(pid == 0)
    {
        WAIT_PARENT();
        char tmp[] = "output from child\n";
        charatatime(tmp);
    }
    else 
    {
        char tmp[] ="output from parent\n"; 
        charatatime(tmp);
        TELL_CHILD(pid);
    }
    return 0;
}

void charatatime(char *str)
{
    char *ptr;
    int c;
    setbuf(stdout, NULL);
    for(ptr = str; (c = *ptr ++) != 0;)
        putc(c, stdout);
}