#include <apue.h>

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{

    char * filename = nullptr;
    if(argc > 1)
        filename = argv[1];
    else
    {
        err_quit("using as xxx filename\n");
    }

    FILE * fd = popen(filename, "r");

    sleep(300);

    pclose(fd);

    return 0;
}