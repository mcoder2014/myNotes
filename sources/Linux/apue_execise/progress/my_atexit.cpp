#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

static void my_exit1(void);
static void my_exit2(void);

int main(int argc, char **argv)
{

    /// 输入的参数
    /// my_atexit -m 1 -h -alh
    /// argv[0]:        ./progress/bin/my_atexit
    /// argv[1]:        -m
    /// argv[2]:        1
    /// argv[3]:        -h
    /// argv[4]:        -alh
    for(int i =0; i < argc; i++)
    {
        printf("argv[%d]:\t%s\n",i, argv[i]);
    }

    /// 查看环境变量
    for(int i = 0; environ[i] != NULL; i++)
    {
        printf("environ[%d]:\t%s\n",i, environ[i]);
    }

    /// Get env
    char* path_env = getenv("PATH");
    printf("getenv(PATH):\t%s\n",path_env);

    /// putenv setenv unsetenv 
    /// 修改环境变量只能影响当前程序和子进程，无法影响父进程（shell）
    char test_env[] = "TEST=/home/chaoqun/";
    if(putenv(test_env) == 0)
    {
        path_env = getenv("TEST");
        printf("getenv(TEST):\t%s\n",path_env);
    }
    else
    {
        printf("Error! put env failed!\n");
    }
    

    /// 绑定终止处理程序
    if(atexit(my_exit2) != 0)
        cerr << "Error! can't register my_exit2" << endl;
    if(atexit(my_exit1) != 0)
        cerr << "Error! can't register my_exit1" << endl;
    if(atexit(my_exit1) != 0)
        cerr << "Error! can't register my_exit1" << endl;

    printf("Main is done!\n");

    return 0;
    /// 调用终止处理程序
    /// Main is done!  
    /// my_exit1 execute! 1 
    /// my_exit1 execute! 2 
    /// my_exit2 execute!
}

static void my_exit1(void)
{
    static int count = 0;
    printf("my_exit1 execute! %d \n", ++count);
}

static void my_exit2(void)
{
    printf("my_exit2 execute!\n");
}