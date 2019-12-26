#include <stdio.h>
#include <iostream>
#include <apue.h>

using namespace std;

void charatatime(char *);

int main()
{
    pid_t pid;
    if((pid = fork()) < 0)
        cerr << "fork error" << endl;
    else if(pid == 0)
        charatatime("output from child\n");
    else 
        charatatime("output from parent\n");

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