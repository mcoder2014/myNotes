#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>

int BUF_SIZE = 1024;

void exitError(char* msg );

int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;

    mode_t filePerms;
    int numRead;
    char buf[BUF_SIZE];

    if(argc != 3) {
        printf("cp [sourceFile] [targetFile]\n");
    }

    inputFd = open(argv[1], O_RDONLY);
    if(inputFd == 1) {
        exitError("Open file failed");
    }
    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;  

    outputFd = open(argv[2], openFlags, filePerms);
    if(outputFd == -1) {
        exitError("outputFd failed\n");
    }

    while((numRead = read(inputFd, buf, BUF_SIZE)) > 0) {
        if(write(outputFd, buf, numRead) != numRead) {
            exitError("could not write\n");
        }
    }

    close(inputFd);
    close(outputFd);

    return 0;
}

void exitError(char* msg )
{
    printf("%s", msg);
    exit(1);
}